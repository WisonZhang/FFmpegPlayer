cmake_minimum_required(VERSION 3.10.2)

#find_library(log-lib log)

set(JNI_LIBS_DIR ${CMAKE_SOURCE_DIR}/jniLibs/armeabi-v7a)
set(libname player_core)

include_directories(
        ${CMAKE_SOURCE_DIR}/cpp/include
        ${CMAKE_SOURCE_DIR}/cpp/player
        ${CMAKE_SOURCE_DIR}/cpp/player/decode
        ${CMAKE_SOURCE_DIR}/cpp/player/render
)

file(GLOB src-files
        ${CMAKE_SOURCE_DIR}/cpp/*.cpp
        ${CMAKE_SOURCE_DIR}/cpp/player/*.cpp
        ${CMAKE_SOURCE_DIR}/cpp/player/decode/*.cpp
        ${CMAKE_SOURCE_DIR}/cpp/player/render/*.cpp
        )
add_library(${libname} SHARED ${src-files})
#add_library(utils SHARED ${CMAKE_SOURCE_DIR}/cpp/ffmpeg_utils.cpp)

add_library(avcodec SHARED IMPORTED)
set_target_properties(avcodec
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/libavcodec.so)

add_library(libavdevice SHARED IMPORTED)
set_target_properties(libavdevice
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/libavdevice.so)

add_library(libavfilter SHARED IMPORTED)
set_target_properties(libavfilter
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/libavfilter.so)

add_library(libavformat SHARED IMPORTED)
set_target_properties(libavformat
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/libavformat.so)

add_library(libavutil SHARED IMPORTED)
set_target_properties(libavutil
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/libavutil.so)

add_library(libpostproc SHARED IMPORTED)
set_target_properties(libpostproc
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/libpostproc.so)

add_library(libswresample SHARED IMPORTED)
set_target_properties(libswresample
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/libswresample.so)

add_library(libswscale SHARED IMPORTED)
set_target_properties(libswscale
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/libswscale.so)

add_library(libx264 SHARED IMPORTED)
set_target_properties(libx264
        PROPERTIES IMPORTED_LOCATION
        ${JNI_LIBS_DIR}/libx264161.so)

set(native-libs
        android
        log
        )

target_link_libraries(${libname} avcodec libavdevice libavfilter libavformat libavutil libpostproc libswresample libswscale libx264 ${native-libs})