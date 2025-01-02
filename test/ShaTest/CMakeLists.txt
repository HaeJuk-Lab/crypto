cmake_minimum_required(VERSION 3.17)

# 프로젝트 이름 설정
project("hxShaTest")

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 빌드 타입 설정
if (${CMAKE_BUILD_TYPE} MATCHES Debug)
    set(TARGET_BUILD_TYPE_STRING "_debug")
    set(CMAKE_BUILD_TYPE Debug)
    add_definitions(-D_DEBUG)
else()
    set(TARGET_BUILD_TYPE_STRING "")
    set(CMAKE_BUILD_TYPE Release)
endif()

# 출력 디렉터리 설정
set(OUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../bin/${CMAKE_BUILD_TYPE})
string(TOLOWER ${OUT_PATH} OUT_PATH)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUT_PATH})

# OS별 빌드 옵션 설정
if(WIN32 OR MSVC)
    add_definitions(-DPLATFORM_WINDOWS)
    add_definitions(-D_WIN64)
    add_definitions(-DCONSOLE -D_AMD64_ -D_CRT_SECURE_NO_WARNINGS -D__HX_WINDOWS__ )
elseif(APPLE)
    SET(CMAKE_C_COMPILER gcc)
    SET(CMAKE_CXX_COMPILER g++)
    add_definitions(-D__HX_MAXOS__ )
    add_definitions(-DPLATFORM_MAC)
elseif(UNIX)
    SET(CMAKE_C_COMPILER gcc)
    SET(CMAKE_CXX_COMPILER g++)
    add_definitions(-D__HX_LINUX__ )
    add_definitions(-DPLATFORM_LINUX)

    ADD_COMPILE_OPTIONS(-pipe -Wall -W -finline-functions -D_REENTRANT
        -Werror=return-type
        -Werror=type-limits
        -Wno-unused-parameter
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
    LINK_LIBRARIES(gcov dl pthread)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

# 소스 파일 검색
file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.h)

# 소스 파일 추가 (src/sha/*.cpp 포함)
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../../src/sha/*.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/../../src/sha/*.hpp
)



# 실행 파일 생성
add_executable(test_main main.cpp ${SRC_FILES})

# 인클루드 디렉터리 추가
target_include_directories(test_main PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include  # root/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/sha  # root/src/sha
)
