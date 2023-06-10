#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <android/log.h>
#include "ccosutils.h"
#include <QTimer>
#include "doomgeneric.h"
#include <QPixmap>
#include <QFile>
#include "ccosutils.h"
#include "HSeat.h"
#include <QKeyEvent>
#include "doomgeneric.h"
#include "DAudio2DoomConfig.h"

MainWindow::MainWindow(AppView *appView, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->appView = appView;
    setGeometry(0, 0, 799, 419);
    setWindowFlags(Qt::WindowType::Window);

    this->bufferQImage = new QImage((uchar *)DG_ScreenBuffer, DOOMGENERIC_RESX, DOOMGENERIC_RESY, QImage::Format::Format_RGB32);
    ui->displayLabel->setPixmap(QPixmap::fromImage(*bufferQImage));

    ui->dumpButton->setVisible(RENDER_DUMP_BUTTON);

    hSeat = ccos::vehicle::general::HSeat::getInstance();
    hBody = ccos::vehicle::general::HBody::getInstance();
    hChassis = ccos::vehicle::general::HChassis::getInstance();

    hModeManager = HModeManager::getInstance();
    hModeManager->setEventListener(this);

    buckleCheckTimer = new QTimer(this);
    connect(buckleCheckTimer, &QTimer::timeout, this, &MainWindow::buckleCheckTimerTick);
    buckleCheckTimer->start(1000);// Checks every second

    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "MainWindow constructor()");

    doomRenderWindow = this;

#if DAUDIO2DOOM_EXTRA_LOGGING
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "MainWindow constructor() DG_ScreenBuffer is: %u", DG_ScreenBuffer);
#endif
}

MainWindow::~MainWindow()
{
    delete bufferQImage;
    delete ui;
}

void MainWindow::startGame()
{
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "MainWindow::startGame()");
    QTimer *gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &MainWindow::gameTimerTick);

    QTimer *inputTimer = new QTimer(this);
    connect(inputTimer, &QTimer::timeout, this, &MainWindow::inputTimerTick);

    gameTimer->start(10);
    inputTimer->start(20);
}

void MainWindow::onKeyEvent(int32 curMode, int32 keyNum, int32 keyParam)
{
    if (!isBuckledIn)
    {
        return;
    }

    bool isPressed = !(keyParam & 1);
    KeyConstants::KeyNum keyType = static_cast<KeyConstants::KeyNum>(keyNum);

    switch(keyType)
    {
    case (KeyConstants::KeyNum::SWRKEY_SEEK_DOWN): // Is actually up
    addDoomKeyToQueue(isPressed, SimpleDoomKey::UP);
    break;
    case (KeyConstants::KeyNum::SWRKEY_SEEK_UP): // Is actually down
    addDoomKeyToQueue(isPressed, SimpleDoomKey::DOWN);
    break;
    case (KeyConstants::KeyNum::SWRKEY_MUTE):
    addDoomKeyToQueue(isPressed, SimpleDoomKey::USE);
    break;
    case (KeyConstants::KeyNum::SWRKEY_END):
    addDoomKeyToQueue(isPressed, SimpleDoomKey::FIRE);
    break;
    case (KeyConstants::KeyNum::KEY_POWER):
    addDoomKeyToQueue(isPressed, SimpleDoomKey::ENTER);
    break;
    case (11):
    addDoomKeyToQueue(isPressed, SimpleDoomKey::ESCAPE);
    break;
    default:
        break;
    }

#if DAUDIO2DOOM_EXTRA_LOGGING
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "MainWindow::onKeyEvent() Current Mode (%u) Key Num (%u) Key Param (%u)", curMode, keyNum, keyParam);
#endif
}

void MainWindow::buckleCheckTimerTick()
{
    ccos::vehicle::HTriState isDriverSeatBeltBuckleLatched;
    ccos::HResult driverSeatBeltResult = hSeat->isSeatBeltBuckleLatched(ccos::vehicle::HSeatPosition::DRIVER, isDriverSeatBeltBuckleLatched);

#if DAUDIO2DOOM_EXTRA_LOGGING
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "MainWindow::buckleCheckTimerTick() Is Driver Seat Belt Buckle Latched (%s)", ccOSUtils::HTriStateToString(isDriverSeatBeltBuckleLatched));
#endif

    if(driverSeatBeltResult == ccos::HResult::OK)
    {
        if(isDriverSeatBeltBuckleLatched == ccos::vehicle::HTriState::TRUEE)
        {
            buckleCheckTimer->stop();
            isBuckledIn = true;
            ui->buckleInLabel->setEnabled(false);
            ui->buckleInLabel->setVisible(false);
            startGame();
        }
    }
}

