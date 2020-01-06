#!/usr/bin/env bash

pushd .
cd ..

mkdir _conan
cd _conan || exit
conan install .. -s compiler=clang -s compiler.version="6.0" -s compiler.libcxx=libstdc++11
cd ..

export CC=clang-6.0
export CXX=clang++-6.0

mkdir _build_clang6
cd _build_clang6 || exit
cmake .. -G "Unix Makefiles"

make -j
