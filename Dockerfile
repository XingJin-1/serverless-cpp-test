FROM ubuntu:xenial

ENV CCACHE_DIR=/ccache

RUN apt-get update
RUN apt-get install -y gcc
RUN apt-get install -y g++
RUN apt-get install -y build-essential libtcmalloc-minimal4 && ln -s /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libtcmalloc_minimal.so
RUN apt-get install -y libboost-all-dev
RUN apt-get install -y libcurl4-gnutls-dev
RUN apt-get install -y cmake \ 
					   ccache

RUN apt-get update && apt-get install -y curl ca-certificates
RUN curl -L http://crl.infineon.com/RootCA2/RootCA2.crt -o /usr/local/share/ca-certificates/RootCA2.crt && \
    curl -L http://crl.infineon.com/SSLCA3/SSLCA3.crt -o /usr/local/share/ca-certificates/SSLCA3.crt && \
    curl -L http://crl.infineon.com/RootCA3/RootCA3.crt -o /usr/local/share/ca-certificates/RootCA3.crt && \
    curl -L http://crl.infineon.com/SSLCA4/SSLCA4.crt -o /usr/local/share/ca-certificates/SSLCA4.crt && \
    update-ca-certificates

RUN for p in gcc g++ cc c++; do ln -vs /usr/bin/ccache /usr/local/bin/$p;  done

RUN --mount=type=cache,target=/ccache/ ccache -s

ADD . /app

WORKDIR /app/build

RUN cmake ..
RUN make

EXPOSE 8080/tcp
WORKDIR /app
ENTRYPOINT ["./build/src/example"]