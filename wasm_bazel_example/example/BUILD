
licenses(["notice"])  # Apache 2


cc_library(
    name = "workpool_lib",
    srcs = ["workpool.cc"],   # 实现文件
    hdrs = ["workpool.h"],   # 头文件
    visibility = ["//visibility:public"],  # 允许其他包依赖
)

cc_library(
    name = "wasmedge_lib",
    srcs = ["wasmedge_vm.cc",
        "wasm_api.cc"
    ],   # 实现文件
    hdrs = ["wasmedge_vm.h"],   # 头文件
    deps = ["@com_wasmedge//:wasmedge"],  # 直接依赖wasmedge库
    visibility = ["//visibility:public"],  # 允许其他包依赖
)

cc_binary(
    name = "run_wasm",
    srcs = ["main.cc"],
    deps = [":workpool_lib",
        ":wasmedge_lib",
    ],
)

# 定义一个cc_binary来运行Wasm程序
cc_binary(
    name = "run_wasm_vm_test",
    srcs = ["wasmedge_vm.cc"],
    deps = ["@com_wasmedge//:wasmedge"],  # 直接依赖wasmedge库
)
