#include <iostream>

//#include <cstring>
#include <sstream>


//#include <fstream>

#include "test_protobuf_optimus.h"

#include "file_bin.h"


using target_t = uint64_t;
using targets_t = std::vector<target_t>;

class WasmData {
public:
  // Constructs a buffer that owns `size` bytes starting at `data`.
  WasmData(const char *data, size_t size) : data_(data), size_(size) {}
  // Frees buffer data.
  ~WasmData() { 
    ::free(const_cast<char *>(data_));
  }
  // Returns pointer to the start of the buffer;
  const char *data() { return data_; }
  // Returns the size of the buffer in bytes.
  size_t size() { return size_; }
  // Returns buffer data in the form of a string_view.
  std::string_view view() { return {data_, size_}; }
  // Returns a string copy of buffer data.
  std::string toString() { return std::string(view()); }
  // Returns a series of string pairs decoded from and backed by the buffer.
  std::vector<std::pair<std::string_view, std::string_view>> pairs();
  // Returns a protobuf of type T parsed from buffer contents.
  template <typename T> T proto() {
    T p;
    p.ParseFromArray(data_, size_);
    return p;
  }

  WasmData &operator=(const WasmData &) = delete;
  WasmData(const WasmData &) = delete;

private:
  const char *data_;
  size_t size_;
};
typedef std::unique_ptr<WasmData> WasmDataPtr;


extern "C" TENDIS_WASM_KEEPALIVE
int32_t tendis_wasm_dispatche_phase(int32_t ctxId) {
  /*tendis_set_buffer_bytes(ctxId, 0, "test", 4);
  std::string testRes1 = "tendis_wasm_dispatche_phase *******: req data:";
  tendis_set_buffer_bytes(ctxId, 0, testRes1.c_str(), testRes1.size());

  std::string testRes2 = "tendis_wasm_dispatche_phase *******: req data: tests2222";
  tendis_set_buffer_bytes(ctxId, 0, testRes2.c_str(), testRes2.size());*/

  {
  const char *ptr = nullptr;
  int32_t size = 0;
  if (tendis_get_buffer_bytes(ctxId, 3, &ptr, &size) != 0) return -100;
  }
  {
  const char *ptr = nullptr;
  int32_t size = 0;
  if (tendis_get_buffer_bytes(ctxId, 3, &ptr, &size) != 0) return -200;
  }

  // todo
  /*{
  std::string testRes1 = "tendis_wasm_dispatche_phase *******: req data:";
  tendis_set_buffer_bytes(ctxId, 4, testRes1.c_str(), testRes1.size());
  }*/
  return 0;
}


