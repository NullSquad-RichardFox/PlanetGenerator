@echo off

pushd %~dp0\..\
call Programs\Premake\premake5.exe --file=PlanetGenerator.lua gmake2
call Programs\Premake\premake5.exe --file=PlanetGenerator.lua vscode
popd
PAUSE