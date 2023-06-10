# D-Audio 2V Doom
This contains a basic port of DOOM for D-Audio 2V IVIs.

DAudio2Doom is based off of [doomgeneric by ozkl](https://github.com/ozkl/doomgeneric).

To see more information on creating D-Audio 2 applications visit [my blog](https://programmingwithstyle.com/tags/d-audio2/).

## Installing
To install DAudio2Doom on a D-Audio2V head unit make sure you have a root shell. Follow [this guide](https://programmingwithstyle.com/posts/howihackedmycarpart5/) to create an ADB backdoored firmware for your head unit if you do not already have one.

You will need three files, the DAudio2Doom.appconf file, the DAudio2Doom executable, and a DOOM.WAD file you want to play. The DAudio2Doom.appconf file and the DAudio2Doom executable can be found in the releases section. You must find the DOOM.WAD file yourself.

Copy all 3 files to a FAT32 formatted flash drive.

Launch a root shell on the head unit and run the following commands:
```
ls -al /run/media/
```
take note of the folder listed (There should only be one). This folder is your flash drive. Substitute the listed folder in the next commands.


This will remount the root to be writable:
```
mount -o rw,remount /
```

This will copy the DAudio2Doom app configuration file to the system:
```
cp /run/media/{YourFlashDriveGuid}/DAudio2Doom.appconf /etc/appmanager/appconf
```

This will copy the DAudio2Doom binary to the appdata folder on the head unit:
```
cp /run/media/{YourFlashDriveGuid}/DAudio2Doom /appdata
```

This will copy the Doom WAD file to the appdata folder on the head unit:
```
cp /run/media/{YourFlashDriveGuid}/DOOM.WAD /appdata
```

Reboot the head unit so the DAudio2Doom app configuration will be loaded:
```
reboot
```

## Running DAudio2Doom
After DAudio2Doom is installed, open a root shell and use the following command to start Doom.
```
appctl startAppView com.greenluigi1.doom.DoomAppView
```

To stop DAudio2Doom, run the command:
```
appctl finishAppView com.greenluigi1.doom.DoomAppView
```

## Build Notes
I recommend using Ubuntu 20.04 as the development OS.

Follow the guide [here](https://programmingwithstyle.com/posts/howihackedmycarpart3/#automating-it) to setup a development environment for D-Audio 2 application development.

Before building, edit the SYSTEM_IMAGE_ROOT variable in DAudio2Doom.pro to point to the root of your head unit's mounted system image.

Make sure your system image is mounted before trying to run QT Creator.

## Controls
| Vehicle Input Location | Vehicle Input | Doom Input |
| ----------- | ----------- | ----------- |
| Steering Wheel | Turning wheel Left | Left Arrow Key  |
| Steering Wheel | Turning wheel Right | Right Arrow Key  |
| Steering Wheel | Seek Down Key (Which is actually the up key) | Up Arrow Key  |
| Steering Wheel | Seek Up Key (Which is actually the down key) | Down Arrow Key  |
| Steering Wheel | Mute Button | Use  |
| Steering Wheel | End Call Button | Fire |
| Head Unit | Volume Knob Press | Enter |
| Head Unit | Tune Knob Press | Escape |

## Settings
Check the DAudio2DoomConfig.h file for some adjustable settings relating to debugging.

## Debugging
Get a root shell in the head unit and run the following command to see a live view of logs from DAudio2Doom:
```
logcat -s DAudio2Doom:v
```