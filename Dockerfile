FROM ubuntu:xenial

RUN apt-get update
RUN apt-get install -y gcc
RUN apt-get install -y g++
RUN apt-get install -y build-essential libtcmalloc-minimal4 && ln -s /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libtcmalloc_minimal.so
RUN apt-get install -y libboost-all-dev
RUN apt-get install -y libcurl4-gnutls-dev
RUN apt-get install -y cmake


ADD . /app

WORKDIR /app/build

RUN cmake ..
RUN make

EXPOSE 8080/tcp
WORKDIR /app
ENTRYPOINT ["./build/src/example"]