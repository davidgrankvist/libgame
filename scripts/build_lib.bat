@echo off

mkdir bin > NUL 2>&1

cl src\lib\platform\win32.c src\lib\common\*.c ^
    /DLIBGAME_OPENGL_RENDER_330 ^
    /LD ^
    /Fe: bin\libgame.dll ^
    /Fo: bin\ ^
    /Fd: bin\ ^
    /Zi ^
    /I"src\lib\include" ^
    /I"src\lib\common" ^
    /I"vendor\include" ^
    /link ^
        user32.lib ^
        winmm.lib ^
        gdi32.lib ^
        opengl32.lib ^
    /nologo
