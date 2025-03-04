#include "wasmedge_vm.h"

#include <iostream>
#include <fstream>
#include <sstream>

 #include <stdarg.h>

#define DEFINE_WASM_NAME_ARG_VOID \
    0, {}
#define DEFINE_WASM_API_ARG_CHECK_VOID(NAME) \
    int32_t res = NAME();

#define DEFINE_WASM_NAME_ARG_I32_1 \
    1,                             \
    {                              \
        WasmEdge_ValTypeGenI32(),      \
    }
#define DEFINE_WASM_API_ARG_CHECK_I32_1(NAME) \
    int32_t p0 = WasmEdge_ValueGetI32(In[0]); \
    int32_t res = NAME(p0);

#define DEFINE_WASM_NAME_ARG_I32_2                  \
    2,                                              \
    {                                               \
        WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), \
    }
#define DEFINE_WASM_API_ARG_CHECK_I32_2(NAME) \
    int32_t p0 = WasmEdge_ValueGetI32(In[0]); \
    int32_t p1 = WasmEdge_ValueGetI32(In[1]); \
    int32_t res = NAME(p0, p1);

#define DEFINE_WASM_NAME_ARG_I32_3                                        \
    3,                                                                    \
    {                                                                     \
        WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), \
    }
#define DEFINE_WASM_API_ARG_CHECK_I32_3(NAME) \
    int32_t p0 = WasmEdge_ValueGetI32(In[0]); \
    int32_t p1 = WasmEdge_ValueGetI32(In[1]); \
    int32_t p2 = WasmEdge_ValueGetI32(In[2]); \
    int32_t res = NAME(p0, p1, p2);

#define DEFINE_WASM_NAME_ARG_I32_4                                                              \
    4,                                                                                          \
    {                                                                                           \
        WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), \
    }
#define DEFINE_WASM_API_ARG_CHECK_I32_4(NAME) \
    int32_t p0 = WasmEdge_ValueGetI32(In[0]); \
    int32_t p1 = WasmEdge_ValueGetI32(In[1]); \
    int32_t p2 = WasmEdge_ValueGetI32(In[2]); \
    int32_t p3 = WasmEdge_ValueGetI32(In[3]); \
    int32_t res = NAME(p0, p1, p2, p3);

#define DEFINE_WASM_NAME_ARG_I32_5                                                                                    \
    5,                                                                                                                \
    {                                                                                                                 \
        WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), \
    }
#define DEFINE_WASM_API_ARG_CHECK_I32_5(NAME) \
    int32_t p0 = WasmEdge_ValueGetI32(In[0]); \
    int32_t p1 = WasmEdge_ValueGetI32(In[1]); \
    int32_t p2 = WasmEdge_ValueGetI32(In[2]); \
    int32_t p3 = WasmEdge_ValueGetI32(In[3]); \
    int32_t p4 = WasmEdge_ValueGetI32(In[4]); \
    int32_t res = NAME(p0, p1, p2, p3, p4);

#define DEFINE_WASM_NAME_ARG_I32_6                                                                                    \
    6,                                                                                                                \
    {                                                                                                                 \
        WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), \
            WasmEdge_ValTypeGenI32(),                                                                                     \
    }
#define DEFINE_WASM_API_ARG_CHECK_I32_6(NAME) \
    int32_t p0 = WasmEdge_ValueGetI32(In[0]); \
    int32_t p1 = WasmEdge_ValueGetI32(In[1]); \
    int32_t p2 = WasmEdge_ValueGetI32(In[2]); \
    int32_t p3 = WasmEdge_ValueGetI32(In[3]); \
    int32_t p4 = WasmEdge_ValueGetI32(In[4]); \
    int32_t p5 = WasmEdge_ValueGetI32(In[5]); \
    int32_t res = NAME(p0, p1, p2, p3, p4, p5);

#define DEFINE_WASM_NAME_ARG_I32_7                                                                                    \
    7,                                                                                                                \
    {                                                                                                                 \
        WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(), \
            WasmEdge_ValTypeGenI32(), WasmEdge_ValTypeGenI32(),                                                               \
    }
