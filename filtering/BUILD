cc_library(
    name = "pose_message",
    srcs = [
        "pose_message.cc",
    ],
    hdrs = [
        "pose_message.hh",
    ],
    deps = [
        "@experiments//:eigen",
        "@experiments//:sophus",
        "//infrastructure/comms/schemas:message",
        "//infrastructure/comms/serialization:macros",
        "//infrastructure/time",
    ],
    visibility = ["//visibility:public"],
)
