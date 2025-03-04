# build

```sh
bazelisk build //example:tendis_wasm_example_test.wasm

# aot

wasmedgec bazel-bin/example/tendis_wasm_example_test.wasm bazel-bin/example/tendis_wasm_example_test.wasm.aot
```

# clean

```sh
bazel clean --expunge
```

# wasm run

```sh
wasmedge --reactor bazel-bin/example/tendis_wasm_example_test.wasm.aot tendis_wasm_process 20000
```
