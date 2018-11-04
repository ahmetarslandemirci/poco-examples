cmake_minimum_required(VERSION 3.5)


include(${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
add_definitions(-std=c++11)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

add_executable(ntpclient main.cpp)
target_link_libraries(ntpclient ${CONAN_LIBS})
