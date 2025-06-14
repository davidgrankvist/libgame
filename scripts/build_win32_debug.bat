@echo off

pushd "%~dp0\.."

mkdir bin > NUL 2>&1

cl src\platform\win32.c src\common\*.c ^
    /DLIBGAME_OPENGL_RENDER_330 ^
    /LD ^
    /Fe: bin\libgame.dll ^
    /Fo: bin\ ^
    /Fd: bin\ ^
    /Zi ^
    /I"src\include" ^
    /I"src\common" ^
    /I"vendor\include" ^
    /link ^
        user32.lib ^
        winmm.lib ^
        gdi32.lib ^
        opengl32.lib ^
    /nologo

popd
