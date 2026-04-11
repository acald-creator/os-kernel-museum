1. Build GNU binutils/gcc as i?68-elf/x86_64-elf targets
2. Create custom kernel and custom libc as sysroot headers
3. Create a custom kernel in c, and develop an api using Terra, while creating a custom libc in mixture of C/Lua
4. Configure GNU binutils/gcc to os specific targets
5. Compile and build os specific GNU binutils/gcc with previously created sysroot headers
6. Cross-compile the toolchain and then build Clang/LLVM without GNU libgcc (possibly)
7. Create userland in Lua
8. First desktop environment is Awesome WM which is in Lua

# ANSI C Library header files
<assert.h>
<complex.h>
<ctype.h>
<errno.h>
<fenv.h>
<float.h>
<inttypes.h>
<iso646.h>
<limits.h>
<locale.h>
<math.h>
<setjmp.h>
<signal.h>
<stdarg.h>
<stdbool.h>
<stdint.h>
<stddef.h>
<stdio.h>
<stdlib.h>
<string.h>
<tgmath.h>
<time.h>
<wchar.h>
<wctype.h>

# POSIX standard library

# Custom C library

Hosted environment is meant for user-space programming
Freestanding environment is meant for kernel programming

The __STDC__HOSTED__ macross expands to 1 on hosted implementations or 0 on freestanding implementations.

Freestanding headers
<float.h>
<iso646.h>
<limits.h>
<stdalign.h>
<stdarg.h>
<stdbool.h>
<stddef.h>
<stdint.h>
<stdnoreturn.h>

# Compile freestanding compiler (GNU binutils/gcc) (standard headers needed in first pass)
## GNU GCC `libcc` standard headers

<sys/types.h>
<errno.h>
<stdlib.h>
    abort()
    free()
    malloc()
<stdio.h>
    FILE
    stderr
    fflush()
    fprintf()
<string.h>
    size_t
    memcpy
    memset
    strlen
<time.h>
<unistd.h>

## GNU GCC `all-target-libgcc` standard headers

<sys/types.h>
    pid_t
<stdlib.h>
    atexit()
    atoi()
    getenv()
<stdio.h>
    size_t
    SEEK_SET
    fclose()
    fopen()
    fread()
    fseek()
    ftell()
    fwrite()
    setbuf()
    vprintf()
<string.h>
    strcpy()
<unistd.h>
    pid_t
    fork()
    execv()
    execve()
    execvp()

# Compile freestanding compiler (GNU binutils/gcc)

```bash
sudo apt install build-essential \
    bison \
    flex \
    libgmp3-dev \
    libmpc-dev \
    libmpfr-dev \
    texinfo \
    libisl-dev
```

export PREFIX="/mnt/kairos/toolchain"
export TARGET=x86_64-kairos-elf
export PATH="$PREFIX/bin:$PATH"
export HOST=x86_64-cross-linux-gnu
export SYSROOT=/mnt/sysroot

cd /mnt/kairos/sources/pkgs
mkdir naked-binutils && cd naked-binutils
../binutils-gdb/configure \
    --target=$TARGET \
    --prefix="$PREFIX" \
    --with-sysroot \
    --disable-nls \
    --disable-werror

make -j$(nproc) && make install

cd /mnt/kairos/sources/pkgs
mkdir naked-gcc && cd naked-gcc
../gcc/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers

make all-gcc -j$(nproc)
make all-target-libgcc -j$(nproc)
make install-gcc -j$(nproc)
make install-target-libgcc -j$(nproc)

# Create a custom libc, then create os-specific toolchains
cd /mnt/kairos/sources/pkgs
mkdir os-binutils && cd os-binutils
../binutils-gdb/configure \
    --target=$TARGET \
    --prefix="/mnt/kairos/toolchain" \
    --with-sysroot=/mnt/sysroot \
    --disable-nls \
    --disable-werror \
    --disable-gdb \
    --disable-static \
    --disable-multilib \
    --enable-plugins \
    --enable-gold \
    --disable-sim \
    --disable-libdecnumber \
    --disable-readline

make -j$(nproc) && make install

cd /mnt/kairos/sources/pkgs
mkdir os-gcc && cd os-gcc
CFLAGS='-g0 -O0' CXXFLAGS=$CFLAGS ../gcc/configure --target=$TARGET \
    --prefix="/mnt/kairos/toolchain" \
    --with-sysroot=/mnt/sysroot \
    --enable-languages=c \
    --disable-nls \
    --disable-libvtv \
    --disable-libitm \
    --disable-libssp \
    --disable-shared \
    --disable-libgomp \
    --disable-threads \
    --disable-multilib \
    --disable-libatomic \
    --disable-libstdcxx \
    --disable-libquadmath \
    --disable-libsanitizer \
    --disable-decimal-float \
    --enable-clocale=generic \
    --disable-gcov

--disable-gcov warned sys/mman.h is not found

make all-gcc all-target-libgcc -j$(nproc)
make install-gcc install-target-libgcc -j$(nproc)

# Fine-tune custom c library

cd /mnt/kairos/sources/pkgs
mkdir fine-tune-gcc && cd fine-tune-gcc
AR=/mnt/kairos/toolchain/bin/x86_64-kairos-elf-ar \
    LDFLAGS="-Wl,-rpath,/mnt/kairos/toolchain/lib" \
    ../gcc/configure --target=x86_64-kairos-elf \
        --prefix=/mnt/kairos/toolchain/ \
        --with-sysroot=/mnt/sysroot \
        --enable-languages=c,c++ \
        --enable-libstdcxx-time \
        --enable-clocale=generic \
        --enable-fully-dynamic-string \
        --disable-hosted-libstdcxx \
        --disable-libsanitizer \
        --disable-lto-plugin \
        --disable-multilib \
        --disable-symvers \
        --disable-libsspc \
        --disable-libssp \
        --disable-static \
        --disable-nls \
        --disable-shared \
        --enable-thread=single

--enable-threads=posix requires pthread.h
--enable-shared was looking for dlopen()

make AS_FOR_TARGET=/mnt/kairos/toolchain/bin/x86_64-kairos-elf-as LD_FOR_TARGET=/mnt/kairos/toolchain/bin/x86_64-kairos-elf-ld all-gcc all-target-libgcc -j$(nproc)
make install-gcc install-target-libgcc

libstd++ still errors out

CC=x86_64-kairos-elf-gcc \
CXX=x86_64-kairos-elf-g++ \
AR=x86_64-kairos-elf-ar \
AS=x86_64-kairos-elf-as \
RANLIB=x86_64-kairos-elf-ranlib \
LD=x86_64-kairos-elf-ld \
STRIP=x86_64-kairos-elf-strip \
LDFLAGS="-Wl,-rpath,/mnt/kairos/toolchain/lib" \
../configure --disable-bzlib \
    --disable-libseccomp \
    --disable-xzlib \
    --disable-zlib \
    --prefix=/mnt/sysroot/usr \
    --host=x86_64-kairos-elf \
    --build=x86_64-kairos-elf