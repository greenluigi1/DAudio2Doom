#include "doomAppView.h"
#include "doomgeneric.h"

DoomAppView::DoomAppView(Application *application, const char *name)
    : AppView(application, name)
{
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "DoomAppView::Constructor called");
}

void DoomAppView::onCreate(int32_t argc, const char *argv[])
{
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "DoomAppView::onCreate called");
    mainWindow = new MainWindow(this, 0);
    HelixQt::Window::init(mainWindow, this);
    HelixQt::Window::setViewSizeAlwaysFull(mainWindow, false);
}

void DoomAppView::onStart()
{
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "DoomAppView::onStart called");
    HelixQt::Window::show(mainWindow);
}

void DoomAppView::onNewStart(int32_t argc, const char **argv)
{
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "DoomAppView::onNewStart called");
    HelixQt::Window::show(mainWindow);
}

void DoomAppView::onStop()
{
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "DoomAppView::onStop called");
    HelixQt::Window::hide(mainWindow);
}

void DoomAppView::onDestroy()
{
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "DoomAppView::onDestroy called");

    if (mainWindow)
    {
        HelixQt::Window::finish(mainWindow);
        delete mainWindow;
    }

    qApp->quit();
}
