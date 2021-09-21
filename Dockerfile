FROM lganzzzo/alpine-cmake:latest

RUN apk add linux-headers

ADD . /service

WORKDIR /service/build

RUN cmake .. -DBOOST_ROOT=/service/include
RUN make

EXPOSE 8000 8000

ENTRYPOINT ["./src"]