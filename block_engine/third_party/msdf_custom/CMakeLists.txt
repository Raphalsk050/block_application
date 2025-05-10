# block_engine/third_party/msdf_custom/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(msdf_custom)

# Core sources from msdfgen
file(GLOB MSDFGEN_CORE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/../msdf_atlas_gen/msdfgen/core/*.cpp"
)

# Only essential atlas sources
set(MSDF_ATLAS_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/../msdf_atlas_gen/msdf-atlas-gen/size-selectors.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/../msdf_atlas_gen/msdf-atlas-gen/glyph-generators.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/../msdf_atlas_gen/msdf-atlas-gen/Charset.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/../msdf_atlas_gen/msdf-atlas-gen/bitmap-blit.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/../msdf_atlas_gen/msdf-atlas-gen/Workload.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/../msdf_atlas_gen/msdf-atlas-gen/Remap.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/../msdf_atlas_gen/msdf-atlas-gen/Rectangle.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/../msdf_atlas_gen/msdf-atlas-gen/GlyphGeometry.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/../msdf_atlas_gen/msdf-atlas-gen/GlyphBox.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/../msdf_atlas_gen/msdf-atlas-gen/FontGeometry.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/../msdf_atlas_gen/msdf-atlas-gen/AtlasStorage.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/../msdf_atlas_gen/msdf-atlas-gen/AtlasGenerator.h"
)

# Create a library with only the core functionality
add_library(msdf_custom STATIC
        ${MSDFGEN_CORE_SOURCES}
        ${MSDF_ATLAS_SOURCES}
)

# Configure include directories
target_include_directories(msdf_custom PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../msdf_atlas_gen/msdfgen"
        "${CMAKE_CURRENT_SOURCE_DIR}/../msdf_atlas_gen"
)

# Define preprocessor macros to disable dependencies
target_compile_definitions(msdf_custom PUBLIC
        MSDFGEN_USE_OPENMP=0
        MSDFGEN_USE_CPP11=1
        MSDFGEN_NO_FREETYPE=1
        MSDF_ATLAS_NO_PNG=1
        MSDF_ATLAS_NO_ARTERY_FONT=1
)