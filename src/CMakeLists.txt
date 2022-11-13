
include_directories(${CMAKE_SOURCE_DIR}/src)
add_library(lodge ${SOURCE_FILES})
target_link_libraries(lodge fmt)
