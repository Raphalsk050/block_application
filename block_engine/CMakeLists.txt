cmake_minimum_required(VERSION 3.31)
project(block_engine)

###############################################################
#### Cmake Variables ##########################################
###############################################################

set(CMAKE_CXX_STANDARD 20)
set(glm_DIR third_party/glm)
set(glfw_DIR third_party/glfw)
set(glad_DIR third_party/glad)
set(spdlog_DIR third_party/spdlog)
set(linmath_DIR third_party/linmath)
set(imgui_DIR third_party/ImGui)
set(imguizmo_DIR third_party/ImGuizmo)

###############################################################
#### platform detection #######################################
###############################################################

# GLM ===================
add_subdirectory(${glm_DIR})
add_subdirectory(${glfw_DIR})
add_subdirectory(${spdlog_DIR})
add_subdirectory(${imgui_DIR})
add_subdirectory(${imguizmo_DIR})

###############################################################
#### platform detection #######################################
###############################################################

add_library(glad STATIC
        ${glad_DIR}/src/glad.c
)

include_directories(
        ${glad_DIR}/include
        ${linmath_DIR}
        ${imgui_DIR}
        ${imguizmo_DIR}
)

file(GLOB_RECURSE ENGINE_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp
)

add_library(block_engine STATIC
        ${ENGINE_SRC}
)


# Compile commands
target_compile_definitions(block_engine
        PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
)

###############################################################
#### platform detection #######################################
###############################################################

if (WIN32)
    target_compile_definitions(block_engine
            PUBLIC
            BENGINE_PLATFORM_WINDOWS
    )
elseif (APPLE)
    target_compile_definitions(block_engine
            PUBLIC
            BENGINE_PLATFORM_APPLE
    )
elseif (UNIX)
    target_compile_definitions(block_engine
            PUBLIC
            BENGINE_PLATFORM_LINUX
    )
endif ()


#target_sources(block_engine PRIVATE
#        $<$<CONFIG:Debug>:src/log/belog.cpp>
#)

###############################################################
#### linked libraries #########################################
###############################################################

target_link_libraries(ImGui PUBLIC glm glfw glad)
target_include_directories(ImGui PUBLIC
        ${glad_DIR}/include
        ${linmath_DIR}
        ${imgui_DIR}
)

target_link_libraries(block_engine PUBLIC glm glfw glad spdlog ImGui ImGuizmo)
