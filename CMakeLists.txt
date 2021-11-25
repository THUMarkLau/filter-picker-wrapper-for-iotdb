cmake_minimum_required(VERSION 3.20)
project(FilterPicker)

set(CMAKE_CXX_STANDARD 11)

add_executable(FilterPicker main.cpp fp/FilterPicker5_Memory.cpp fp/FilterPicker5.cpp fp/FilterPickerWrapper.cpp fp/PickData.cpp fp/ValueCache.cpp fp/ValueBuffer.cpp)
