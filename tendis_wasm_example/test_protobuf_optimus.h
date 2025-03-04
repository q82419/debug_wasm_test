#pragma once

#ifndef TENDIS_WASM_KEEPALIVE
#define TENDIS_WASM_KEEPALIVE __attribute__((used)) __attribute__((visibility("default")))
#endif
#define WASM_EXPORT(_return_type, _function_name, _function_args)                                  \
  extern "C" TENDIS_WASM_KEEPALIVE _return_type _function_name _function_args

//#include "optimus.pb.h"

extern "C" int32_t tendis_get_buffer_bytes(int32_t ctxId, int32_t type, const char **ptr, int32_t *size);
extern "C" int32_t tendis_set_buffer_bytes(int32_t ctxId, int32_t type, const char *data, int32_t size);
