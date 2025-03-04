#include <iostream>
#include "test_protobuf_wasm_full.h"

#include <cstring>
#include "lz4.h"

#include "parallel_hashmap/phmap.h"

void phmap_test() {
  // 创建一个 flat_hash_map，键和值均为 std::string 类型
    phmap::flat_hash_map<std::string, std::string> email = {
        { "tom",  "tom@gmail.com" },
        { "jeff", "jk@gmail.com" },
        { "jim",  "jimg@microsoft.com" }
    };

    // 输出所有键值对
    auto it = email.find("jeff");
    if (it == email.end()) {
      std::cout << "Key  jeff does not exist in the map.\n";
    }
    // 添加新的键值对
    email["bill"] = "billg@microsoft.com";
}

void lz4_test() {
  // 原始数据
    const char* src = "Hello, LZ4 Compression! lsllslsllslaalsllsllslsllslsllsldldkdlslsldskdkkkdlslslnxnnxnxnlslslsdlkdkslsldkkdlslskdksljwi838388292999ssslslsldklal;asla;a;sldkdkdkkdkdkdkdkddkdkkdsllslslsls12222222222222222222299999999999999999999999999999999999999999999999999999999999";
    int src_size = static_cast<int>(strlen(src)) + 1; // 包括终止符

    // 计算最大压缩后大小
    int max_dst_size = LZ4_compressBound(src_size);
    char* compressed_data = new char[max_dst_size];

    // 压缩数据
    int compressed_size = LZ4_compress_default(src, compressed_data, src_size, max_dst_size);
    if (compressed_size <= 0) {
        std::cerr << "压缩失败！" << std::endl;
        delete[] compressed_data;
        return ;
    }

    // 解压缩
    char* decompressed_data = new char[src_size];
    int decompressed_size = LZ4_decompress_safe(compressed_data, decompressed_data, compressed_size, src_size);
    if (decompressed_size < 0) {
        std::cerr << "decompressed failed." << std::endl;
        delete[] compressed_data;
        delete[] decompressed_data;
        return ;
    }
    if (memcmp(src, decompressed_data, src_size - 1) != 0) {
        std::cout << "decompressed_data error" << std::endl;
    }

    // 释放内存
    delete[] compressed_data;
    delete[] decompressed_data;
}

void protobuf_test() {
  // 创建并设置一个 Person 对象
  Person person;
  person.set_name("John Doe");
  person.set_id(1234);
  person.set_email("johndoe@example.com");

  // 序列化 Person 对象
  std::string output;
  if (!person.SerializeToString(&output)) {
    std::cerr << "Failed to serialize person." << std::endl;
    return ;
  }

  // 反序列化
  Person new_person;
  if (!new_person.ParseFromString(output)) {
    std::cerr << "Failed to parse person." << std::endl;
    return ;
  }

  if (new_person.name() != person.name()) {
    std::cout << "The deserialized person does not match the original." << std::endl;
  }
  if (new_person.id() != person.id()) {
    std::cout << "The deserialized person does not match the original." << std::endl;
  }
  if (new_person.email() != person.email()) {
    std::cout << "The deserialized person does not match the original." << std::endl;
  }
}


extern "C" TENDIS_WASM_KEEPALIVE
void tendis_wasm_process(int count) {
  // 获取当前时间点
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < count;i ++) {
  // protobuf test
  //std::cout << "====================protobuf test start====================" << std::endl;
  protobuf_test();
  //std::cout << "====================protobuf test end====================" << std::endl;

  // lz4 test
  //std::cout << "====================lz4 test start====================" << std::endl;
  lz4_test();
  //std::cout << "====================lz4 test end====================" << std::endl;

  // phmap test
  //std::cout << "====================phmap test start====================" << std::endl;
  phmap_test();
  //std::cout << "====================phmap test end====================" << std::endl;
  }
  // 获取当前时间点
  auto end = std::chrono::high_resolution_clock::now();
  //std::chrono::duration<double, std::milli> duration_ms = end - start;
  //std::cout << "Run " << count << " times,Execution time: " << duration_ms.count() << " milliseconds\n";
}
