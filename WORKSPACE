load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "eigen",
    build_file = "//src:eigen.BUILD",
    sha256 = "d56fbad95abf993f8af608484729e3d87ef611dd85b3380a8bad1d5cbc373a57",
    strip_prefix = "eigen-3.3.7",
    urls = [
        "https://gitlab.com/libeigen/eigen/-/archive/3.3.7/eigen-3.3.7.tar.gz",
        "http://vertexwahn.de/artifacts/eigen-3.3.7.tar.gz",
    ],
)

all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

http_archive(
    name = "opencv",
    build_file_content = all_content,
    strip_prefix = "opencv-4.5.1",
    urls = ["https://github.com/opencv/opencv/archive/4.5.1.zip"],
)

http_archive(
    name = "rules_foreign_cc",
    strip_prefix = "rules_foreign_cc-master",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/master.zip",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies()