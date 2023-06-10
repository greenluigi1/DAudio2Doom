#ifndef DOOMGUIAPPLICATION_H
#define DOOMGUIAPPLICATION_H

#include <helix/app/ApplicationQt.h>
#include <helix/app/AppView.h>
#include <helix/display/HelixQt.h>
#include <helix/app/EventReceiver.h>
#include <helix/app/AppManager.h>
#include "doomAppView.h"

class DoomGuiApplication : public ApplicationQt
{
public:
    DoomGuiApplication();
protected:
    AppView *createAppView(Application *application, const char *componentName) override;
    AppService *createAppService(Application *application, const char *componentName) override;
    EventReceiver *createEventReceiver(const char *componentName) override;
};

#endif // DOOMGUIAPPLICATION_H
