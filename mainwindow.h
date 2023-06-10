#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <helix/app/AppView.h>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include "HBody.h"
#include "HChassis.h"
#include "HSeat.h"
#undef KEY_HOME
#undef KEY_ENTER
#include "HModeManager.h"
#include "simpledoomkeys.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public IHModeChangeListener
{
    Q_OBJECT

public:
    MainWindow(AppView *appView, QWidget *parent = nullptr);
    ~MainWindow();
    void refreshDrawingBuffer();
    void onModeStart(int32 modeType,  int32 foregroundOption, int32 mainReason) override {};
    void onAVPowerChanged(int32 status, int32 type) override {};
    void onModeChanged(int32 modeType, int32 runningOption) override {};
    void onModeStatusChanged(int32 modeType, int32 status) override {};
    void onKeyEvent(int32 curMode, int32 keyNum, int32 keyParam) override;
    void onKeyEvent_blocked(int32 curMode, int32 keyNum, int32 keyParam, int32 reason) override {};

private slots:
    void on_dumpButton_clicked();

private:
    void buckleCheckTimerTick();
    void gameTimerTick();
    void inputTimerTick();
    void startGame();
    QPixmap bufferQPixmap;
    QImage *bufferQImage;
    Ui::MainWindow *ui;
    AppView *appView;
    ccos::vehicle::general::HBody* hBody;
    ccos::vehicle::general::HChassis* hChassis;
    ccos::vehicle::general::HSeat * hSeat;
    HModeManager * hModeManager;

    bool isBuckledIn;
    QTimer* buckleCheckTimer;
    SimpleDoomKey lastDirection;
    SimpleDoomKey currentDirection;
};

#endif // MAINWINDOW_H

