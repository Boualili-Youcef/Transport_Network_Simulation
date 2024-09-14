include_directories(${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(transport transport.h transport.c main.c)

#add_library(transport xxx.hpp xxx.cpp)

#target_link_libraries(transport)

#add_executable(main main.cpp)

#target_link_libraries(main transport)

