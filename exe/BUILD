load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    linkopts = [
        "-lGLEW",
        "-lglfw",
        "-lGL",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//blinn_phong:blinn_phong_shader",
        "//checkboard:checkboard_shader",
        "//spring_mass:spring_mass_shader",
    ],
)
