cmake_minimum_required(VERSION 3.5)

project(crs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(crs
	main.cpp
	User.h
	User.cpp
	Travel.h
	Travel.cpp
	Auth.h
	Auth.cpp
	Common.hpp
	TravelTable.h
	TravelTable.cpp
	UserTable.h
	UserTable.cpp)

install(TARGETS crs
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
