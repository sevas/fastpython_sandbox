#!/usr/bin/env bash

pushd .
cd ..

mkdir _conan
cd _conan || exit
conan install ..
cd ..

export CC=clang
export CXX=clang++

mkdir _build_clang
cd _build_clang || exit
cmake .. -G "Unix Makefiles"

make -j
