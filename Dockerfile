FROM debian:stretch-slim

WORKDIR /usr/src/gtest

RUN apt-get update && \
  apt-get install -y libgtest-dev cmake

WORKDIR /app
