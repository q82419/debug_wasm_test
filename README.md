# wasm_test
wasm test

# macos 14.1 build

```sh
# install bazelisk
brew install bazelisk

# wasm vm build
cd wasm_bazel_example/
bazelisk build //example:run_wasm

# wasm build
cd tendis_wasm_example/
bazelisk build //example:optimus_test.wasm

# wasm aot
wasmedgec bazel-bin/example/optimus_test.wasm bazel-bin/example/optimus_test.wasm.aot

# test

$ ../wasm_bazel_example/bazel-bin/example/run_wasm bazel-bin/example/optimus_test.wasm test ../wasm_bazel_example/100181088_1.bin
define wasm host API  tendis_get_buffer_bytes
define wasm host API  tendis_set_buffer_bytes
loaded wasm plugin
define wasm host API  tendis_get_buffer_bytes
define wasm host API  tendis_set_buffer_bytes
loaded wasm plugin
define wasm host API  tendis_get_buffer_bytes
define wasm host API  tendis_set_buffer_bytes
loaded wasm plugin
define wasm host API  tendis_get_buffer_bytes
define wasm host API  tendis_set_buffer_bytes
loaded wasm plugin
define wasm host API  tendis_get_buffer_bytes
define wasm host API  tendis_set_buffer_bytes
loaded wasm plugin
define wasm host API  tendis_get_buffer_bytes
define wasm host API  tendis_set_buffer_bytes
loaded wasm plugin
test_dispatche_phase ctx id 0
tendis_get_buffer_bytes start ..., ctx_id: 0
tendis_get_buffer_bytes start1 ..., ctx_id: 0
tendis_get_buffer_bytes start2 ..., ctx_id: 0
tendis_get_buffer_bytes start3 ..., ctx_id: 0
run wasm malloc: 16 addr:68280
tendis_get_buffer_bytes start10 ..., ctx_id:
tendis_get_buffer_bytes start ..., ctx_id: 0
tendis_get_buffer_bytes start1 ..., ctx_id: 0
tendis_get_buffer_bytes start2 ..., ctx_id: 0
tendis_get_buffer_bytes start3 ..., ctx_id: 0
run wasm malloc: 16 addr:68304
tendis_get_buffer_bytes start10 ..., ctx_id:
test_dispatche_phase result:
wg wait ok, run time: 0.600291 milliseconds

# wasm aot

$ ../wasm_bazel_example/bazel-bin/example/run_wasm bazel-bin/example/optimus_test.wasm.aot test ../wasm_bazel_example/100181088_1.bin
define wasm host API  tendis_get_buffer_bytes
define wasm host API  tendis_set_buffer_bytes
loaded wasm plugin
define wasm host API  tendis_get_buffer_bytes
define wasm host API  tendis_set_buffer_bytes
loaded wasm plugin
define wasm host API  tendis_get_buffer_bytes
define wasm host API  tendis_set_buffer_bytes
loaded wasm plugin
define wasm host API  tendis_get_buffer_bytes
define wasm host API  tendis_set_buffer_bytes
loaded wasm plugin
define wasm host API  tendis_get_buffer_bytes
define wasm host API  tendis_set_buffer_bytes
loaded wasm plugin
define wasm host API  tendis_get_buffer_bytes
define wasm host API  tendis_set_buffer_bytes
loaded wasm plugin
test_dispatche_phase ctx id 0
tendis_get_buffer_bytes start ..., ctx_id: 0
tendis_get_buffer_bytes start1 ..., ctx_id: 0
tendis_get_buffer_bytes start2 ..., ctx_id: 0
tendis_get_buffer_bytes start3 ..., ctx_id: 0
run wasm malloc: 16 addr:68280
tendis_get_buffer_bytes start10 ..., ctx_id:
[2025-03-04 10:27:12.922] [error] execution failed: out of bounds memory access, Code: 0x408
failed to call function(:tendis_wasm_dispatche_phase) out of bounds memory access
tendis_wasm_dispatche_phase wasm_call failed. res: -1
libc++abi: terminating
Abort trap: 6
```

#ubuntu 22.04 build

```sh
# install bazelisk
wget https://github.com/bazelbuild/bazelisk/releases/download/v1.17.0/bazelisk-linux-arm64
chmod +x bazelisk-linux-arm64
mv bazelisk-linux-arm64 /usr/local/bin/bazelisk
sudo mv bazelisk-linux-arm64 /usr/local/bin/bazelisk
bazelisk --version

# Modify here

wasm_bazel_example/bazel/repositories.bzl
# linux
   #maybe(
   #     http_archive,
   #     name = "com_wasmedge",
   #     sha256 = "6006eed4bf0f4898c3a76e685b1d7eed29c0a5a2b79461ff469490b0b1463dc8",
   #     strip_prefix = "WasmEdge-0.14.1-Linux",
   #     url = "https://github.com/WasmEdge/WasmEdge/releases/download/0.14.1/WasmEdge-0.14.1-ubuntu20.04_aarch64.tar.gz",
   #     build_file = "//bazel:wasmedge.BUILD",  # 指定自定义的 BUILD 文件
   # )


wasm_bazel_example/bazel/wasmedge.BUILD

#srcs = glob(["lib/*.so"]),  # linux


```
