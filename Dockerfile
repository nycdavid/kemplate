FROM debian:stretch-slim

WORKDIR /usr/src/googletest

RUN apt-get update &&\
  apt-get install -y libgtest-dev cmake g++ &&\
  cmake CMakeLists.txt &&\
  make

WORKDIR /app
