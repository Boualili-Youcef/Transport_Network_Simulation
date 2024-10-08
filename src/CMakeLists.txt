include_directories(${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_SOURCE_DIR}/src)

add_library(transport Kernel.cpp Kernel.hpp Line.cpp Line.hpp main.cpp State.cpp State.hpp Station.hpp Train.cpp Train.hpp Way.hpp)

target_link_libraries(transport)

add_executable(main main.cpp)

target_link_libraries(main transport)

