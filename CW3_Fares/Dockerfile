FROM alpine as proj

RUN apk add build-base
WORKDIR /app
COPY . .

RUN gcc -o task1 task1.c -std=c17 -Wall -Wpedantic -Wextra && \
    gcc -o task2 task2.c -std=c17 -Wall -Wpedantic -Wextra && \
    gcc -o task3 task3.c -std=c17 -Wall -Wpedantic -Wextra

FROM alpine:latest

COPY --from=proj /app/task1 /app/task1
WORKDIR /app
