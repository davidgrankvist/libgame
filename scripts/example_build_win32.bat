@echo off

pushd "%~dp0\.."

mkdir bin > NUL 2>&1

set example=%1
set help_text=Usage: .\example_build_and_run_win32.bat example rebuild
set rebuild_lib_option=%2

if not exist %example% (
    echo Unable to find example %example%
    echo %help_text%
    exit 1
)

echo Building example %example%

if "%rebuild_lib_option%" == "rebuild" (
    echo The rebuild option was set. Rebuilding libgame.
    call .\scripts\clean.bat
    call .\scripts\build_win32.bat debug dynamic
)

if /I "%example:~-2%"==".c" (
    set build_src=%example%
) else (
    set build_src=%example%\*.c
)

cl %build_src% ^
    /Fe: bin\example.exe ^
    /Fo: bin\ ^
    /Fd: bin\ ^
    /Zi ^
    /I"src\include" ^
    /I"src" ^
    /link ^
        /LIBPATH:bin ^
        /LIBPATH:"libgame\bin" ^
        libgamedll.lib ^
        /SUBSYSTEM:WINDOWS ^
    /nologo

popd
