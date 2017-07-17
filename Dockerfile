FROM debian:stretch-slim

WORKDIR /app

RUN mkdir /test_bin vendor

RUN apt-get update
RUN apt-get install -y g++ wget libboost-all-dev libboost-tools-dev &&\
  wget https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp &&\
  bcp any vendor/ --boost=/usr/include
