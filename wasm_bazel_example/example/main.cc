#include "workpool.h"
#include <iostream>
#include <chrono>

#include "wasmedge_vm.h"

class run_test {
public:
    run_test(std::string wasm_file, std::string wasm_name, std::string data_file, int vmNum) {
        wasm_name_ = wasm_name;
        vmMag_ = new WasmedgeVMManager(vmNum);
        if(vmMag_->load(wasm_file, wasm_name) < 0) {
            std::cout << "wasm load failed" << std::endl;
            throw;
        }
        data_file_ = readFileToString(data_file);
    }
    ~run_test() {}

    void test_dispatche_phase() {
        auto vm = vmMag_->pop_wasm_vm(wasm_name_);
        auto wasm_dat = std::make_shared<wasm_phase_data_t>();
        wasm_dat->vm = vm;
        wasm_dat->ctx_id = vm->getCtxId();
        std::cout << "test_dispatche_phase ctx id " <<  wasm_dat->ctx_id << std::endl;
        wasm_dat->request_data = "meta,1,2,3,4,5,6";
        wasm_dat->type = TENDIS_WASM_RUN_PHASE_DISPATCHE;

        g_ctx_.setCtx(wasm_dat);
        // todo
        int32_t res = vm->wasm_call("tendis_wasm_dispatche_phase", true, TENDIS_WASM_PARAM_I32, wasm_dat->ctx_id);
        if (res != 0) {
            std::cout << "tendis_wasm_dispatche_phase wasm_call failed. res: " << res << std::endl;
            throw;
        }
        // todo
        std::cout << "test_dispatche_phase result: " << wasm_dat->result_data << std::endl;

        g_ctx_.delCtx(wasm_dat->ctx_id);
        vmMag_->push_wasm_vm(vm);
    }

    void test_parallel_exec_phase() {
        auto vm = vmMag_->pop_wasm_vm(wasm_name_);
        auto wasm_dat = std::make_shared<wasm_phase_data_t>();
        wasm_dat->vm = vm;
        wasm_dat->ctx_id = vm->getCtxId();
        wasm_dat->request_data = data_file_;
        wasm_dat->type = TENDIS_WASM_RUN_PHASE_PARALLEL_EXEC;
        g_ctx_.setCtx(wasm_dat);

        int32_t res = vm->wasm_call("tendis_wasm_exec_phase", true, TENDIS_WASM_PARAM_I32, wasm_dat->ctx_id);
        if (res != 0) {
            std::cout << "wasm_call failed: " << res << std::endl;
            throw;
        }
        if (wasm_dat->result_data.size() == 0) {
            std::cout << "test_parallel_exec_phase result_data is null" << std::endl;
        } /*else {
            std::cout << "test_parallel_exec_phase result data size: " << wasm_dat->result_data.size() << std::endl;
        }*/
        g_ctx_.delCtx(wasm_dat->ctx_id);
        vmMag_->push_wasm_vm(vm);
    }

    void test_merge_phase() {
    // todo
    }
private:
    WasmedgeVMManager* vmMag_;
    std::string wasm_name_;

    std::string data_file_;
};



int main(int argc, char** argv) {
    if (argc < 4) {
        std::cout << argv[0] << " wasm_file wasm_name data_file" << std::endl;
        return -1;
    }
    int threadNum = 6;
    run_test test(argv[1], argv[2], argv[3], threadNum);

    WaitGroup wg;
    // 创建包含 4 个工作线程的线程池
    ThreadPool pool(threadNum);

    auto start = std::chrono::high_resolution_clock::now();
    wg.Add(threadNum);
    test.test_dispatche_phase();
    // 提交任务到线程池
    for (int i = 0; i < threadNum; ++i) {
        pool.enqueue([&test, &wg] {
            //test.test_parallel_exec_phase();
            wg.Done();
        });
    }

    wg.Wait();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_ms = end - start;

    std::cout << "wg wait ok, run time: " << duration_ms.count() << " milliseconds" << std::endl;

    // 注意：实际使用时需要确保任务在析构前完成
    // 这里为了演示简单，直接立即析构（可能需要适当延时）
    return 0;
}
