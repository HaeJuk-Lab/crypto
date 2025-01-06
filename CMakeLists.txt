#/******************************************************************************
#*  _   _    _    _____    _ _   _ _  __   _        _    ____ ____
#* | | | |  / \  | ____|  | | | | | |/ /  | |      / \  | __ ) ___|
#* | |_| | / _ \ |  _| _  | | | | | ' /   | |     / _ \ |  _ \___ \
#* |  _  |/ ___ \| |__| |_| | |_| | . \   | |___ / ___ \| |_) |__) |
#* |_| |_/_/   \_\_____\___/ \___/|_|\_\  |_____/_/   \_\____/____/
#*
#* Copyright (c) HAEJUK LABS All Rights Reserved.
#*
#*******************************************************************************/

#--------------------------------------------------------------------------------------------------
# CMAKE MINIMUM VERSION 
cmake_minimum_required(VERSION 3.17)

#--------------------------------------------------------------------------------------------------
# make 실행 시 상세한 상세한 정보를 남기도록 설정합니다.
SET (CMAKE_VERBOSE_MAKEFILE false)

#--------------------------------------------------------------------------------------------------
# PROJECT NAME 
PROJECT("hxCrypto")

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#--------------------------------------------------------------------------------------------------
# BUILD TYPE SET, DEFAULT is Release
if (${CMAKE_BUILD_TYPE} MATCHES Debug)
    set(TARGET_BUILD_TYPE_STRING "_debug")
    set(CMAKE_BUILD_TYPE Debug)
    add_definitions(-D_DEBUG)
else()
    set(TARGET_BUILD_TYPE_STRING "")
    set(CMAKE_BUILD_TYPE Release)
endif()

#--------------------------------------------------------------------------------------------------
# BUILD OUTPUT DIRECTORY SET
set(OUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
string(TOLOWER ${OUT_PATH} OUT_PATH)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUT_PATH})


# OS별 빌드 옵션
if(WIN32 OR MSVC)
    add_definitions(-DPLATFORM_WINDOWS)
    add_definitions(-D_WIN64)
    add_definitions(-DWINDOWS -D_AMD64_ -D_CRT_SECURE_NO_WARNINGS -D__HX_WINDOWS__ )
    set(LIBRARY_OUTPUT_NAME "hxCrypto")

elseif(APPLE)
    # 컴파일러를 정의합니다.
    SET(CMAKE_C_COMPILER gcc)
    SET(CMAKE_CXX_COMPILER g++)
    add_definitions(-D__HX_MAXOS__ )
    add_definitions(-DPLATFORM_MAC)
    set(LIBRARY_OUTPUT_NAME "libhxCrypto")
elseif(UNIX)
    # 컴파일러를 정의합니다.
    SET(CMAKE_C_COMPILER gcc)
    SET(CMAKE_CXX_COMPILER g++)
    add_definitions(-D__HX_LINUX__ )
    add_definitions(-DPLATFORM_LINUX)
    set(LIBRARY_OUTPUT_NAME "libhxCrypto")

     ADD_COMPILE_OPTIONS(-pipe -Wall -W -finline-functions -D_REENTRANT
        -Werror=return-type # 반환 값이 있는 함수에서 아무런 값도 반환하지 않는 경우 오류를 발생시킵니다.
        -Werror=type-limits # 자료형의 최댓값보다 큰/작은 값을 사용하려는 경우 오류를 발생시킵니다.
        -Wno-unused-parameter # 사용하지 않는 인자에 대한 경고를 발생시키지 않습니다.
        )
    SET(CMAKE_C_FLAGS_DEBUG "-g -ggdb -DDEBUG")
    SET(CMAKE_C_FLAGS_RELEASE "-g -ggdb -DNDEBUG -O2 -finline-functions")
    SET(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb -DDEBUG")
    SET(CMAKE_CXX_FLAGS_RELEASE "-g -ggdb -DNDEBUG -O2 -finline-functions")
    IF (BUILD_COVERAGE)
        SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
        SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
    ENDIF ()

    add_compile_options(-pipe -Wall -Wextra -Werror=return-type -Werror=type-limits -Wno-unused-parameter)
    # 링킹할 라이브러리 이름입니다. (gcc의 -l)
    LINK_LIBRARIES(gcov dl pthread)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

# 소스 파일 설정
file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES 
        include/*.h
        export/*.h
)

# 라이브러리 생성
add_library(${LIBRARY_OUTPUT_NAME} SHARED ${SRC_FILES})

# 인클루드 디렉토리 설정
target_include_directories(${LIBRARY_OUTPUT_NAME} PUBLIC include)

# 빌드 옵션
#target_compile_options(${LIBRARY_OUTPUT_NAME} PRIVATE -Wall -Wextra -Werror)