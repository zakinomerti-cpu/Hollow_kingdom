cmake_minimum_required(VERSION 3.14)
project(nonownContainers C)

add_library(nonownContainers STATIC
    hashArray/pvd_realization.c
    pVoidArray/pVoidArray.c
)

target_compile_features(nonownContainers PUBLIC c_std_99)
target_include_directories(nonownContainers PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/pVoidArray/
	${CMAKE_CURRENT_SOURCE_DIR}/hashArray/
)