#define DEFINE_WASM_API_ARG_CHECK_I32_7(NAME) \
    int32_t p0 = WasmEdge_ValueGetI32(In[0]); \
    int32_t p1 = WasmEdge_ValueGetI32(In[1]); \
    int32_t p2 = WasmEdge_ValueGetI32(In[2]); \
    int32_t p3 = WasmEdge_ValueGetI32(In[3]); \
    int32_t p4 = WasmEdge_ValueGetI32(In[4]); \
    int32_t p5 = WasmEdge_ValueGetI32(In[5]); \
    int32_t p6 = WasmEdge_ValueGetI32(In[6]); \
    int32_t res = NAME(p0, p1, p2, p3, p4, p5, p6);


#define DEFINE_WASM_API(NAME, ARG_CHECK)        \
    static WasmEdge_Result wasmedge_##NAME(     \
        void *Data,                             \
        const WasmEdge_CallingFrameContext *CallFrameCxt, \
        const WasmEdge_Value *In,               \
        WasmEdge_Value *Out)                    \
    {                                           \
        ARG_CHECK                               \
        Out[0] = WasmEdge_ValueGenI32(res);     \
        return WasmEdge_Result_Success;         \
    }

DEFINE_WASM_API(tendis_get_buffer_bytes,
                DEFINE_WASM_API_ARG_CHECK_I32_4(tendis_get_buffer_bytes))

DEFINE_WASM_API(tendis_set_buffer_bytes,
                DEFINE_WASM_API_ARG_CHECK_I32_4(tendis_set_buffer_bytes))

