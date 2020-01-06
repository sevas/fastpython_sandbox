@echo off
pushd .

set SOURCE_DIR=%~dp0\..
cd %SOURCE_DIR%
md _conan
cd _conan
conan install ..

cd ..
md _build_vs2015
cd _build_vs2015
cmake .. -G "Visual Studio 14 2015 Win64"




popd

pause