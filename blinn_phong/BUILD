load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "blinn_phong_shader",
    hdrs = ["blinn_phong_shader.h"],
    visibility = ["//visibility:public"],
    deps = [
        "blinn_phong_object",
        "//util:curve",
        "//util:gl_util",
        "//util:light",
        "//util:program",
        "//util:texture",
        "//util:transformation",
    ],
)

cc_library(
    name = "blinn_phong_object",
    hdrs = ["blinn_phong_object.h"],
    deps = [
        "//util:gl_util",
        "//util:object",
    ],
)
