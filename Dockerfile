FROM debian:latest

RUN apt-get update && apt-get install -y -t buster binutils \
  git gcc g++ make cmake linux-headers
  
ADD . /service

WORKDIR /service/build

RUN cmake .. -DBOOST_ROOT=/service/include
RUN make

EXPOSE 8000 8000

ENTRYPOINT ["./src"]