@echo off

pushd "%~dp0\.."

set example=%1

call .\scripts\example_build_win32.bat %*

.\bin\example.exe

popd
