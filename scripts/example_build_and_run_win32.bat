@echo off

pushd "%~dp0\.."

call .\scripts\example_build_win32.bat %*

.\bin\example.exe

popd
