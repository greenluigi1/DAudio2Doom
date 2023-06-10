#ifndef DOOM_GENERIC
#define DOOM_GENERIC

#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include "doomkeys.h"
#include "simpledoomkeys.h"

#ifdef __cplusplus
#include "doomGuiApplication.h"
#include "mainwindow.h"
#endif

#define DOOMGENERIC_RESX 640
#define DOOMGENERIC_RESY 400


extern uint32_t* DG_ScreenBuffer;

#ifdef __cplusplus
extern "C" {
#endif
void doomgeneric_Create(int argc, char **argv);
void doomgeneric_Tick();
void DG_Init();
void DG_DrawFrame();
void DG_SleepMs(uint32_t ms);
uint32_t DG_GetTicksMs();
int DG_GetKey(int* pressed, unsigned char* key);
void DG_SetWindowTitle(const char * title);
void DG_Log(const char* logMessage);
int DG_Log_vprintf(const char *__restrict __format, va_list ap);
int DG_Log_printf(const char *__restrict __format, ...);
#ifdef __cplusplus
    void addDoomKeyToQueue(int pressed, SimpleDoomKey key);
    static DoomGuiApplication *doomGuiApplication;
    extern MainWindow *doomRenderWindow;
}
#endif

#endif //DOOM_GENERIC
