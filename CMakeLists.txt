cmake_minimum_required(VERSION 2.4.3)
project(block_application)

set(CMAKE_CXX_STANDARD 20)

# Engine
add_subdirectory(block_engine)

target_include_directories(block_engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Application
add_subdirectory(block_application)