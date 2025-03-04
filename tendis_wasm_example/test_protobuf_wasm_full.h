#pragma once

#ifndef TENDIS_WASM_KEEPALIVE
#define TENDIS_WASM_KEEPALIVE __attribute__((used)) __attribute__((visibility("default")))
#endif
#define WASM_EXPORT(_return_type, _function_name, _function_args)                                  \
  extern "C" TENDIS_WASM_KEEPALIVE _return_type _function_name _function_args


#include "test_person.pb.h"
