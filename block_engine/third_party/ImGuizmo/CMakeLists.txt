cmake_minimum_required(VERSION 3.10)

project(ImGuizmo)

file(GLOB SRC_DIR
        *.h
        *.cpp
)

add_library(ImGuizmo STATIC
        ${SRC_DIR}
)