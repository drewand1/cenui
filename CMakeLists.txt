cmake_minimum_required(VERSION 3.28)
project(cenuilib LANGUAGES CXX)

option(CENUI_BUILD_TESTS OFF)

# Fetch SFML from GitHub
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.1.0 # Or use "master" / "2.6.x" depending on your target version
    GIT_SHALLOW    ON
    EXCLUDE_FROM_ALL SYSTEM
)
FetchContent_MakeAvailable(SFML)

if(CENUI_BUILD_TESTS)
    add_subdirectory(tests)
endif()

add_library(cenui STATIC
    src/frame.cpp
    src/uidimensions.cpp
    src/draw.cpp
    src/framemanager.cpp
    src/clickhandler.cpp
    src/err.cpp
)
target_include_directories(cenui PUBLIC include)
target_link_libraries(cenui PUBLIC SFML::Graphics)