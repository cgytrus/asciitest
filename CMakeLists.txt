cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

project(asciitest)

add_executable(asciitest
    src/main.cpp
    src/Shader.cpp
)

include(cmake/CPM.cmake)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
else()
    #find_package(X11 REQUIRED)
    #find_package(OpenGL REQUIRED)
    #target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL X11::X11 X11::Xrandr)
endif()

CPMAddPackage("gh:ColleagueRiley/RGFW#f49b9e7")
target_include_directories(${PROJECT_NAME} PRIVATE ${RGFW_SOURCE_DIR})

CPMAddPackage("gh:Dav1dde/glad@2.0.8")
add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
glad_add_library(glad_gl_core_33 REPRODUCIBLE API gl:core=3.3)
target_link_libraries(${PROJECT_NAME} PRIVATE glad_gl_core_33)

CPMAddPackage(
    URI "gh:g-truc/glm#1.0.3"
    OPTIONS "GLM_ENABLE_CXX_20 ON" "GLM_ENABLE_LANG_EXTENSIONS ON" "GLM_ENABLE_SIMD_AVX2 ON"
)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

CPMAddPackage("gh:fmtlib/fmt#12.1.0")
target_link_libraries(${PROJECT_NAME} PRIVATE fmt)

CPMAddPackage("gh:dankmeme01/asp2#51d3773")
get_target_property(aspDefs asp COMPILE_DEFINITIONS)
list(FILTER aspDefs EXCLUDE REGEX [[^_HAS_ITERATOR_DEBUGGING=0$]])
set_property(TARGET asp PROPERTY COMPILE_DEFINITIONS ${aspDefs})
target_link_libraries(${PROJECT_NAME} PRIVATE asp)

CPMAddPackage("gh:sivachandran/cmake-bin2h#3777f88")
include(${cmake-bin2h_SOURCE_DIR}/bin2h.cmake)
function(add_resource SOURCE_FILE)
    get_filename_component(name ${SOURCE_FILE} NAME)
    bin2h(
        SOURCE_FILE ${SOURCE_FILE}
        VARIABLE_NAME ${name}
        HEADER_FILE ${CMAKE_CURRENT_BINARY_DIR}/resources/${name}.h
    )
endfunction()
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/resources)

add_resource(src/default.vert)
add_resource(src/default.frag)

add_resource(src/mat.vert)
add_resource(src/mat.frag)
