#!/bin/bash

KERNELDIR=$HOME/dev/kernel-powerpc \
ARCH=powerpc \
CROSS_COMPILE=powerpc64le-linux-gnu- \
make
