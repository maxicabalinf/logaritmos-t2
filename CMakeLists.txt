cmake_minimum_required(VERSION 3.10)
project(t2)

# Especifica directorios para el sistema de compilado.
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# Define opciones de compilación.
if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wunused -O3 -fopenmp)
    add_link_options(-fopenmp)
endif()

include_directories("${PROJECT_SOURCE_DIR}/src")

# Agrupa código fuente común a experimentos.
add_library(experiment_utils src/sorting.cpp src/sorting.h src/stats.cpp src/stats.h)

# Crea ejecutables
add_executable(comparison src/comparison.cpp)
target_link_libraries(comparison experiment_utils)

add_executable(test_sorting test/test_sorting.cpp)
target_link_libraries(test_sorting experiment_utils)