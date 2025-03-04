#  Copyright 2020 Google LLC
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load(
    "@bazel_tools//tools/build_defs/repo:git.bzl",
    "git_repository",
)

load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def tendis_wasm_example_repositories():
    maybe(
        http_archive,
        name = "emsdk",
        sha256 = "0cb0eabd6e3ceb1a970a2363e67f2b1689c2d83fbeae1e75901213c1f84de2e2",
        strip_prefix = "emsdk-3.1.67/bazel",
        url = "https://github.com/emscripten-core/emsdk/archive/refs/tags/3.1.67.tar.gz",
    )

