FROM ubuntu:17.10
ENV DEBIAN_FRONTEND noninteractive
LABEL maintainer "Noritaka Horio <holy.shared.design@gmail.com>"
RUN apt-get update && apt-get install -y cmake
RUN mkdir /var/tmp/clang-program
WORKDIR /var/tmp/clang-program
