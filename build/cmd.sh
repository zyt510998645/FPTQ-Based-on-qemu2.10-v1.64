#!/bin/sh
#../configure --target-list=arm-linux-user --enable-tcg-interpreter
../configure --target-list=x86_64-linux-user --enable-tcg-interpreter
make
make install
