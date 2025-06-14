@echo off

pushd "%~dp0\.."

rd /S /Q release
mkdir release

popd
