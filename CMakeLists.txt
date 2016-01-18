cmake_minimum_required(VERSION 3.3)
project(opencv_facedetect_server)

set(CMAKE_MODULE_PATH ${opencv_facedetect_server_SOURCE_DIR})

find_package( OpenCV REQUIRED )
find_package (ZBar0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories( ${OpenCV_INCLUDE_DIRS} )

set(SOURCE_FILES main.cpp config.h score.h detect_face.h detect_symbols.h detect_size.h lib.h roy_system.h)
add_executable(test.exe ${SOURCE_FILES})
target_link_libraries( test.exe ${OpenCV_LIBS} ${ZBAR_LIBRARIES} -lboost_system)