#!/usr/bin/env bash

rm -rf /mnt/kairos-chroot
mkdir -p /mnt/kairos-chroot
cp -r libc/include /mnt/kairos-chroot/usr
rm *.o

/mnt/kairos/hosted/bin/x86_64-kairos-elf-gcc -std=gnu99 -fpic \
  -shared \
  -mno-red-zone \
  --sysroot=/mnt/kairos-chroot -c crt/x86_64/crt*.s

mkdir -p /mnt/kairos-chroot/lib
mv *.o /mnt/kairos-chroot/lib

rm *.o
/mnt/kairos/hosted/bin/x86_64-kairos-elf-gcc -std=gnu99 -fpic \
  -shared \
  -mno-red-zone \
  --sysroot=/mnt/kairos-chroot -c src/*/*.c -I libc/include

mkdir -p /mnt/kairos-chroot/lib
/mnt/kairos/hosted/bin/x86_64-kairos-elf-ar crs /mnt/kairos-chroot/lib/libc.a *.o
rm *.o