@echo off

set RAYINC=C:/dev/libraries/raylib-5.5_win64_mingw-w64/include
set RAYLIB=C:/dev/libraries/raylib-5.5_win64_mingw-w64/lib

set before_flags= -O3 -ggdb3 -I"%RAYINC%"
set after_flags=-L"%RAYLIB%" -l:libraylib.a -lgdi32 -lwinmm

set after_flags_nocmd=-L"%RAYLIB%" -l:libraylib.a -lgdi32 -lwinmm -Wl,--subsystem,windows

set opengl_mightbenecessary_atsomepoint=-L"%RAYLIB%" -l:libraylib.a -lgdi32 -lwinmm -lopengl32 -Wl,--subsystem,windows

@echo on
g++ %before_flags% -o main.exe main.cpp %after_flags_nocmd%

.\main.exe
