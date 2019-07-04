load("//tools/rules:balsaq.bzl", "bq_binary")

cc_library(
    name = "control_utilities",
    srcs = ["control_utilities.cc"],
    hdrs = ["control_utilities.hh"],
    deps = [
        "@experiments//:eigen",
        "@experiments//:sophus",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "vanes_generated",
    srcs = ["vanes_generated.cc"],
    hdrs = ["vanes_generated.hh"],
    deps = [
        "@experiments//:eigen",
    ],
)

cc_library(
    name = "wrench_generated",
    srcs = ["wrench_generated.cc"],
    hdrs = ["wrench_generated.hh"],
    deps = [
        "@experiments//:eigen",
    ],
)

cc_library(
    name = "wrench",
    srcs = ["wrench.cc"],
    hdrs = ["wrench.hh"],
    deps = [
        "@experiments//:eigen",
        "@experiments//:sophus",
        "@experiments//:eigen_helpers",
        ":wrench_generated",
    ],
)

cc_library(
    name = "jet_vane_model",
    srcs = ["jet_vane_model.cc"],
    hdrs = ["jet_vane_model.hh"],
    deps = [
        "@experiments//:eigen",
        "@experiments//:eigen_helpers",
        "@experiments//:sophus",
        ":wrench",
    ],
)

cc_library(
    name = "quadraframe_model",
    srcs = ["quadraframe_model.cc"],
    hdrs = ["quadraframe_model.hh"],
    deps = [
        ":vanes_generated",
        ":wrench",
        ":jet_vane_model",
    ],
)

cc_library(
    name = "jet_vane_mapper",
    srcs = ["jet_vane_mapper.cc"],
    hdrs = ["jet_vane_mapper.hh"],
    deps = [
        ":wrench",
        ":vanes_generated",
        ":quadraframe_model",
        "@experiments//:numerics",
    ],
)

cc_library(
    name = "servo_interface",
    srcs = [
        "servo_interface.cc",
    ],
    hdrs = [
        "servo_interface.hh",
    ],
    deps = [
        ":vanes_generated",
        "//embedded/servo_bq:set_servo_message",
        "//infrastructure/comms/schemas:message",
        "//infrastructure/comms/serialization:macros",
        "//infrastructure/time",
    ],
)

bq_binary(
    name = "controller_bq",
    srcs = [
        "controller_balsaq.cc",
        "controller_balsaq.hh",
    ],
    deps = [
        "@experiments//:time_point",
        "//infrastructure/balsa_queue:balsaqs",
        ":quadraframe_model",
        ":control_utilities",
        ":jet_vane_mapper",
        ":servo_interface",
        "//filtering:pose_message",
        "//infrastructure/engine:engine_messages",
        "//infrastructure/engine:schemas",
    ],
)
