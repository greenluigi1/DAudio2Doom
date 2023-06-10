#include "doomkeys.h"

#include "doomgeneric.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include <QApplication>
#include <android/log.h>
#include <doomGuiApplication.h>
#include <stdarg.h>
#include "i_video.h"

#define KEYQUEUE_SIZE 16

MainWindow *doomRenderWindow = 0;

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

void addDoomKeyToQueue(int pressed, SimpleDoomKey doomKey)
{
    if (doomKey == SimpleDoomKey::NONE)
    {
        return;
    }

    unsigned char key =  static_cast<unsigned char>(doomKey);
    unsigned short keyData = (pressed << 8) | key;

    s_KeyQueue[s_KeyQueueWriteIndex] = keyData;
    s_KeyQueueWriteIndex++;
    s_KeyQueueWriteIndex %= KEYQUEUE_SIZE;
}

void DG_Log(const char* logMessage)
{
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", logMessage);
}

int DG_Log_printf(const char *__restrict __format, ...)
{
    int result;
    va_list args;
    va_start(args, __format);
    result = __android_log_vprint(ANDROID_LOG_DEBUG, "DAudio2Doom", __format, args);
    va_end(args);

    return result;
}

int DG_Log_vprintf(const char *__restrict __format, va_list ap)
{
    return __android_log_vprint(ANDROID_LOG_DEBUG, "DAudio2Doom", __format, ap);
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QGuiApplication::setQuitOnLastWindowClosed(true);
    doomGuiApplication = new DoomGuiApplication();
    doomGuiApplication->init(app, argc, argv);

    DG_Log("creating doomArgs");
    int doomArgc = 0;
    char *doomArgs[] = {
        NULL
    };

    DG_Log("creating s_KeyQueue");
    memset(s_KeyQueue, 0, KEYQUEUE_SIZE * sizeof(unsigned short));

    DG_Log("doomgeneric_Create() begin");
    doomgeneric_Create(doomArgc, doomArgs);
    DG_Log("doomgeneric_Create() done");

    return app.exec();
}

void DG_DrawFrame()
{
    if (doomRenderWindow)
    {
        doomRenderWindow->refreshDrawingBuffer();
    }
    else
    {
        DG_Log("Tried to DG_DrawFrame() but doomRenderWindow == NULL.");
    }
}

void DG_SleepMs(uint32_t ms)
{
    usleep (ms * 1000);
}

uint32_t DG_GetTicksMs()
{
    struct timeval  tp;
    struct timezone tzp;

    gettimeofday(&tp, &tzp);

    return (tp.tv_sec * 1000) + (tp.tv_usec / 1000); /* return milliseconds */
}

int DG_GetKey(int* pressed, unsigned char* doomKey)
{
    if (s_KeyQueueReadIndex == s_KeyQueueWriteIndex)
    {
        //key queue is empty

        return 0;
    }
    else
    {
        unsigned short keyData = s_KeyQueue[s_KeyQueueReadIndex];
        s_KeyQueueReadIndex++;
        s_KeyQueueReadIndex %= KEYQUEUE_SIZE;

        *pressed = keyData >> 8;
        *doomKey = keyData & 0xFF;

        return 1;
    }
}

void DG_SetWindowTitle(const char * title)
{
    std::string message = std::string("DG_SetWindowTitle() called setting title to: ");
    message.append(title);

    DG_Log(message.c_str());
}
