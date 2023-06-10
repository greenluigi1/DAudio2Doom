#include "doomGuiApplication.h"
#include <android/log.h>

DoomGuiApplication::DoomGuiApplication()
{
}

AppView *DoomGuiApplication::createAppView(Application *application, const char *componentName)
{
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "DoomGuiApplication::createAppView was called: %s", componentName);

    if (!strcmp(componentName, "com.greenluigi1.doom.DoomAppView"))
    {
        __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "Launching DoomAppView");
        DoomAppView *appView = new DoomAppView(application, componentName);
        return appView;
    }

    return nullptr;
};

AppService *DoomGuiApplication::createAppService(Application *application, const char *componentName)
{
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "DoomGuiApplication::createAppService was called: %s", componentName);
    return nullptr;
};

EventReceiver *DoomGuiApplication::createEventReceiver(const char *componentName)
{
    __android_log_print(ANDROID_LOG_DEBUG, "DAudio2Doom", "DoomGuiApplication::createEventReceiver was called: %s", componentName);
    return nullptr;
};
