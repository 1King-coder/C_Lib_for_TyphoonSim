cmake_minimum_required(VERSION 4.1)
project(C_FOR_TYPHOON C)

set(CMAKE_C_STANDARD 11)

add_library(C_FOR_TYPHOON SHARED c_for_typhoon.c)
