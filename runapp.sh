#!/bin/bash

g++ timer.cpp -o timer_app -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./timer_app
