cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(SoftbodySimulation LANGUAGES CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# Set to Release by default
if (NOT (CMAKE_BUILD_TYPE OR CMAKE_CONFIGURATION_TYPES))
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "RelWithDebInfo" "MinSizeRel" "Debug")
endif ()
option(BUILD_SHARED_LIBS "Build dependency as shared libraries" TRUE)
# Detect some compiler flags
include(CheckCXXCompilerFlag)
include(CheckIPOSupported)
if (NOT COMPILER_FLAG_TEST_COMPLETE)
    check_ipo_supported(RESULT COMPILER_SUPPORT_IPO)
    check_cxx_compiler_flag("-march=native" COMPILER_SUPPORT_MARCH_NATIVE)
    check_cxx_compiler_flag("-xHost" COMPILER_SUPPORT_xHOST)
    check_cxx_compiler_flag("/QxHost" COMPILER_SUPPORT_QxHOST)
    check_cxx_compiler_flag("/arch:AVX512" COMPILER_SUPPORT_ARCH_AVX512)
    set(COMPILER_FLAG_TEST_COMPLETE TRUE)
endif()
# Link time optimization
if (MSVC)
	add_compile_options("$<$<CONFIG:Release>:/GL>")
	add_link_options("$<$<CONFIG:Release>:/LTCG:incremental>")
elseif(COMPILER_SUPPORT_IPO)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()
# Visual Studio need this for multithread compile
if (MSVC)
    add_compile_options("/MP")
endif()
# Detect AVX2 if using Visual Studio since it doens't provided -march=native
if (MSVC)
    if (NOT DEFINED AVX512_RUN_RESULT AND COMPILER_SUPPORT_ARCH_AVX512)
        try_run(AVX512_RUN_RESULT AVX512_COMPILE_RESULT ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cputest/avx512.cpp)
    endif()
    if (NOT DEFINED AVX2_RUN_RESULT)
        try_run(AVX2_RUN_RESULT AVX2_COMPILE_RESULT ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cputest/avx2.cpp)
    endif()
    if (NOT DEFINED AVX_RUN_RESULT)
        try_run(AVX_RUN_RESULT AVX_COMPILE_RESULT ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cputest/avx.cpp)
    endif()
endif()
# SIMD support
if (COMPILER_SUPPORT_MARCH_NATIVE)
    add_compile_options("-march=native")
elseif(COMPILER_SUPPORT_xHOST)
    add_compile_options("-xHost")
elseif(COMPILER_SUPPORT_QxHOST)
    add_compile_options("/QxHost")
elseif(MSVC)
    if (AVX512_RUN_RESULT EQUAL 0)
        message(STATUS "Your CPU supports AVX512")
        add_compile_options("/arch:AVX512")
    elseif(AVX2_RUN_RESULT EQUAL 0)
        message(STATUS "Your CPU supports AVX2")
        add_compile_options("/arch:AVX2")
    elseif(AVX_RUN_RESULT EQUAL 0)
        message(STATUS "Your CPU supports AVX")
        add_compile_options("/arch:AVX")
    endif()
endif()
# Softbody simulation part
add_executable(SoftbodySimulation
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/default_camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/free_camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/rigidbody.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/graphic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/plane.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/sphere.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/simulation/cube.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/simulation/integrator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/simulation/massSpringSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/simulation/particle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/simulation/spring.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/simulation/terrain.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/util/clock.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/util/exporter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/util/filesystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/util/helper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SoftbodySimulation/main.cpp
)
# Base include files
target_include_directories(SoftbodySimulation PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
# Use C++17
target_compile_features(SoftbodySimulation PRIVATE cxx_std_17)
# Use std C++17 not GNU C++17
set_target_properties(SoftbodySimulation PROPERTIES CMAKE_CXX_EXTENSIONS OFF)
# Workaround for include order of glfw and glad2
target_compile_definitions(SoftbodySimulation PRIVATE GLFW_INCLUDE_NONE)
# For exporter
find_package(Threads REQUIRED)
# Add third-party libraries
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern)
# Link those third-party libraries
target_link_libraries(SoftbodySimulation
    PRIVATE Threads::Threads
    PRIVATE external
)
