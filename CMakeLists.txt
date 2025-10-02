cmake_minimum_required(VERSION 3.31)
project(mike C)

set(CMAKE_C_STANDARD 11)

add_executable(mike main.c deps/glad/src/glad.c deps/open-simplex-noise/open-simplex-noise.c
        player.c shader.c main.c
        chunk.c
        texture.c
)

add_custom_target(cope
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
        COMMENT "copying ${CMAKE_SOURCE_DIR}/resources to ${CMAKE_BINARY_DIR}/resources"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_dependencies(mike cope)

add_subdirectory(deps/glfw-3.4)
target_link_libraries(mike glfw)

target_include_directories(mike PUBLIC deps/glad/include)
target_include_directories(mike PUBLIC deps/cglm/include)
target_include_directories(mike PUBLIC deps/open-simplex-noise)