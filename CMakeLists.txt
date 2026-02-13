cmake_minimum_required(VERSION 3.10.0)
project(REPLACE_ME VERSION 0.1.0 LANGUAGES C CXX)

### Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -Wpedantic)
# add_compile_options(-Werror)
add_compile_options(-g -O0 -fno-omit-frame-pointer -fstandalone-debug) 

### Set the output directories for the all binarys
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(CTest)
if (BUILD_TESTING)

    enable_testing()
    include(FetchContent)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    FetchContent_MakeAvailable(googletest)
    add_compile_definitions(UNIT_TEST)
endif()

add_executable(${PROJECT_NAME} main.cpp)

# add_subdirectory(src)

target_link_libraries(${PROJECT_NAME}
    
)
