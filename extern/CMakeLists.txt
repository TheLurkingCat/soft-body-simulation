project (external LANGUAGES C CXX)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${external_SOURCE_DIR}/stb)

add_library(eigen INTERFACE)
target_include_directories(eigen INTERFACE ${external_SOURCE_DIR}/eigen)
target_compile_definitions(eigen INTERFACE EIGEN_MPL2_ONLY)
target_compile_definitions(eigen INTERFACE EIGEN_NO_DEBUG)
target_compile_definitions(eigen INTERFACE EIGEN_DONT_PARALLELIZE)
if (MSVC)
    target_compile_options(eigen INTERFACE "/wd4819")
endif()

add_library(glad INTERFACE)
target_include_directories(glad INTERFACE ${external_SOURCE_DIR}/glad/include)
if (MSVC)
    target_compile_options(glad INTERFACE "/wd4551")
endif()

set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_VULKAN_STATIC OFF)
add_subdirectory(glfw)
if (MSVC)
    target_compile_options(glfw PUBLIC "/wd4819")
endif()

add_library(imgui STATIC
    ${external_SOURCE_DIR}/imgui/imgui.cpp
    ${external_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${external_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${external_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
    ${external_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${external_SOURCE_DIR}/imgui/imgui_widgets.cpp
)
target_link_libraries(imgui PRIVATE glfw glad)
set_target_properties(imgui PROPERTIES CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(imgui PRIVATE cxx_std_17)
target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD2)
target_include_directories(imgui
    PUBLIC ${external_SOURCE_DIR}/imgui
    PUBLIC ${external_SOURCE_DIR}/imgui/backends
)

add_library(external INTERFACE)
target_link_libraries(external
    INTERFACE stb
    INTERFACE eigen
    INTERFACE glad
    INTERFACE glfw
    INTERFACE imgui
)

