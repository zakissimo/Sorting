#!/usr/bin/env bash

RANDOMRANGE=$(shuf -i 1-3000)

make -sC ./cpp/
./cpp/main $RANDOMRANGE

cd ./rust/ && cargo -q build --release
./target/release/merge_insertion_sort $RANDOMRANGE
