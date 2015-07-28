#!/bin/bash
#mkdir -p bin include
install -d build
pushd build
#cmake -DCMAKE_INSTALL_PREFIX=~servan/Tools -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
#cmake -DCMAKE_EXE_LINKER_FLAGS="-static" -DCMAKE_INSTALL_PREFIX=$1 -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
cmake -DCMAKE_INSTALL_PREFIX=$1 -DCMAKE_BUILD_TYPE=RelWithDebInfo .. 
make -j4 && \
make install
popd
