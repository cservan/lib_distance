#!/bin/bash
#################################
# lib-distance: an open-source library to use the word2vec models.
#
# Copyright 2015, Christophe Servan, GETALP-LIG, University of Grenoble, France
# Contact: christophe.servan@gmail.com
#
# The tercpp tool and library are free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by 
# the Free Software Foundation, either version 2.1 of the licence, or
# (at your option) any later version.
#
# This program and library are distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
###################################
#mkdir -p bin include
install -d build
pushd build
#cmake -DCMAKE_INSTALL_PREFIX=~servan/Tools -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
#cmake -DCMAKE_EXE_LINKER_FLAGS="-static" -DCMAKE_INSTALL_PREFIX=$1 -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
cmake -DCMAKE_INSTALL_PREFIX=$1 -DCMAKE_BUILD_TYPE=RelWithDebInfo .. 
make -j4 && \
make install
popd
