cmake_minimum_required(VERSION 3.3)
project(opencv_server_source)

set(CMAKE_MODULE_PATH ${opencv_server_source_SOURCE_DIR})
# set the directories to search for cmake modules

find_package( OpenCV REQUIRED )
find_package (ZBar0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(opencv_server_source_BINARY_DIR ${opencv_server_source_SOURCE_DIR}/release)

include_directories( ${opencv_server_source_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS} )

set(SOURCE_FILES
        main.cpp
        config.h
        score.h
        core/detect_face.h
        core/detect_symbols.h
        core/detect_size.h
        lib/lib.h
        lib/roy_system.h
        )

add_executable(opencv.out.1.0.1 ${SOURCE_FILES})
target_link_libraries( opencv.out.1.0.1 ${OpenCV_LIBS} ${ZBAR_LIBRARIES} -lboost_system)