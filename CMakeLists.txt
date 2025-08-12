#Tommaso Boscardin

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(Monopoly LANGUAGES CXX)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(Monopoly
	src/Monopoly.cpp
)
add_library(Table
	include/Table.h
	src/Table.cpp
)
add_library(Land
	include/Land.h
	src/Land.cpp
)
add_library(Player
	include/Player.h
	src/Player.cpp
)
add_library(Human
	include/Human.h
	src/Human.cpp
)
add_library(Computer
	include/Computer.h
	src/Computer.cpp
)
add_library(Match
	include/Match.h
	src/Match.cpp
)

target_link_libraries(Monopoly
	Table
	Land
	Player
	Human
	Computer
	Match
)
target_link_libraries(Match
	Table
	Land
	Player
	Human
	Computer
)
target_link_libraries(Human
	Player
)
target_link_libraries(Computer
	Player
)
target_link_libraries(Land
	Player
)
target_link_libraries(Table
	Player
	Land
)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O2")