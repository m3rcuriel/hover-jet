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

http_archive(
    name = "com_github_google_googletest",
    strip_prefix = "googletest-f7c178ecb33c92763fa41d4999db30aaf43a6b30",
    sha256 = "8a3f7335effa896476bbb804dc95cc66feb588f55e9a284f992fbed9408fe9ce",
    urls = ["https://github.com/google/googletest/archive/f7c178ecb33c92763fa41d4999db30aaf43a6b30.tar.gz" ],
)

http_archive(
    name = "experiments",
    strip_prefix = "experiments-c056c6c7503d087266e871fb68104d58c2fbf6b6",
    build_file = "//third_party:experiments.BUILD",
    patches = ["//third_party:experiments.patch"],
    patch_args = ["-p1"],
    sha256 = "b45b0d0a38d99b7cc842554d9c32ede94890fe088712c535e36f8098874cdb5d",
    urls = [ "https://github.com/jpanikulam/experiments/archive/c056c6c7503d087266e871fb68104d58c2fbf6b6.tar.gz" ],
)

http_archive(
    name = "yaml-cpp",
    build_file_content = """
cc_library(
    name = "yaml",
    srcs = glob(["src/*.h", "src/*.cpp"]),
    hdrs = glob(["include/yaml-cpp/**/*.h"]),
    includes = ["include"],
    visibility = ["//visibility:public"],
)
""",
    strip_prefix = "yaml-cpp-012269756149ae99745b6dafefd415843d7420bb",
    urls = [ "https://github.com/jbeder/yaml-cpp/archive/012269756149ae99745b6dafefd415843d7420bb.tar.gz" ],
)

http_archive(
    name = "mqtt-cpp",
    build_file_content = """
cc_library(
    name = "mqtt",
    srcs = glob(["src/*.cpp"]),
    hdrs = glob(["src/mqtt/*.h"]),
    includes = ["src"],
    visibility = ["//visibility:public"],
    deps = [
        "@mqtt-c//:mqtt-c",
    ],
)
""",
    strip_prefix = "paho.mqtt.cpp-f134e927f7a4e1032e56babbbd89d54b8cd9991b",
    urls = [ "https://github.com/eclipse/paho.mqtt.cpp/archive/f134e927f7a4e1032e56babbbd89d54b8cd9991b.tar.gz" ],
)

http_archive(
    name = "mqtt-c",
    build_file_content = """
cc_library(
    name = "mqtt-c",
    srcs = glob(["src/*.c"]),
    hdrs = glob(["src/*.h"]),
    linkopts = ["-lpthread"],
    includes = ["src"],
    visibility = ["//visibility:public"],
)
""",
    patches = [ "@//third_party:mqtt.c.patch" ],
    strip_prefix = "paho.mqtt.c-7e9b814bfb81d1edc32d8cef3594d5265ffb2395",
    urls = [ "https://github.com/eclipse/paho.mqtt.c/archive/7e9b814bfb81d1edc32d8cef3594d5265ffb2395.tar.gz" ],
)

http_archive(
    name = "crossguid",
    build_file_content = """
cc_library(
    name = "crossguid",
    srcs = [
        "src/guid.cpp"
    ],
    defines = ["GUID_LIBUUID=1"],
    hdrs = [
        "include/crossguid/guid.hpp",
    ],
    includes = [ "include" ],
    visibility = ["//visibility:public"],
)
""",
    strip_prefix = "crossguid-ca1bf4b810e2d188d04cb6286f957008ee1b7681",
    urls = [ "https://github.com/graeme-hill/crossguid/archive/ca1bf4b810e2d188d04cb6286f957008ee1b7681.tar.gz" ],
)

http_archive(
    name = "libnop",
    sha256 = "b6eeaf5f0dc49a189af1f6283418a003d470982bfff4b675ffa743bf52140d74",
    build_file_content = """
cc_library(
    name = "nop",
    hdrs = glob(["include/nop/**/*.h"]),
    strip_include_prefix = "include",
    include_prefix = "third_party",
    includes = [ "_virtual_includes/nop/third_party" ],
    visibility = ["@//infrastructure/comms/serialization:__subpackages__"],
)
""",
    strip_prefix = "libnop-49084b72fe10fa18ce64c7540062651dd0212485",
    urls = [ "https://github.com/google/libnop/archive/49084b72fe10fa18ce64c7540062651dd0212485.tar.gz" ],
)
