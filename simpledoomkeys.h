#ifndef SIMPLEDOOMKEYS_H
#define SIMPLEDOOMKEYS_H

#include "doomkeys.h"

enum SimpleDoomKey
{
    NONE = 0, // Same as KEY_PERIOD, might need to change this?
    RIGHT = KEY_RIGHTARROW,
    LEFT =  KEY_LEFTARROW,
    UP =  KEY_UPARROW,
    DOWN = KEY_DOWNARROW,
    USE = KEY_USE,
    FIRE = KEY_FIRE,
    ESCAPE = KEY_ESCAPE,
    ENTER = 13, // I don't want to deal with the stupid #define conflicts so 13 it is (13 == KEY_ENTER)
};
#endif // SIMPLEDOOMKEYS_H
