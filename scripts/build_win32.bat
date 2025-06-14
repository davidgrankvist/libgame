@echo off

pushd "%~dp0\.."

mkdir bin > NUL 2>&1

set help_text=Usage: .\build_win32.bat target
set target=%1

if not "%target%" == "debug" (
    if not "%target%" == "release" (
        echo Unknown build target "%target%". Please set either debug or release.
        echo %help_text%
        exit 1
    )
)

echo Building for target win32 (%target%)

set common_src=src\platform\win32.c src\common\*.c
set common_flags=^
    /DLIBGAME_OPENGL_RENDER_330 ^
    /LD ^
    /Fe: bin\libgame.dll ^
    /Fo: bin\ ^
    /Fd: bin\ ^
    /I"src\include" ^
    /I"src\common" ^
    /I"vendor\include" ^
    /link ^
        user32.lib ^
        winmm.lib ^
        gdi32.lib ^
        opengl32.lib ^
    /nologo

if "%target%" == "debug" (
    cl %common_src% /Zi /Od %common_flags%
) else (
    cl %common_src% /O1 %common_flags%
)

popd
