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