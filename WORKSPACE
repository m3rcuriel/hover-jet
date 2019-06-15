workspace(name = "hoverjet")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "eigen",
    build_file_content = """
cc_library(
    name = "eigen",
    srcs = glob(["Eigen/src/**/*.h"]),
    hdrs = glob(
        ["Eigen/*"],
        exclude = [
            "Eigen/CholmodSupport",
            "Eigen/MetisSupport",
            "Eigen/PaStiXSupport",
            "Eigen/PardisoSupport",
            "Eigen/SPQRSupport",
            "Eigen/SuperLUSupport",
            "Eigen/UmfPackSupport",
        ],
    ) + ["unsupported/Eigen/MatrixFunctions"] + glob([
        "unsupported/Eigen/src/MatrixFunctions/*.h",
    ]),
    includes = ["."],
    visibility = ["//visibility:public"],
)
""",
    strip_prefix = "eigen-eigen-323c052e1731",
    urls = [ "http://bitbucket.org/eigen/eigen/get/3.3.7.tar.gz" ],
)

http_archive(
    name = "sophus",
    build_file_content = """
cc_library(
    name = "sophus",
    hdrs = glob(["sophus/**/*.hpp"]),
    includes = ["."],
    visibility = ["//visibility:public"],
)
""",
    strip_prefix = "Sophus-d400e5cb7160740084f3f76332a8b8bbd34ddae8",
    urls = [ "https://github.com/strasdat/Sophus/archive/d400e5cb7160740084f3f76332a8b8bbd34ddae8.tar.gz" ],
)
