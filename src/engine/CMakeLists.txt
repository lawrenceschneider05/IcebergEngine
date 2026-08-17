file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

add_library(Engine STATIC 
    ${ENGINE_SOURCES} 
    "${CMAKE_SOURCE_DIR}/vendor/include/glad/glad.c"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Engine PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(Engine PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_include_directories(Engine PRIVATE 
    "${CMAKE_SOURCE_DIR}/src/engine"
    "${CMAKE_SOURCE_DIR}/vendor/include"
)

target_link_directories(Engine PRIVATE 
    "${CMAKE_SOURCE_DIR}/vendor/lib"
)

target_link_libraries(Engine PRIVATE 
    glfw3
    opengl32
)