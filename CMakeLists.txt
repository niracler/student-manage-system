cmake_minimum_required(VERSION 3.7)
project(Student)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp interface_Base.h interface_Class.h interface_Speciality.h interface_set.h interface_Grade.h interface_Student.h school.h student.cpp student.h README.md)
add_executable(Student ${SOURCE_FILES})