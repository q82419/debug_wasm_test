load("@tendis_wasm_example//bazel:defs.bzl", "tendis_wasm_cc_binary")

licenses(["notice"])  # Apache 2


tendis_wasm_cc_binary(
    name = "optimus_test.wasm",
    srcs = ["optimus.cc",
    "file_bin.h",
    ],
    deps = ["@tendis_wasm_example//:test_protobuf_optimus"],
)
