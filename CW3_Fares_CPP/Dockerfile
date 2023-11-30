FROM alpine as cw3_fares_cpp

RUN apk add build-base
WORKDIR /app
COPY . .

RUN gcc sort.cpp main.cpp -lstdc++ -std=c++17 -Wall -Wpedantic -Wextra -o main

FROM alpine:latest

COPY --from=cw3_fares_cpp /app /app
WORKDIR /app
