#G########################################################################
# File Name: optimus_run.sh
# Author: Liupd
# mail: liupeidong0620@163.com
# Created Time: 一  2/24 16:55:34 2025
#########################################################################
#!/bin/bash

for i in {1..10}
do
    /Users/david24.liu/liu-code/wasm/WasmEdge-0.14.1-Darwin/bin/wasmedge --reactor bazel-bin/example/optimus_test.wasm.aot tendis_wasm_process 2 6
    sleep 1
done
