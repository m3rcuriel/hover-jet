cc_library(
    name = "comm_library",
    srcs = [
        "mqtt_comms_factory.cc",
        "mqtt_publisher.cc",
        "mqtt_subscriber.cc",
    ],
    hdrs = [
        "comms_factory.hh",
        "publisher.hh",
        "subscriber.hh",
        "mqtt_subscriber.hh",
        "mqtt_publisher.hh",
        "mqtt_comms_factory.hh",
    ],
    deps = [
        "//infrastructure/comms/schemas:message",
        "//infrastructure/comms/serialization:macros",
        "//infrastructure/time:time",
        "@mqtt-cpp//:mqtt",
        "@crossguid//:crossguid",
    ],
    visibility = ["//visibility:public"],
)
