load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

cc_binary(
    name = "monkey",
    srcs = ["monkey.cc"],
    linkopts = ["-lGLEW", "-lglfw", "-lGL"], 
    deps = ["gl_util"] 
)

cc_binary(
    name = "texture_cube",
    srcs = ["texture_cube.cc"],
    linkopts = ["-lGLEW", "-lglfw", "-lGL"], 
    deps = ["gl_util"] 
)

cc_binary(
    name = "color_cube",
    srcs = ["color_cube.cc"],
    linkopts = ["-lGLEW", "-lglfw", "-lGL"], 
    deps = ["gl_util"] 
)

cc_library(
    name = "gl_util",
    hdrs = ["gl_util.hpp"]
)

cc_binary(
    name = "texture",
    srcs = ["texture.cc"],
    linkopts = ["-lglut", "-lGLEW", "-lGL", "-lGLU"]    
)

cc_binary(
    name = "fog",
    srcs = ["fog.cc"],
    linkopts = ["-lglut", "-lGLU", "-lGL"]    
)

cc_binary(
    name = "sphere",
    srcs = ["sphere.cc"],
    linkopts = ["-lglut", "-lGLU", "-lGL"]    
)

cc_binary(
    name = "click_to_spin",
    srcs = ["click_to_spin.cc"],
    linkopts = ["-lglut", "-lGLU", "-lGL"]    
)

cc_binary(
    name = "click_to_spin_3d",
    srcs = ["click_to_spin_3d.cc"],
    linkopts = ["-lglut", "-lGLU", "-lGL"]    
)

cc_binary(
    name = "polygon",
    srcs = ["polygon.cc"],
    linkopts = ["-lglut", "-lGLU", "-lGL"]      
)

cc_binary(
    name = "matrix_basic",
    srcs = ["matrix_basic.cc"],
    deps = ["@eigen"]
)

cc_binary(
    name = "hw1",
    srcs = ["hw1.cpp"],
    deps = ["rasterizer"]
)

cc_binary(
    name = "hw2",
    srcs = ["hw2.cpp"],
    deps = ["rasterizer"]
)

cc_library(
    name = "rasterizer",
    srcs = ["rasterizer.cpp"],
    hdrs = ["rasterizer.hpp"],
    deps = ["@eigen", "opencv", "triangle"]
)


cmake_external(
    name = "opencv",
    cmake_options = [
        "-GNinja",
        "-DBUILD_LIST=core,highgui,imgcodecs,imgproc",
    ],
    lib_source = "@opencv//:all",
    make_commands = [
        "ninja",
        "ninja install",
    ],
    out_include_dir = "include/opencv4",
    shared_libraries = [
        "libopencv_core.so",
        "libopencv_highgui.so",
        "libopencv_imgcodecs.so",
        "libopencv_imgproc.so",
    ],
    visibility = ["//visibility:public"],
)
