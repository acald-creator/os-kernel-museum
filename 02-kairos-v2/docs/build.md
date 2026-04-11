```bash
export BUILD_TARGET="x86_64-elf"
export BUILD_PREFIX="${HOME}/opt/cross/${BUILD_TARGET}-toolchain"
export HOST="x86_64-pc-linux-gnu"
export PATH="${BUILD_PREFIX}/bin:${PATH}"

concurrency=8

local_lib_dir="/usr/local"

../binutils/configure --target="${BUILD_TARGET}" \
    --prefix="${BUILD_PREFIX}" \
    --host="${HOST}" \
    --disable-nls \
    --disable-multilib \
    --disable-shared \
    --with-sysroot \
    --disable-werror \
    --disable-gdb \
    --disable-libdecnumber \
    --disable-readline \
    --disable-sim

make -j$(nproc) && make install

../gcc/configure --target="${BUILD_TARGET}" \
    --prefix="${BUILD_PREFIX}" \
    --host="${HOST}" \
    --disable-nls \
    --disable-multilib \
    --disable-shared \
    --without-headers \
    --enable-languages="c"

make all-gcc -j$(nproc) && make all-target-libgcc -j$(nproc) && make install-gcc & make install-target-libgcc
```

```bash
----------------------------------------------------------------------
Libraries have been installed in:
   /home/auxyria/opt/cross/x86_64-elf-toolchain/libexec/gcc/x86_64-elf/12.0.0

If you ever happen to want to link against installed libraries
in a given directory, LIBDIR, you must either use libtool, and
specify the full pathname of the library, or use the `-LLIBDIR'
flag during linking and do at least one of the following:
   - add LIBDIR to the `LD_LIBRARY_PATH' environment variable
     during execution
   - add LIBDIR to the `LD_RUN_PATH' environment variable
     during linking
   - use the `-Wl,-rpath -Wl,LIBDIR' linker flag
   - have your system administrator add LIBDIR to `/etc/ld.so.conf'

See any operating system documentation about shared libraries for
more information, such as the ld(1) and ld.so(8) manual pages.
----------------------------------------------------------------------
```
---

```bash
export SYSROOT="${HOME}/opt/sysroot"
export SYSROOT_TARGET="x86_64-kairos-elf"
export SYSROOT_PREFIX="${HOME}/opt/sysroot/usr"
export PATH="${SYSROOT_PREFIX}/bin:${PATH}"
export HOST="x86_64-pc-linux-gnu"

../binutils/configure --target="${SYSROOT_TARGET}" \
    --prefix="${SYSROOT_PREFIX}" \
    --host="${HOST}" \
    --disable-nls \
    --disable-multilib \
    --disable-shared \
    --with-sysroot="${SYSROOT}" \
    --disable-werror \
    --enable-gold \
    --enable-plugins \
    --enable-default=gold \
    --with-pkgversion="GNU Binutils for Kairos OS"

make -j$(nproc) && make install

LD="/home/auxyria/opt/sysroot/usr/bin/x86_64-kairos-elf-ld.gold" \
  AS="/home/auxyria/opt/sysroot/usr/bin/x86_64-kairos-elf-as" \
  LDFLAGS="-Wl,-rpath,/home/auxyria/opt/cross/x86_64-kairos-elf/lib,-rpath,/home/auxyria/opt/sysroot/usr/lib,-rpath,/home/auxyria/opt/sysroot/lib,-rpath,/home/auxyria/opt/cross/x86_64-elf-toolchain/libexec/gcc/x86_64-elf/12.0.0" ../gcc/configure --target="${SYSROOT_TARGET}" \
    --prefix="${SYSROOT_PREFIX}" \
    --host="${HOST}" \
    --with-sysroot="${SYSROOT}" \
    --disable-nls \
    --disable-multilib \
    --disable-shared \
    --enable-static \
    --enable-languages="c" \
    --enable-threads=single \
    --disable-libada \
    --disable-libsanitizer \
    --disable-libssp \
    --disable-libquadmath \
    --disable-libquadmathsupport \
    --disable-libgomp \
    --disable-libstdcxx-verbose \
    --disable-hosted-libstdcxx \
    --disable-libmudflap \
    --enable-initfini-array \
    --enable-decimal-float=no \
    --disable-libvtv \
    --disable-libstdcxx \
    --disable-libatomic \
    --disable-fixed-point \
    --enable-gold

make all-gcc -j$(nproc) && make install-gcc
make all-target-libgcc -j$(nproc) && make install-target-libgcc