#ifndef CONSTANTS_H
#define CONSTANTS_H

#ifndef RAYLIB_H
#include "raylib.h"
#endif

#ifndef comptime
#define comptime static constexpr
#endif

comptime int GRID_LEN = 50;
comptime float CELL_WIDTH = 15.0f;

comptime int TOP_REGION_HEIGHT = 100;
comptime int WINDOW_PADDING = 20;

comptime Color COLOR_ON = PURPLE;
comptime Color COLOR_OFF = DARKPURPLE;
comptime Color COLOR_BORDER = BLACK;
comptime Color COLOR_BACKGROUND = LIGHTGRAY;

comptime int WINDOW_WIDTH = GRID_LEN * CELL_WIDTH + WINDOW_PADDING;
comptime int WINDOW_HEIGHT = GRID_LEN * CELL_WIDTH + WINDOW_PADDING + TOP_REGION_HEIGHT;

comptime int GRID_SIZE = GRID_LEN * GRID_LEN;
#endif