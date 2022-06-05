cmake_minimum_required(VERSION 3.22)
project(VolunteerManagement C)

set(CMAKE_C_STANDARD 99)
set(D:/mysql-8.0.29-winx64 ./include)
set(D:/mysql-8.0.29-winx64 ./lib)
include_directories(D:/mysql-8.0.29-winx64/include)
link_directories(D:/mysql-8.0.29-winx64/lib)

add_executable(VolunteerManagement main.c)
target_link_libraries(VolunteerManagement libmysql.lib)

