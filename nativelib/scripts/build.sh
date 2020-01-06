#!/usr/bin/env bash

pushd .
cd ..

mkdir _conan
cd _conan || exit
conan install ..
cd ..

export CC=gcc
export CXX=g++

mkdir _build_clang
cd _build_clang || exit
cmake .. -G "Unix Makefiles"

make -j
