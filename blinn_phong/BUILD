load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    linkopts = ["-lGLEW", "-lglfw", "-lGL"], 
    deps = ["shader"] 
)

cc_library(
    name = "shader",
    hdrs = ["shader.h"],
    deps = ["gl_util", "texture", "object", "program", "light", "transformation", "curve"]
)

cc_library(
    name = "curve",
    hdrs = ["curve.h"],
    deps = ["gl_util"]
)

cc_library(
    name = "transformation",
    hdrs = ["transformation.h"],
    deps = ["gl_util"]
)

cc_library(
    name = "light",
    hdrs = ["light.h"],
    deps = ["gl_util"]
)

cc_library(
    name = "texture",
    hdrs = ["texture.h"],
    deps = ["gl_util"]
)

cc_library(
    name = "object",
    hdrs = ["object.h"],
    deps = ["gl_util"]
)

cc_library(
    name = "program",
    hdrs = ["program.h"],
    deps = ["gl_util"]
)

cc_library(
    name = "gl_util",
    srcs = ["gl_util.cc"],
    hdrs = ["gl_util.h"],
)