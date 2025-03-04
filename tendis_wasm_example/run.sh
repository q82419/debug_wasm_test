#########################################################################
# File Name: run.sh
# Author: Liupd
# mail: liupeidong0620@163.com
# Created Time: 四  2/13 14:54:22 2025
#########################################################################
#!/bin/bash

for i in {1..20}
do
    wasmedge --reactor bazel-bin/example/tendis_wasm_example_test.wasm.aot tendis_wasm_process 1
    sleep 1
done
