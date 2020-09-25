cmake_minimum_required(VERSION 3.17)
project(NirvanaRendere)

set(CMAKE_CXX_STANDARD 14)

add_executable(NirvanaRendere main.cpp Core/vec.h Core/mat.h Platform/win.h api.h Core/renderer.h Core/input.h Core/color.h Core/data_struct.h Core/mathf.h Core/transform.h Core/model.h)