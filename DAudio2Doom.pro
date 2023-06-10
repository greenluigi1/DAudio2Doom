QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SYSTEM_IMAGE_ROOT = /home/greenluigi1/Desktop/QtDev/system_image

INCLUDEPATH += $$SYSTEM_IMAGE_ROOT/usr/include/glib-2.0
INCLUDEPATH += $$SYSTEM_IMAGE_ROOT/usr/lib/glib-2.0/include

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    am_map.c \
    ccosutils.cpp \
    d_event.c \
    d_items.c \
    d_iwad.c \
    d_loop.c \
    d_main.c \
    d_mode.c \
    d_net.c \
    doomAppView.cpp \
    doomGuiApplication.cpp \
    doomdef.c \
    doomgeneric.c \
    doomgeneric_daudio.cpp \
    doomstat.c \
    dstrings.c \
    dummy.c \
    f_finale.c \
    f_wipe.c \
    g_game.c \
    gusconf.c \
    hu_lib.c \
    hu_stuff.c \
    i_cdmus.c \
    i_endoom.c \
    i_input.c \
    i_joystick.c \
    i_scale.c \
    i_sound.c \
    i_system.c \
    i_timer.c \
    i_video.c \
    icon.c \
    info.c \
    m_argv.c \
    m_bbox.c \
    m_cheat.c \
    m_config.c \
    m_controls.c \
    m_fixed.c \
    m_menu.c \
    m_misc.c \
    m_random.c \
    mainwindow.cpp \
    memio.c \
    mus2mid.c \
    p_ceilng.c \
    p_doors.c \
    p_enemy.c \
    p_floor.c \
    p_inter.c \
    p_lights.c \
    p_map.c \
    p_maputl.c \
    p_mobj.c \
    p_plats.c \
    p_pspr.c \
    p_saveg.c \
    p_setup.c \
    p_sight.c \
    p_spec.c \
    p_switch.c \
    p_telept.c \
    p_tick.c \
    p_user.c \
    r_bsp.c \
    r_data.c \
    r_draw.c \
    r_main.c \
    r_plane.c \
    r_segs.c \
    r_sky.c \
    r_things.c \
    s_sound.c \
    sha1.c \
    sounds.c \
    st_lib.c \
    st_stuff.c \
    statdump.c \
    tables.c \
    v_video.c \
    w_checksum.c \
    w_file.c \
    w_file_stdc.c \
    w_main.c \
    w_wad.c \
    wi_stuff.c \
    z_zone.c

HEADERS += \
    DAudio2DoomConfig.h \
    am_map.h \
    ccosutils.h \
    config.h \
    d_englsh.h \
    d_event.h \
    d_items.h \
    d_iwad.h \
    d_loop.h \
    d_main.h \
    d_mode.h \
    d_player.h \
    d_textur.h \
    d_think.h \
    d_ticcmd.h \
    deh_main.h \
    deh_misc.h \
    deh_str.h \
    doom.h \
    doomAppView.h \
    doomGuiApplication.h \
    doomdata.h \
    doomdef.h \
    doomfeatures.h \
    doomgeneric.h \
    doomkeys.h \
    doomstat.h \
    doomtype.h \
    dstrings.h \
    f_finale.h \
    f_wipe.h \
    g_game.h \
    gusconf.h \
    hu_lib.h \
    hu_stuff.h \
    i_cdmus.h \
    i_endoom.h \
    i_joystick.h \
    i_scale.h \
    i_sound.h \
    i_swap.h \
    i_system.h \
    i_timer.h \
    i_video.h \
    info.h \
    m_argv.h \
    m_bbox.h \
    m_cheat.h \
    m_config.h \
    m_controls.h \
    m_fixed.h \
    m_menu.h \
    m_misc.h \
    m_random.h \
    mainwindow.h \
    memio.h \
    mus2mid.h \
    net_client.h \
    net_dedicated.h \
    net_defs.h \
    net_gui.h \
    net_io.h \
    net_loop.h \
    net_packet.h \
    net_query.h \
    net_sdl.h \
    net_server.h \
    p_inter.h \
    p_local.h \
    p_mobj.h \
    p_pspr.h \
    p_saveg.h \
    p_setup.h \
    p_spec.h \
    p_tick.h \
    qdoomrenderer.h \
    r_bsp.h \
    r_data.h \
    r_defs.h \
    r_draw.h \
    r_local.h \
    r_main.h \
    r_plane.h \
    r_segs.h \
    r_sky.h \
    r_state.h \
    r_things.h \
    s_sound.h \
    sha1.h \
    simpledoomkeys.h \
    sounds.h \
    st_lib.h \
    st_stuff.h \
    statdump.h \
    tables.h \
    v_patch.h \
    v_video.h \
    w_checksum.h \
    w_file.h \
    w_main.h \
    w_merge.h \
    w_wad.h \
    wi_stuff.h \
    z_zone.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#QMAKE_CXXFLAGS += -nodefaultlibs
#QMAKE_CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0 -v

unix:!macx: LIBS += -lstdc++

unix:!macx: LIBS += -lhelix

unix:!macx: LIBS += -lhelixqt

unix:!macx: LIBS += -lHVehicle

unix:!macx: LIBS += -llog

unix:!macx: LIBS += -lHLite

#unix:!macx: LIBS += -lc

#unix:!macx: LIBS += -lgcc_s

#unix:!macx: LIBS += -lgcc

DISTFILES += \
    DAudio2Doom.pro.user \
    DAudio2Doom.pro.user.1c77eae \
    DAudio2Doom.pro.user.aa5c7d4 \
    DAudio2Doom.user \
    GuiExampleApp.appconf \
    Makefile \
    Makefile.emscripten \
    Makefile.freebsd \
    Makefile.sdl \
    Makefile.soso \
    Makefile.sosox \
    README.md \
    doomgeneric.vcxproj \
    doomgeneric.vcxproj.filters \
    installApp.sh

RESOURCES += \
    DoomResources.qrc
