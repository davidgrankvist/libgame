@echo off

pushd "%~dp0\.."

mkdir bin > NUL 2>&1

set help_text=Usage: .\build_win32.bat target
set target=%1
set link_type=%2

if not "%target%" == "debug" (
    if not "%target%" == "release" (
        echo Unknown build target "%target%". Please set either debug or release.
        echo %help_text%
        exit 1
    )
)

if not "%link_type%" == "static" (
    if not "%link_type%" == "dynamic" (
        echo Unknown link type "%link_type%". Please set either static or dynamic.
        echo %help_text%
        exit 1
    )
)

echo Building target win32
echo Build type: %target%
echo Link type: %link_type%

set common_src=src\platform\win32.c src\common\*.c
set common_flags_dynamic=^
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
        /implib:bin\libgamedll.lib ^
    /nologo

set common_flags_static=^
    /c ^
    /DLIBGAME_STATIC_LINK ^
    /DLIBGAME_OPENGL_RENDER_330 ^
    /Fo: bin\ ^
    /Fd: bin\libgame.pdb ^
    /I"src\include" ^
    /I"src\common" ^
    /I"vendor\include" ^
    /nologo

if "%link_type%" == "static" (
    set common_flags=%common_flags_static%
) else (
    set common_flags=%common_flags_dynamic%
)

if "%target%" == "debug" (
    cl %common_src% /Zi /Od %common_flags%
) else (
    cl %common_src% /O1 %common_flags%
)

if "%link_type%" == "static" (
    lib .\bin\*.obj /out:bin\libgame.lib
)

popd
