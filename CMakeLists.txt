cmake_minimum_required(VERSION 4.3)
project(DeltaClicker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(DeltaClickerCore STATIC
        src/common/DeltaClickerCore.cpp
        src/common/DeltaClickerCore.hpp
)

target_include_directories(DeltaClickerCore
        PUBLIC src/common
)

# CLI
add_executable(DeltaClickerCLI
        src/cli/main.cpp
)

target_link_libraries(DeltaClickerCLI
        PRIVATE DeltaClickerCore
)

# GUI — заміни шлях на свій main.cpp
add_executable(DeltaClickerGUI
        src/gui/main.cpp

)

target_link_libraries(DeltaClickerGUI
        PRIVATE DeltaClickerCore
)