#define DEFINE_WASM_NAME(NAME, ARG) \
    {#NAME, wasmedge_##NAME, ARG},

static wasm_wasmedge_host_api_t host_apis[] = {
    DEFINE_WASM_NAME(tendis_get_buffer_bytes, DEFINE_WASM_NAME_ARG_I32_4)
    DEFINE_WASM_NAME(tendis_set_buffer_bytes, DEFINE_WASM_NAME_ARG_I32_4)
    { "", NULL, 0, {} }
};


int WasmedgeVM::load(std::string &bytecode, std::string &wasm_name)
{
    size_t i;
    WasmEdge_Result res;
    WasmEdge_ASTModuleContext *ast_ctx = NULL;
    WasmEdge_StoreContext *store_ctx;
    WasmEdge_LoaderContext *loader;
    WasmEdge_ValidatorContext *validator;
    WasmEdge_ModuleInstanceContext *import;
    WasmEdge_ModuleInstanceContext *import_wasi = NULL;
    WasmEdge_ModuleInstanceContext *module = NULL;
    WasmEdge_ExecutorContext *executor;
    WasmEdge_MemoryInstanceContext *memory;
    WasmEdge_String s;
    plugin = new wasm_wasmedge_plugin_t;
    wasm_name_ = wasm_name;

    /* Create the configure context */
    store_ctx = WasmEdge_StoreCreate();
    if (store_ctx == NULL)
    {
        return -1;
    }

    loader = WasmEdge_LoaderCreate(NULL);
    if (loader == NULL)
    {
        return -1;
    }

    validator = WasmEdge_ValidatorCreate(NULL);
    if (validator == NULL)
    {
        return -1;
    }

    executor = WasmEdge_ExecutorCreate(NULL, NULL);
    if (executor == NULL)
    {
        return -1;
    }

    res = WasmEdge_LoaderParseFromBuffer(loader, &ast_ctx, (const uint8_t *)bytecode.c_str(), bytecode.size());
    if (!WasmEdge_ResultOK(res))
    {
        std::cout << "Loading phase failed: " << WasmEdge_ResultGetMessage(res) << std::endl;
        return -1;
    }

    res = WasmEdge_ValidatorValidate(validator, ast_ctx);
    if (!WasmEdge_ResultOK(res))
    {
        std::cout << "Validation phase failed: " << WasmEdge_ResultGetMessage(res) << std::endl;
        return -1;
    }

    s = WasmEdge_StringCreateByCString("env");
    import = WasmEdge_ModuleInstanceCreate(s);
    WasmEdge_StringDelete(s);

    if (import == NULL)
    {
        return -1;
    }

    for (i = 0; host_apis[i].name.size(); i++)
    {
        wasm_wasmedge_host_api_t *api = &host_apis[i];
        WasmEdge_FunctionTypeContext *ft;
        WasmEdge_FunctionInstanceContext *f;

        std::cout << "define wasm host API  " << api->name << std::endl;

        ft = wasmedge_host_api_func(api);
        if (ft == NULL)
        {
            return -1;
        }

        f = WasmEdge_FunctionInstanceCreate(ft, api->cb, NULL, 0);
        if (f == NULL)
        {
            return -1;
        }

        s = WasmEdge_StringCreateByBuffer((const char *)api->name.c_str(), api->name.size());
        /* The caller should __NOT__ access or delete the function instance context
         * after calling this function.
         */
        WasmEdge_ModuleInstanceAddFunction(import, s, f);
        WasmEdge_StringDelete(s);
        WasmEdge_FunctionTypeDelete(ft);
    }

    res = WasmEdge_ExecutorRegisterImport(executor, store_ctx, import);
    if (!WasmEdge_ResultOK(res))
    {
        std::cout << "Register imports failed: " << WasmEdge_ResultGetMessage(res) << std::endl;
        return -1;
    }

    // TODO: add env
    import_wasi = WasmEdge_ModuleInstanceCreateWASI(NULL, 0, NULL, 0, NULL, 0);
    res = WasmEdge_ExecutorRegisterImport(executor, store_ctx, import_wasi);
    if (!WasmEdge_ResultOK(res))
    {
        std::cout << "Register wasi imports failed: " << WasmEdge_ResultGetMessage(res) << std::endl;
        return -1;
    }

    res = WasmEdge_ExecutorInstantiate(executor, &module, store_ctx, ast_ctx);
    if (!WasmEdge_ResultOK(res))
    {
        std::cout << "Instantiation phase failed: %s" << WasmEdge_ResultGetMessage(res) << std::endl;
        return -1;
    }

    s = WasmEdge_StringCreateByCString("memory");
    memory = WasmEdge_ModuleInstanceFindMemory(module, s);
    WasmEdge_StringDelete(s);
    if (memory == NULL)
    {
        std::cout << "the wasm plugin doesn't export memory" << std::endl;
        return -1;
    }

    plugin->exec = executor;
    plugin->module = module;
    plugin->store = store_ctx;
    plugin->memory = memory;
    plugin->import = import;
    plugin->import_wasi = import_wasi;

    WasmEdge_ASTModuleDelete(ast_ctx);
    WasmEdge_ValidatorDelete(validator);
    WasmEdge_LoaderDelete(loader);

    std::cout << "loaded wasm plugin" << std::endl;

    return 0;
}

WasmEdge_FunctionTypeContext *
WasmedgeVM::wasmedge_host_api_func(const wasm_wasmedge_host_api_t *api)
{
    WasmEdge_ValType result[1] = {WasmEdge_ValTypeGenI32()};

    return WasmEdge_FunctionTypeCreate(api->param_type, api->param_num, result, 1);
}

WasmedgeVM::~WasmedgeVM() {
    WasmEdge_ModuleInstanceDelete(plugin->module);
    WasmEdge_ExecutorDelete(plugin->exec);
    WasmEdge_StoreDelete(plugin->store);
    WasmEdge_ModuleInstanceDelete(plugin->import);
    WasmEdge_ModuleInstanceDelete(plugin->import_wasi);
    free(plugin);
    std::cout << "unloaded wasm plugin: " << wasm_name_ << std::endl;
}

int32_t WasmedgeVM::wasm_call(std::string func_name, bool has_result, int param_type, ...)
{
    WasmEdge_FunctionInstanceContext *finst = NULL;
    WasmEdge_Result res;
    WasmEdge_String s;
    int rc;
    size_t i;
    va_list args;
    size_t param_num = 0;
    WasmEdge_Value param_list[MAX_WASM_API_ARG];
    WasmEdge_Value results[1];

    va_start(args, param_type);

    switch (param_type)
    {
    case TENDIS_WASM_PARAM_VOID:
        break;

    case TENDIS_WASM_PARAM_I32:
        param_num = 1;
        break;

    case TENDIS_WASM_PARAM_I32_I32:
        param_num = 2;
        break;

    case TENDIS_WASM_PARAM_I32_I32_I32:
        param_num = 3;
        break;

    case TENDIS_WASM_PARAM_I32_I32_I32_I32:
        param_num = 4;
        break;

    case TENDIS_WASM_PARAM_I32_I32_I32_I32_I32:
        param_num = 5;
        break;

    default:
        std::cout << "unknown param type: " << param_type << std::endl;
        va_end(args);
        return -1;
    }

    for (i = 0; i < param_num; i++)
    {
        param_list[i] = WasmEdge_ValueGenI32(va_arg(args, int32_t));
    }

    va_end(args);
    //std::cout << "call param_num " << param_num << std::endl;
    s = WasmEdge_StringCreateByBuffer((const char *)func_name.c_str(), func_name.size());
    //std::cout << "call param_num 1 " << param_num << std::endl;
    finst = WasmEdge_ModuleInstanceFindFunction(plugin->module, s);
    //std::cout << "call exec " << std::endl;
    res = WasmEdge_ExecutorInvoke(plugin->exec, finst,
                                  param_list, param_num, results, has_result ? 1 : 0);
    //std::cout << "call exec1 " << std::endl;
    WasmEdge_StringDelete(s);
    //std::cout << "call param_num ok" << std::endl;
    if (!WasmEdge_ResultOK(res))
    {
        std::cout << "failed to call function(:" << func_name << ") " << WasmEdge_ResultGetMessage(res) << std::endl;
        return -1;
    }

    if (!has_result)
    {
        return 0;
    }

    rc = WasmEdge_ValueGetI32(results[0]);

    return rc;
}


static std::string exported_malloc = "malloc";
int32_t WasmedgeVM::wasm_memory_alloc(int32_t size)
{
    int32_t addr;
    addr = wasm_call(exported_malloc, true, TENDIS_WASM_PARAM_I32, size);

    if (addr == 0)
    {
        std::cout << "failed to malloc" << std::endl;
        return 0;
    }
    std::cout << "run wasm malloc: " << size << " addr:" << addr << std::endl;

    return addr;
}

char *WasmedgeVM::wasm_get_memory(int32_t addr, int32_t size)
{
    uint8_t* data;

    /* If the `addr + size` is larger, than the data size in the memory instance,
     * this function will return NULL. */
    data = WasmEdge_MemoryInstanceGetPointer(plugin->memory, addr, size);
    if (data == NULL)
    {
        std::cout << "wasmedge failed to access memory addr " << addr << " with size " << std::endl;
    }

    return (char *)data;
}


std::string readFileToString(const std::string& filename) {
    // 打开文件
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    
    // 检查文件是否成功打开
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    // 使用 stringstream 来存储文件内容
    std::stringstream buffer;
    buffer << file.rdbuf();

    // 返回读取的字符串
    return buffer.str();
}

int32_t WasmedgeVMManager::load(std::string &wasm_file, std::string &wasm_name)
{
    std::string bytecode = readFileToString(wasm_file);
    std::queue<std::shared_ptr<WasmedgeVM>> qu;
    for (int32_t i = 0; i < vm_num_; i++)
    {
        auto vm = std::make_shared<WasmedgeVM>();
        if (vm->load(bytecode, wasm_name) < 0) {
            return -1;
        }
        qu.push(vm);
    }
    vms_[wasm_name] = qu;
    return 0;
}

std::shared_ptr<WasmedgeVM> WasmedgeVMManager::pop_wasm_vm(std::string &wasm_name)
{
    std::lock_guard<std::mutex> lk(mtx_);
    auto it = vms_.find(wasm_name);
    if (it == vms_.end() || it->second.empty())
    {
        return nullptr;
    }
    auto vm = it->second.front();
    vm->setCtxId(wasm_ctx_id_alloc_++);
    it->second.pop();
    return vm;
}

void WasmedgeVMManager::push_wasm_vm(std::shared_ptr<WasmedgeVM> vm)
{
    std::lock_guard<std::mutex> lk(mtx_);
    auto it = vms_.find(vm->wasm_name());
    if (it == vms_.end())
    {
        return;
    }
    it->second.push(vm);
}
