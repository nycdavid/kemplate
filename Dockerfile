FROM debian:stretch-slim

WORKDIR /app

RUN apt-get update &&\
  apt-get install -y g++ wget &&\
  wget https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp
