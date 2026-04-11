##-----------------------------------------------------------
# Compile naked gnu binutils and gnu gcc toolchain
# Set envs for freestanding toolchain to build custom kernel
##-----------------------------------------------------------
export PREFIX=/mnt/kairos/free-toolchain
export KLFS_TARGET=x86_64-kairos-elf
export PATH="$PREFIX/bin:$PATH"
--
export KARGS="--prefix=${PREFIX} "
export KARGS+="--target=${KLFS_TARGET} "
export KARGS+="--with-sysroot "
export KARGS+="--disable-werror "
export KARGS+="--disable-nls "
export KARGS+="--disable-werror "
export KARGS+="--disable-gdb "
export KARGS+="--disable-libdecnumber "
export KARGS+="--disable-readline "
export KARGS+="--disable-sim "
# export KARGS+="--with-sysroot=/mnt/kairos-system/freestanding-toolchain/${KLFS_TARGET} "
--
mkdir naked-binutils && cd naked-binutils
../binutils-gdb/configure ${KARGS}

make -j$(nproc) && make install && unset KARGS

##-----------------------------------------------------------
which -- $KLFS_TARGET-as || echo $KLFS_TARGET-as is not in the PATH
--
cd .. && mkdir naked-gcc && cd naked-gcc
--
export KARGS="--prefix=${PREFIX} "
export KARGS+="--target=${KLFS_TARGET} "
export KARGS+="--disable-nls "
export KARGS+="--enable-languages=c,c++ "
export KARGS+="--without-headers "
--
AS_FOR_TARGET=${PREFIX}/bin/x86_64-kairos-elf-as \
    LD_AS_TARGET=${PREFIX}/bin/x86_64-kairos-elf-ld ../gcc/configure ${KARGS}
make all-gcc -j$(nproc) && make all-target-libgcc -j$(nproc)
make install-gcc & make install-target-libgcc

##----------------------------------------------------------------
# Configure custom libc and fine-tune as needed
# Compile hosted gnu binutils and gnu gcc toolchain for userspace
# After building the custom c library, it seems it was sufficient
# enough to build the hosted compiler with the build target
##----------------------------------------------------------------
export SYSROOT_PREFIX=/mnt/kairos/hosted
export SYSROOT=/mnt/kairos-syroot
--
export KARGS="--prefix=${SYSROOT_PREFIX} "
export KARGS+="--target=${KLFS_TARGET} "
export KARGS+="--build=${KLFS_TARGET} "
export KARGS+="--with-sysroot=${SYSROOT} "
export KARGS+="--disable-nls "
export KARGS+="--enable-shared "
export KARGS+="--enable-static "
export KARGS+="--enable-gold "
export KARGS+="--enable-default=gold "
export KARGS+="--enable-plugins "
export KARGS+="--disable-werror "
--
mkdir hosted-binutils && cd hosted-binutils
../binutils-gdb/configure ${KARGS} && make -j$(nproc) && make install && unset KARGS

##-----------------------------------------------------------------
cd .. && mkdir hosted-gcc && cd hosted-gcc
--
export KARGS="--prefix=${SYSROOT_PREFIX} "
export KARGS+="--target=${KLFS_TARGET} "
export KARGS+="--build=${KLFS_TARGET} "
export KARGS+="--with-sysroot=${SYSROOT} "
export KARGS+="--enable-languages=c "
export KARGS+="--disable-nls "
export KARGS+="--enable-shared "
export KARGS+="--enable-static "
export KARGS+="--disable-multilib "
export KARGS+="--disable-threads "
export KARGS+="--disable-libstdcxx-verbose "
export KARGS+="--disable-libquadmath "
export KARGS+="--disable-libssp "
export KARGS+="--disable-bootstrap "
export KARGS+="--disable-hosted-libstdcxx "
export KARGS+="--disable-libgomp "
export KARGS+="--disable-libmudflap "
export KARGS+="--enable-gold "
--
LD=${SYSROOT_PREFIX}/bin/ld.gold AR=${SYSROOT_PREFIX}/bin/ar LDFLAGS="-Wl,-rpath,/mnt/kairos-sysroot/lib" ../gcc/configure ${KARGS}
make all-gcc -j$(nproc) && make all-target-libgcc -j$(nproc)
make install-gcc & make install-target-libgcc
--
make all-target-libstdc++-v3
make install-target-libstdc++-v3

compiling libstdc++-v3 is still failing

##--------------------------------------------------------------------
# Compile Clang/LLVM

cmake -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_ENABLE_PROJECTS="clang;compiler-rt" \
    -DLLVM_ENABLE_ZLIB=OFF \
    -DLLVM_ENABLE_LIBXML2=OFF \
    -DLLVM_ENABLE_THREADS=OFF \
    -DCLANG_ENABLE_ARCMT=OFF \
    -DLLVM_ENABLE_ASSERTIONS=ON \
    -DCMAKE_INSTALL_PREFIX=/mnt/kairos/llvmtools \
    -DCMAKE_CXX_STANDARD=11 \
    -DLLVM_TARGET_ARCH=X86 \
    -DLLVM_TARGETS_TO_BUILD=X86 \
    -DCMAKE_CXX_FLAGS="--sysroot=/mnt/kairos-chroot" \
    -DCMAKE_BUILD_WITH_INSTALL_RPATH=ON \
    -DLLVM_USE_LINKER=gold \
    -DLLVM_INCLUDE_TESTS=OFF \
    -DLLVM_INCLUDE_EXAMPLES=OFF \
    -DLLVM_INCLUDE_DOCS=OFF \
    -DLLVM_ENABLE_OCAMLDOC=OFF \
    ../llvm

    -DLLVM_ENABLE_RUNTIMES="libunwind" \
    -DLLVM_DEFAULT_TARGET_TRIPLE=x86_64-unknown-unknown-elf \
    -DCMAKE_CXX_FLAGS="-fms-extensions" \
/mnt/kairos/hosted/bin/x86_64-kairos-elf-gcc -std=gnu99 -fpic -shared -mno-red-zone -I/usr/local/terra/include/terra -L/usr/local/terra/lib -lterra -ldl --sysroot=/mnt/kairos-chroot -c kairos_libc/libc/src/fs/fs.c  -I kairos_libc/libc/src/fs -O2 -Wall -fPIC -W -Waggregate-return -Wcast-align -Wmissing-prototypes -Wnested-externs -Wshadow -Wwrite-strings -pedantic -o fs.so
    

#    -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind" \

# Cross-compiling clang/llvm with the custom c library required certain features to be off
# #include <unicode/ucnv.h> requires LLVM_ENABLE_LIBXML2 to be off
# #include <zlib.h> requires LLVM_ENABLE_ZLIB to be off
# There were errors in completing the compilation in libcxx/libcxxabi looking for pthreads which requires LLVM_ENABLE_THREADS to be off