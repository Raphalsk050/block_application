cmake_minimum_required(VERSION 3.31)


add_executable(block_application
        block_application.cpp
        generic_layer.cpp
        generic_layer.h
)

target_compile_definitions(block_application
        PRIVATE
        DEBUG
)

target_link_libraries(block_application PRIVATE block_engine ImGui)
target_include_directories(block_application PRIVATE ${PROJECT_SOURCE_DIR}/block_engine ${PROJECT_SOURCE_DIR}/block_engine/third_party/imgui)