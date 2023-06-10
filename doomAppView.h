#ifndef DOOMAPPVIEW_H
#define DOOMAPPVIEW_H

#include <helix/app/ApplicationQt.h>
#include <helix/app/AppView.h>
#include <helix/display/HelixQt.h>
#include "mainwindow.h"

class DoomAppView : public AppView
{
public:
    DoomAppView(Application *application, const char *name);
    void onCreate(int32_t argc, const char *argv[]) override;
    void onStart() override;
    void onNewStart(int32_t argc, const char *argv[]) override;
    void onStop() override;
    void onDestroy() override;
private:
    MainWindow *mainWindow;
};

#endif // DOOMAPPVIEW_H
