load("//tools/rules:balsaq.bzl", "bq_binary")

cc_library(
    name = "client_timesync_message",
    hdrs = [
        "client_timesync_message.hh",
    ],
)

bq_binary(
    name = "timesync_client_bq",
    srcs = [
        "timesync_client_bq.cc",
        "timesync_client_bq.hh",
    ],
    deps = [
        "//infrastructure/balsa_queue:balsaqs",
        ":client_timesync_message",
    ],
)

bq_binary(
    name = "timesync_master_bq",
    srcs = [
        "timesync_master_bq.cc",
        "timesync_master_bq.hh",
    ],
    deps = [
        "//infrastructure/balsa_queue:balsaqs",
        ":client_timesync_message",
    ],
)
