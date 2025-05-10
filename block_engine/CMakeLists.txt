cmake_minimum_required(VERSION 3.31)
project(block_engine)


###############################################################
#### Cmake Variables ##########################################
###############################################################
set(SHADERC_SKIP_INSTALL OFF)
set(SHADERC_SKIP_TESTS ON)
set(SHADERC_ENABLE_SHARED_CRT ON)
set(SPIRV_CROSS_CLI OFF CACHE BOOL "Build the CLI binary")
set(SPIRV_CROSS_ENABLE_TESTS OFF CACHE BOOL "Enable SPIRV-Cross tests")
set(SPIRV_CROSS_ENABLE_GLSL ON CACHE BOOL "Enable GLSL support")
set(SPIRV_CROSS_SKIP_INSTALL ON CACHE BOOL "Skip installation")
set(GLFW_INSTALL OFF CACHE BOOL "Generate installation target" FORCE)

###############################################################
#### MSDF_ATLAS_GEN ###########################################
###############################################################
#[[set(MSDFGEN_DISABLE_PNG ON CACHE BOOL "Disable PNG support" FORCE)
set(MSDF_ATLAS_BUILD_TESTS OFF CACHE BOOL "Build tests" FORCE)
set(MSDF_ATLAS_BUILD_STANDALONE OFF CACHE BOOL "Build command line executable" FORCE)
set(MSDF_ATLAS_NO_ARTERY_FONT ON CACHE BOOL "Disable Artery Font support" FORCE)
set(MSDFGEN_EXTERNAL_FREETYPE ON CACHE BOOL "Use external Freetype" FORCE)
set(MSDFGEN_FREETYPE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/block_engine/third_party/freetype" CACHE PATH "Path to Freetype" FORCE)]]


###############################################################
#### Lib Paths ################################################
###############################################################
set(CMAKE_CXX_STANDARD 20)
set(glm_DIR third_party/glm)
set(glfw_DIR third_party/glfw)
set(glad_DIR third_party/glad)
set(spdlog_DIR third_party/spdlog)
set(linmath_DIR third_party/linmath)
set(imgui_DIR third_party/ImGui)
set(imguizmo_DIR third_party/ImGuizmo)
set(spirv_cross_DIR third_party/spirv-cross)
set(shaderc_DIR third_party/shaderc)
set(msdf_atlas_gen_DIR third_party/msdf_custom)
set(freetype_DIR third_party/freetype)

###############################################################
#### platform detection #######################################
###############################################################
# GLM ===================
add_subdirectory(${glm_DIR})
add_subdirectory(${glfw_DIR})
add_subdirectory(${spdlog_DIR})
add_subdirectory(${imgui_DIR})
add_subdirectory(${imguizmo_DIR})
add_subdirectory(${shaderc_DIR})
add_subdirectory(${spirv_cross_DIR})
add_subdirectory(${freetype_DIR})
add_subdirectory(${msdf_atlas_gen_DIR})


###############################################################
#### Libs #####################################################
###############################################################
add_library(glad STATIC
        ${glad_DIR}/src/glad.c
)

include_directories(
        ${glad_DIR}/include
        ${linmath_DIR}
        ${imgui_DIR}
        ${imguizmo_DIR}
        ${spirv_cross_DIR}
        ${shaderc_DIR}
        ${msdf_atlas_gen_DIR}
        ${freetype_DIR}
)

file(GLOB_RECURSE ENGINE_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp
)

add_library(block_engine STATIC
        ${ENGINE_SRC}
        third_party/stb_image/stb_image.h
        third_party/stb_image/stb_image.cpp

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

target_link_libraries(ImGuizmo PUBLIC ImGui)

target_include_directories(ImGui PUBLIC
        ${imgui_DIR}

)

target_link_libraries(block_engine PUBLIC glm glfw glad spdlog ImGui ImGuizmo spirv-cross-core spirv-cross-glsl shaderc msdf_custom)
