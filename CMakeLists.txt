cmake_minimum_required(VERSION 3.17)
project(NirvanaRenderer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Core)
include_directories(Platform)

add_executable(NirvanaRenderer
        Core/color.h
        Core/input.h
        Core/model.h
        Core/renderer.h
        Platform/win.h
        api.h
        main.cpp Core/maths.h Core/camera.h Core/macro.h Core/Component/transform.h Core/Component/com_inc.h Core/object.h Core/Asset/obj_loader.h Core/Asset/loader.h Core/Asset/asset_inc.h Core/Component/component.h)
