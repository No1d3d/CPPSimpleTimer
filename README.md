# CPPSimpleTimer
A simple CPP timer app for your simple timing needs.

It is written using raylib and was tested on Linux (Ubuntu 22.04).


#INSTALLATION

To install raylib on your system, follow these steps (Steps taken from here - https://community.gamedev.tv/t/raylib-on-linux/212199):

1 - execute these commands in the terminal

```bash
sudo apt install build-essential git
sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
```

2 - Change to your home directory and execute these commands

```bash
git clone https://github.com/raysan5/raylib.git raylib
cd raylib/src/
make PLATFORM=PLATFORM_DESKTOP
sudo make install
```

#WHAT IT CAN DO

This timer acts both as a timer and as a clock. It outputs current system time in real life. To use the actual timer, set the timer by pressing "Start timer" button. To make a time mark, press the "Tap timer" button. Last five time marks are output on the right side of the window for you to look at.

#RUN

To run the app, use runapp.sh bash script.

```bash
sh runapp.sh
```

#TODO
I want to make it so that the timer measurements could be saved in a file when the timer is fully stopped.