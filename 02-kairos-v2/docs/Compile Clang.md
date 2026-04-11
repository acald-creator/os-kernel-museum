sudo snap install cmake --classic
sudo apt install build-essential ccache ninja-build

git clone --depth=1 https://github.com/llvm/llvm-project.git

mkdir llvm-config-build && llvm-config-build
cmake -DLLVM_TARGETS_TO_BUILD=Native -DCMAKE_INSTALL_PREFIX=/mnt/toolchain ../llvm

cd llvm-project && mkdir build
cmake -G Ninja -S runtimes -B build \
    -DLLVM_ENABLE_RUNTIMES="libunwind" \
    -DCMAKE_INSTALL_PREFIX=/mnt/toolchain \
    -DCMAKE_BUILD_WITH_INSTALL_RPATH=ON

ninja -C build/ unwind
ninja -C build/ check-unwind
sudo ninja -C build/ install-unwind
ninja: Entering directory `build/'
[1/1] cd /home/ubuntu/llvm-project/build/libunwind/src && /snap/cmake/992/bin/cmake -DCMAKE_INSTALL_COMPONENT=unwind -P /home/ubuntu/llvm-project/build/libunwind/cmake_install.cmake
-- Install configuration: ""
-- Installing: /mnt/toolchain/lib/libunwind.so.1.0
-- Installing: /mnt/toolchain/lib/libunwind.so.1
-- Installing: /mnt/toolchain/lib/libunwind.so
-- Installing: /mnt/toolchain/lib/libunwind.a

mkdir build-clang && cd build-clang
cmake \
    -DCMAKE_BUILD_TYPE=MinSizeRel \
    -DCMAKE_INSTALL_PREFIX=/mnt/toolchain \
    -DCMAKE_BUILD_WITH_INSTALL_RPATH=ON \
    -DLLVM_TARGETS_TO_BUILD=Native \
    -DLLVM_ENABLE_OCAMLDOC=OFF \
    -DLLVM_ENABLE_PROJECTS="compiler-rt;clang;lld" \
    -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind" \
    -DCLANG_ENABLE_BOOTSTRAP=ON \
    -DCLANG_DEFAULT_CXX_STDLIB=libc++ \
    -DCLANG_DEFAULT_RTLIB=compiler-rt \
    -DCLANG_DEFAULT_UNWINDLIB=libunwind \
    -DCLANG_ENABLE_ARCMT=OFF \
    -DCLANG_INCLUDE_DOCS=OFF \
    -DCOMPILER_RT_INCLUDE_DOCS=OFF \
    -DLIBCXX_INCLUDE_DOCS=OFF \
    -DLIBCXX_INCLUDE_TESTS=NO \
    -DLIBCXX_USE_COMPILER_RT=YES \
    -DLIBCXXABI_USE_COMPILER_RT=YES \
    -DLIBCXXABI_USE_LLVM_UNWINDER=YES \
    -DLIBCXXABI_INCLUDE_DOCS=OFF \
    -DLIBCXXABI_INCLUDE_TESTS=NO \
    -DLIBUNWIND_USE_COMPILER_RT=YES \
    -DLIBUNWIND_INCLUDE_DOCS=NO \
    -DLIBUNWIND_INCLUDE_TESTS=NO \
    -DBOOTSTRAP_CMAKE_BUILD_TYPE=MinSizeRel \
    -DBOOTSTRAP_CLANG_DEFAULT_CXX_STDLIB=libc++ \
    -DBOOTSTRAP_CLANG_DEFAULT_RTLIB=compiler-rt \
    -DBOOTSTRAP_LIBCXX_USE_COMPILER_RT=YES \
    -DBOOTSTRAP_LIBCXXABI_USE_COMPILER_RT=YES \
    -DBOOTSTRAP_LIBCXXABI_USE_LLVM_UNWINDER=YES \
    -DBOOTSTRAP_LIBUNWIND_USE_COMPILER_RT=Yes \
    -DBOOTSTRAP_LLVM_USE_LINKER=lld \
    -DBOOTSTRAP_LLVM_ENABLE_LLD=ON \
    -DLIBCXX_ENABLE_STATIC_ABI_LIBRARY=ON \
    -DLIBCXX_ENABLE_ABI_LINKER_SCRIPT=OFF \
    ../llvm

ninja cxx cxxabi unwind
ninja check-cxx check-cxxabi check-unwind
sudo ninja install-cxx install-cxxabi install-unwind
ninja build runtimes
ninja check-runtimes
sudo ninja install-runtimes
ninja && sudo ninja install

ldd lib/x86_64-unknown-linux-gnu/libc++.so.1
        linux-vdso.so.1 (0x00007ffe55b68000)
        libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f3b98ed2000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f3b98ce0000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f3b98b91000)
        librt.so.1 => /lib/x86_64-linux-gnu/librt.so.1 (0x00007f3b98b86000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f3b98b6b000)
        libatomic.so.1 => /lib/x86_64-linux-gnu/libatomic.so.1 (0x00007f3b98b61000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f3b98fd0000)
        libc++abi.so.1 => not found
        libunwind.so.1 => not found

ldd bin/clang
        linux-vdso.so.1 (0x00007fff3e578000)
        libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f0b8bd01000)
        libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f0b8bcfb000)
        libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f0b8bb19000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f0b8b9ca000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f0b8b9af000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f0b8b7bd000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f0b924c4000)
--
ldd lib/x86_64-unknown-linux-gnu/libc++.so.1
        linux-vdso.so.1 (0x00007ffc9aab2000)
        libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f7cdd1a1000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f7cdcfaf000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f7cdce60000)
        librt.so.1 => /lib/x86_64-linux-gnu/librt.so.1 (0x00007f7cdce55000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f7cdce3a000)
        libatomic.so.1 => /lib/x86_64-linux-gnu/libatomic.so.1 (0x00007f7cdce30000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f7cdd2a8000)
        libunwind.so.1 => not found

ldd bin/clang
        linux-vdso.so.1 (0x00007ffd791d5000)
        libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f6c3ca73000)
        libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f6c3ca6d000)
        libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f6c3c88b000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f6c3c73c000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f6c3c721000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f6c3c52f000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f6c40b7f000)