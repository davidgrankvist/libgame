@echo off

pushd "%~dp0\.."

for %%f in (.\examples\*.c) do (
    echo Building example %%f
    call .\scripts\example_build_win32 %%f
)

popd