void MainWindow::gameTimerTick()
{
    doomgeneric_Tick();
}

void MainWindow::inputTimerTick()
{
    const float DEAD_ZONE_MIN = 7;
    const float HALF_MARK = 3276.75;
    const float DEAD_ZONE_MAX = 6546.5;

    ccos::HFloat steeringAngle;
    ccos::HResult steeringResult = hChassis->getSteeringAngle(steeringAngle);

    SimpleDoomKey newDirection = SimpleDoomKey::NONE;

    if (steeringResult == ccos::HResult::OK)
    {
        if (steeringAngle > HALF_MARK && steeringAngle < DEAD_ZONE_MAX)
        {
            newDirection = SimpleDoomKey::RIGHT;
        }
        else if (steeringAngle < HALF_MARK && steeringAngle > DEAD_ZONE_MIN)
        {
            newDirection = SimpleDoomKey::LEFT;
        }
    }

    if (currentDirection != newDirection)
    {
        if (currentDirection != SimpleDoomKey::NONE)
        {
            addDoomKeyToQueue(0, currentDirection);
        }

        addDoomKeyToQueue(1, newDirection);

#if DAUDIO2DOOM_EXTRA_LOGGING
        __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "MainWindow::inputTimerTick() Current Direction (%u) New Direction (%u)", currentDirection, newDirection);
#endif
    }

    currentDirection = newDirection;
}

void MainWindow::refreshDrawingBuffer()
{
    ui->displayLabel->setPixmap(QPixmap::fromImage(*bufferQImage));
}

void MainWindow::on_dumpButton_clicked()
{
    ccos::HFloat steeringAngle;
    ccos::HResult steeringResult = hChassis->getSteeringAngle(steeringAngle);
    ccos::HUInt8 pedalState;
    ccos::HResult pedalResult = hChassis->getAcceleratorPedalState(pedalState);

    ccos::vehicle::HTriState isSeatBeltBuckleLatched;
    ccos::HResult seatBeltResult = hSeat->isSeatBeltBuckleLatched(ccos::vehicle::HSeatPosition::DRIVER, isSeatBeltBuckleLatched);


    ccos::vehicle::HTriState isLeftTurnSignalOn;
    ccos::vehicle::HTriState isRightTurnSignalOn;
    ccos::HResult leftTurnSignalResult = hBody->isTurnSignalSwitchOn(ccos::vehicle::HTurnSignalType::LEFT, isLeftTurnSignalOn);
    ccos::HResult rightTurnSignalResult = hBody->isTurnSignalSwitchOn(ccos::vehicle::HTurnSignalType::RIGHT, isRightTurnSignalOn);

    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "MainWindow::on_dumpButton_clicked()");
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "Steering Angle Result: (%s) State: (%f)", ccOSUtils::HResultToString(steeringResult), steeringAngle);
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "Accelerator Pedal State Result: (%s) State: (%u)", ccOSUtils::HResultToString(pedalResult), pedalResult);
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "Is Driver Seat Belt Buckle Latched: (%s) State: (%u)", ccOSUtils::HResultToString(seatBeltResult), isSeatBeltBuckleLatched);
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "Is Left Turn Signal On: (%s) State: (%s)", ccOSUtils::HResultToString(leftTurnSignalResult), ccOSUtils::HTriStateToString(isLeftTurnSignalOn));
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "Is Right Turn Signal On: (%s) State: (%s)", ccOSUtils::HResultToString(rightTurnSignalResult), ccOSUtils::HTriStateToString(isRightTurnSignalOn));

    // Uncomment to dump the frame buffer
    //QFile fbFile("/run/media/B208-FF9A/DoomFrameBufferDump");
    //fbFile.open(QFile::OpenModeFlag::WriteOnly);
    //fbFile.write((char*)DG_ScreenBuffer, DOOMGENERIC_RESX * DOOMGENERIC_RESY * 4);
    //fbFile.close();

}
