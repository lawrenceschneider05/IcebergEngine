file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

add_executable(Game ${GAME_SOURCES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Game PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(Game PRIVATE 
    "${CMAKE_SOURCE_DIR}/vendor/include"
)
target_link_directories(Game PRIVATE 
    "${CMAKE_SOURCE_DIR}/vendor/lib"
)

target_link_libraries(Game PRIVATE Engine)