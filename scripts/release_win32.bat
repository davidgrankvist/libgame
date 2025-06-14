@echo off

set version=%1
set help_text=Usage: .\release_win32.bat version

if "%version%" == "" (
    echo Please provide a version.
    echo %help_text%
    exit 1
)

pushd "%~dp0\.."

set target=win64_msvc
set release_subdir=libgame-%version%_%target%
set release_dir=release\%release_subdir%

echo Creating release artifacts for win32
echo Artifact name: %release_subdir%
echo Release directory: %cd%\%release_dir%

mkdir release > NUL 2>&1
mkdir %release_dir% > NUL 2>&1
mkdir %release_dir%\include > NUL 2>&1
mkdir %release_dir%\lib > NUL 2>&1

echo Building dynamic library
call .\scripts\clean.bat
call .\scripts\build_win32.bat release

echo Copying files
copy .\README.md %release_dir%\
copy .\LICENSE %release_dir%\
copy .\src\include\* %release_dir%\include\
copy .\bin\libgame.dll %release_dir%\lib\
copy .\bin\libgame.lib %release_dir%\lib\libgame.lib

echo Creating archive %release_dir%.zip
powershell -Command "Compress-Archive -Path %release_dir% -DestinationPath %release_dir%.zip"

popd
