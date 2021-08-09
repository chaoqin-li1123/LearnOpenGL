load("@rules_cc//cc:defs.bzl", "cc_library")
load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

cc_library(
    name = "checkboard_shader",
    hdrs = ["checkboard_shader.h"],
    visibility = ["//visibility:public"],
    deps = [
        "checkboard_object",
        "//util:gl_util",
        "//util:program",
    ],
)

cc_library(
    name = "checkboard_object",
    hdrs = ["checkboard_object.h"],
    deps = [
        "//util:gl_util",
        "//util:program",
    ],
)
