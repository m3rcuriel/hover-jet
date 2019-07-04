cc_library(
    name = "eigen",
    hdrs = ["eigen.hh"],
    visibility = ["//visibility:public"],
    include_prefix = "third_party/experiments",
    includes = [ "_virtual_includes/eigen/third_party/experiments" ],
    deps = ["@eigen"],
)

cc_library(
    name = "eigen_helpers",
    hdrs = ["eigen_helpers.hh"],
    visibility = ["//visibility:public"],
    include_prefix = "third_party/experiments",
    includes = [ "_virtual_includes/eigen_helpers/third_party/experiments" ],
    deps = [":eigen"],
)

cc_library(
    name = "sophus",
    hdrs = ["sophus.hh"],
    include_prefix = "third_party/experiments",
    includes = [ "_virtual_includes/eigen/third_party/experiments" ],
    visibility = ["//visibility:public"],
    deps = ["@sophus"],
)

cc_library(
    name = "numerics",
    srcs = glob(["numerics/*.cc"],
        exclude = [
            "numerics/conjugate_gradient_test.cc",
            "numerics/gradient_descent_test.cc",
            "numerics/numdiff_test.cc",
            "numerics/gauss_newton_test.cc",
            "numerics/nt_gauss_newton_test.cc",
            "numerics/jacobi_laplacian_test.cc",
            "numerics/optimize_test.cc",
            "numerics/covariance_test.cc",
            "numerics/nt_gauss_newton.cc",
        ]),
    hdrs = glob(["numerics/*.hh"],
        exclude = [
            "numerics/nt_gauss_newton.hh",
        ]),
    include_prefix = "third_party/experiments",
    includes = [ "_virtual_includes/numerics/third_party/experiments/numerics" ],
    deps = [
        ":eigen",
        ":out",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "time_point",
    hdrs = ["estimation/time_point.hh"],
    include_prefix = "third_party/experiments",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "out",
    hdrs = ["out.hh"],
    include_prefix = "third_party/experiments",
    includes = [ "_virtual_includes/out/third_party/experiments" ],
)
