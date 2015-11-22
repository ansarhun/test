add_library(MyLib lib.cpp)
target_link_libraries(MyLib Qt5::Core)

add_executable(store main.cpp)
target_link_libraries(store MyLib)