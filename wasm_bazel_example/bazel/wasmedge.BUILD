
cc_library(
    name = "wasmedge",
    srcs = glob(["lib/*.dylib"]),  # macos
    #srcs = glob(["lib/*.so"]),  # linux
    hdrs = glob(["include/wasmedge/**"]),  # 匹配 include/wasmedge 目录下的所有头文件
    includes = ["include"],  # 头文件搜索路径
    visibility = ["//visibility:public"],
)
