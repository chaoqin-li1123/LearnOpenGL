load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "spring_mass_shader",
    hdrs = ["spring_mass_shader.h"],
    visibility = ["//visibility:public"],
    deps = [
        "spring_mass_object",
        "//util:program",
    ],
)

cc_library(
    name = "spring_mass_object",
    hdrs = ["spring_mass_object.h"],
    deps = ["//util:object"],
)
