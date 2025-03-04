#pragma once

#include <wasmedge/wasmedge.h>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>
#include <memory>

#define TENDIS_BUFFER_TYPE_PLUGIN_USER_DATA 1
#define TENDIS_BUFFER_TYPE_PLUGIN_GET_VAL 2
#define TENDIS_BUFFER_TYPE_PLUGIN_SET_RESP 3

int32_t
tendis_get_buffer_bytes(int32_t ctxId, int32_t type,
                       int32_t addr, int32_t size_addr);
int32_t
tendis_set_buffer_bytes(int32_t ctxId, int32_t type,
                       int32_t body, int32_t bodySize);

std::string readFileToString(const std::string& filename);

typedef struct {
    WasmEdge_ModuleInstanceContext *module;
    WasmEdge_StoreContext          *store;
    WasmEdge_ExecutorContext       *exec;
    WasmEdge_MemoryInstanceContext *memory;
    /* need to ensure the import objects have the same lifecycle as plugin */
    WasmEdge_ModuleInstanceContext *import;
    WasmEdge_ModuleInstanceContext *import_wasi;
} wasm_wasmedge_plugin_t;

#define MAX_WASM_API_ARG  7

#define TENDIS_WASM_PARAM_VOID                 1
#define TENDIS_WASM_PARAM_I32                  2
#define TENDIS_WASM_PARAM_I32_I32              3
#define TENDIS_WASM_PARAM_I32_I32_I32          4
#define TENDIS_WASM_PARAM_I32_I32_I32_I32      5
#define TENDIS_WASM_PARAM_I32_I32_I32_I32_I32  6

typedef struct {
    std::string              name;
    WasmEdge_HostFunc_t      cb;
    int8_t                   param_num;
    WasmEdge_ValType    param_type[MAX_WASM_API_ARG];
} wasm_wasmedge_host_api_t;

class WasmedgeVM {
public:
    WasmedgeVM() {}
    int load(std::string& wasm_file, std::string& wasm_name); // return wasm_id
    int32_t wasm_call(std::string func_name, bool has_result, int param_type, ...);

    int32_t wasm_memory_alloc(int32_t size);
    char* wasm_get_memory(int32_t addr, int32_t size);

    ~WasmedgeVM();

    WasmEdge_FunctionTypeContext *wasmedge_host_api_func(const wasm_wasmedge_host_api_t *api);

    void setCtxId(int32_t wasm_ctx_id) {
        wasm_ctx_id_ = wasm_ctx_id;
    }
    int32_t getCtxId() {
        return wasm_ctx_id_;
    }
    std::string& wasm_name() {
        return wasm_name_;
    }
private:
    wasm_wasmedge_plugin_t* plugin;
    int32_t wasm_ctx_id_ = 0;
    std::string wasm_name_;
};

class WasmedgeVMManager {
public:
    WasmedgeVMManager(int32_t vm_num) : vm_num_(vm_num) {}
    ~WasmedgeVMManager() {}

    int32_t load(std::string& wasm_file, std::string& wasm_name);
    
    std::shared_ptr<WasmedgeVM> pop_wasm_vm(std::string& wasm_name);
    void push_wasm_vm(std::shared_ptr<WasmedgeVM> vm);
private:
    std::mutex mtx_;
    int32_t wasm_ctx_id_alloc_ = 0;
    int32_t vm_num_ = 0;
    std::map<std::string, std::queue<std::shared_ptr<WasmedgeVM>>> vms_;
};


#define TENDIS_WASM_RUN_PHASE_DISPATCHE 1
#define TENDIS_WASM_RUN_PHASE_PARALLEL_EXEC 2
#define TENDIS_WASM_RUN_PHASE_MERGE 3

#define TENDIS_WASM_BUFFER_TYPE_LOG 1
#define TENDIS_WASM_BUFFER_TYPE_CONF 2
#define TENDIS_WASM_BUFFER_TYPE_REQUEST 3
#define TENDIS_WASM_BUFFER_TYPE_RESULT 4

struct wasm_phase_data_t {
    std::shared_ptr<WasmedgeVM> vm;
    int32_t type;
    int32_t ctx_id;

    std::string_view conf;
    std::string_view request_data;
    std::string result_data;
};

struct wasm_phase_ctx_t {
    std::mutex mtx_;
    std::map<int32_t, std::shared_ptr<wasm_phase_data_t>> ctxs_;

    std::shared_ptr<wasm_phase_data_t> getCtx(int32_t ctx_id) {
        //std::cout << "------- getCtx: ctxs_.size: " << ctxs_.size() << std::endl;
        std::lock_guard<std::mutex> lk(mtx_);
        auto it = ctxs_.find(ctx_id);
        if (it == ctxs_.end()) return nullptr;
        return it->second;
    }
    void setCtx(std::shared_ptr<wasm_phase_data_t> data) {
        std::lock_guard<std::mutex> lk(mtx_);
        ctxs_[data->ctx_id] = data;
        //std::cout << "------- setCtx: " << data->ctx_id << " ctxs_.size: " << ctxs_.size() << std::endl;
    }
    void delCtx(int32_t ctx_id) {
        //std::cout << "------ delCtx:" << ctx_id << std::endl;
        std::lock_guard<std::mutex> lk(mtx_);
        ctxs_.erase(ctx_id);
    }
};


extern wasm_phase_ctx_t g_ctx_;
