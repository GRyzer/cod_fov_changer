cmake_minimum_required(VERSION 3.15)

project(FovChanger)

set(CMAKE_CXX_STANDARD 17)

set(basicSourceFiles  
src/process.cpp 
)

add_executable(mw3_mp ${basicSourceFiles} src/mw3.cpp src/mw3_mp.cpp)
add_executable(mw3_sp ${basicSourceFiles} src/mw3.cpp src/mw3_sp.cpp)
add_executable(mw2_mp ${basicSourceFiles} src/mw2.cpp)

target_include_directories(mw3_mp PUBLIC include)
target_include_directories(mw3_sp PUBLIC include)
target_include_directories(mw2_mp PUBLIC include)
