FROM continuumio/miniconda3:latest

# install apt dependencies
RUN apt-get -qq update \
 && apt-get -y upgrade \
 && apt-get -y install \
      cmake \
      clang-6.0 \
 && apt-get -qq autoremove \
 && apt-get autoclean \
 && rm -rf /var/lib/apt/lists/*
 
# show versions
RUN cmake --version \
 && clang --version
