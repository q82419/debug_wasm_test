#include <cstdint>
#include <cstring>
#include "wasmedge_vm.h"

wasm_phase_ctx_t g_ctx_;

static int32_t wasm_copy_to_wasm(std::shared_ptr<wasm_phase_data_t> wasm_ctx, const char* data,int32_t  len, int32_t addr, int32_t size_addr) {
    int32_t        *p_size;
    int32_t         buf_addr;
    int32_t        *p;
    char * buf = nullptr;
    p_size = (int32_t *) wasm_ctx->vm->wasm_get_memory(size_addr, sizeof(int32_t));
    if (p_size == NULL) {
        return -1;
    }
    *p_size = len;
    if (len == 0) {
        return 0;
    }
    buf_addr = wasm_ctx->vm->wasm_memory_alloc(len);
    if (buf_addr == 0) {
        return -1;
    }
    buf = (char *) wasm_ctx->vm->wasm_get_memory(buf_addr, len);
    if (p_size == NULL) {
        return -1;
    }
    memcpy(buf, data, len);

    p = (int32_t *) wasm_ctx->vm->wasm_get_memory(addr, sizeof(int32_t));
    if (p == NULL) {
        return -1;
    }
    std::cout << "tendis_get_buffer_bytes start10 ..., ctx_id: " << std::endl;
    *p = buf_addr;
    return 0;
}

int32_t
tendis_get_buffer_bytes(int32_t ctx_id, int32_t type,
                       int32_t addr, int32_t size_addr)
{
    std::cout << "tendis_get_buffer_bytes start ..., ctx_id: " << ctx_id << std::endl;
    std::string_view buffer;
    const char         *data = NULL;
    int32_t               len = 0;
    auto wasm_ctx = g_ctx_.getCtx(ctx_id);
    switch (type)
    {
    case TENDIS_WASM_BUFFER_TYPE_REQUEST:
        buffer = wasm_ctx->request_data;
        break;
    case TENDIS_WASM_BUFFER_TYPE_CONF:
        buffer = wasm_ctx->conf;
        break;
    default:
        return -1;
    }
    std::cout << "tendis_get_buffer_bytes start1 ..., ctx_id: " << ctx_id << std::endl;
    if (buffer.size() != 0) {
        data = buffer.data();
        len = buffer.size();
        std::cout << "tendis_get_buffer_bytes start2 ..., ctx_id: " << ctx_id << std::endl;
    }
    if (len == 0) return -2;
    
    std::cout << "tendis_get_buffer_bytes start3 ..., ctx_id: " << ctx_id << std::endl;
    return wasm_copy_to_wasm(wasm_ctx, data, len, addr, size_addr);
}

int32_t
tendis_set_buffer_bytes(int32_t ctx_id, int32_t type,
                       int32_t data, int32_t size)
{
    std::cout << "tendis_set_buffer_bytes start ..." << ctx_id << " size:" << size << std::endl;
    char *p;
    auto wasm_ctx = g_ctx_.getCtx(ctx_id);
    if (wasm_ctx == nullptr) {
        std::cout << "get ctx is nullptr" << std::endl;
    }

    if (size <= 0) return 0;

    p = (char *) wasm_ctx->vm->wasm_get_memory(data, size);
    switch (type)
    {
    case TENDIS_WASM_BUFFER_TYPE_RESULT:
        std::copy(p, p+size, std::back_inserter(wasm_ctx->result_data));
        break;
    
    default:
        std::cout << "log: ";
        std::cout.write(p, size);
        std::cout << std::endl;
        break;
    }
    std::cout << "tendis_set_buffer_bytes end ..." << std::endl;

    return 0;
}

