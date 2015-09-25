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
PROJECT(wookie)


include_directories(BEFORE ${CMAKE_SOURCE_DIR}/src)

SET(giveDistance_SRCS
   main.cpp
   ${CMAKE_SOURCE_DIR}/src/tools.cpp
   ${CMAKE_SOURCE_DIR}/src/biword.cpp
   ${CMAKE_SOURCE_DIR}/src/bilingualModel.cpp
   ${CMAKE_SOURCE_DIR}/src/monolingualModel.cpp
   ${CMAKE_SOURCE_DIR}/src/alignmentData.cpp
   ${CMAKE_SOURCE_DIR}/src/distance.cpp
)

SET(threads_tests_SRCS
   main_test.cpp
   
)

add_executable(giveDistance ${giveDistance_SRCS})
#add_executable(threads_tests ${threads_tests_SRCS})

target_link_libraries(giveDistance boost_regex boost_system boost_filesystem boost_iostreams boost_thread)
#target_link_libraries(threads_tests boost_thread)
# target_link_libraries(wookie tercalc xmlStructure documentStructure multiEvaluation)
# 
install(TARGETS giveDistance DESTINATION bin)

