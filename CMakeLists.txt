cmake_minimum_required(VERSION 3.20)
project(DeltaClicker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(DeltaClickerCore STATIC
        src/common/DeltaClickerCore.cpp
        src/common/DeltaClickerCore.hpp
)

target_include_directories(DeltaClickerCore
        PUBLIC src/common
)


add_executable(DeltaClickerCLI
        src/cli/main.cpp
)

target_link_libraries(DeltaClickerCLI
        PRIVATE DeltaClickerCore
)


include(FetchContent)
FetchContent_Declare(glfw  GIT_REPOSITORY https://github.com/glfw/glfw.git     GIT_TAG 3.4)
FetchContent_Declare(imgui GIT_REPOSITORY https://github.com/ocornut/imgui.git GIT_TAG v1.91.5)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw imgui)

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

add_library(imgui_lib STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui_lib PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui_lib PUBLIC glfw OpenGL::GL)

add_executable(DeltaClickerGUI
        src/gui/main.cpp
)

target_link_libraries(DeltaClickerGUI
        PRIVATE imgui_lib DeltaClickerCore Threads::Threads
)


if(MINGW)
    target_link_options(DeltaClickerGUI PRIVATE -static-libgcc -static-libstdc++)
endif()