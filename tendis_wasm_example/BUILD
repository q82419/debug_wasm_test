load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

licenses(["notice"])  # Apache 2

package(default_visibility = ["//visibility:public"])

exports_files(["LICENSE"])


# include full protobuf support
cc_library(
    name = "test_protobuf_optimus",
    hdrs = ["test_protobuf_optimus.h"],
    copts = ["-std=c++17"],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "tendis_wasm_intrinsics_js",
    srcs = [
        "tendis_wasm_intrinsics.js",
    ],
    visibility = ["//visibility:public"],
)
