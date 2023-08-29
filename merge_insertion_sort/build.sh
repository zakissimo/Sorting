#!/usr/bin/env bash

RANDOMRANGE=$(shuf -i 0-3000);

make -C ./cpp/;
./cpp/main $RANDOMRANGE;
