1. Compile naked binutils

```bash
../binutils-gdb/configure --target=x86_64-kairos-elf --prefix=/mnt/gnu-toolchain --with-sysroot=/mnt/kairos-system/ --disable-werror
make $(nproc) && make install
```

Compile gcc
```bash
AR=/mnt/kairos/toolchain/bin/x86_64-kairos-elf-ar LDFLAGS="-Wl,-rpath,/mnt/kairos/toolchain/lib" ../gcc/configure --target=x86_64-kairos-elf --prefix=/mnt/gnu-toolchain --with-sysroot=/mnt/kairos-system/ --enable-languages=c,c++
make AS_FOR_TARGET=/mnt/gnu-toolchain/bin/x86_64-kairos-elf-as LD_FOR_TARGET=/mnt/gnu-toolchain/bin/x86_64-kairos-elf-ld all-gcc all-target-libgcc $(nproc)
make install-gcc install-target-libgcc $(nproc)
```

Compile llvm to get lld linker as a replacement

```bash
git clone --depth=1 https://github.com/llvm/llvm-project
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CROSSCOMPILE=True \
    -DLLVM_ENABLE_PROJECTS=lld \
    -DCMAKE_INSTALL_PREFIX=/mnt/kairos-system/usr/local \
    -DLLVM_TARGET_ARCH=X86 \
    -DLLVM_TARGETS_TO_BUILD=X86 \
    -DCMAKE_C_COMPILER=/mnt/gnu-toolchain/bin/x86_64-kairos-elf-gcc \
    -DCMAKE_CXX_COMPILER=/mnt/gnu-toolchain/bin/x86_64-kairos-elf-g++ \
    -DCMAKE_CXX_FLAGS="--sysroot=/mnt/kairos-system" \
    ../llvm

    -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind" \
    ../llvm