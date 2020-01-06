#!/usr/bin/env bash

pushd .
cd ..

mkdir _conan
cd _conan || exit
conan install .. -s compiler=clang -s compiler.version=8 -s compiler.libcxx=libstdc++11
cd ..

export CC=clang-8
export CXX=clang++-8

mkdir _build_clang8
cd _build_clang8 || exit
cmake .. -G "Unix Makefiles"

make -j
