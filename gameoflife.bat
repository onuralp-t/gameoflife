@echo off

set RAYINC=C:/dev/libraries/raylib-5.5_win64_mingw-w64/include
set RAYLIB=C:/dev/libraries/raylib-5.5_win64_mingw-w64/lib

set before_flags=-static -O3 -ggdb3 -I"%RAYINC%"
set after_flags=-L"%RAYLIB%" -l:libraylib.a -lgdi32 -lwinmm

set after_flags_nocmd=-L"%RAYLIB%" -l:libraylib.a -lgdi32 -lwinmm -Wl,--subsystem,windows

set opengl_mightbenecessary_atsomepoint=-L"%RAYLIB%" -l:libraylib.a -lgdi32 -lwinmm -lopengl32 -Wl,--subsystem,windows

@echo on
g++ %before_flags% gameoflife.cpp assets/icon.res -o gameoflife.exe %after_flags%

.\gameoflife.exe
