load("@rules_cc//cc:defs.bzl", "cc_library")
load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

cc_library(
    name = "curve",
    hdrs = ["curve.h"],
    deps = ["gl_util"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "transformation",
    hdrs = ["transformation.h"],
    deps = ["gl_util"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "light",
    hdrs = ["light.h"],
    deps = ["gl_util"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "texture",
    hdrs = ["texture.h"],
    deps = ["gl_util"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "object",
    hdrs = ["object.h"],
    deps = ["gl_util"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "program",
    hdrs = ["program.h"],
    deps = ["gl_util"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "gl_util",
    srcs = ["gl_util.cc"],
    hdrs = ["gl_util.h"],
    visibility = ["//visibility:public"]
)