/*
 * Copyright 2019 Xilinx, Inc.
 * Copyright 2022 - 2024 Advanced Micro Devices, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "xir/graph/graph.hpp"

#include "UniLog/UniLog.hpp"
#include "xir/graph/graph_imp.hpp"
#include "xir/graph/serialize_v2.hpp"

namespace xir {

std::unique_ptr<Graph> Graph::create(std::string name) {
  return std::unique_ptr<Graph>{static_cast<Graph*>(new GraphImp{name})};
}

std::unique_ptr<Graph> Graph::deserialize(const std::string& pb_fname) {
  v2::Serialize s;
  auto g = s.read(pb_fname);
  return g;
}

std::unique_ptr<Graph> Graph::deserialize_from_string(const std::string& str) {
  v2::Serialize s;
  auto g = s.read_from_string(str);
  return g;
}

std::unique_ptr<Graph> Graph::deserialize_from_memory(const void* data,
                                                      size_t size) {
  v2::Serialize s;
  auto g = s.read_from_memory(data, size);
  return g;
}

std::map<std::string, std::size_t> Graph::compute_graph_attribute_size() const {
  const GraphImp* g = dynamic_cast<const GraphImp*>(this);
  if (g == nullptr) {
    return {};
  }
  return g->compute_graph_attribute_size();
}

std::int64_t Graph::compute_model_size() const {
  const GraphImp* g = dynamic_cast<const GraphImp*>(this);
  if (g == nullptr) {
    return 0;
  }
  return g->compute_model_size();
}
}  // namespace xir

extern "C" {
#ifdef _WIN32
__declspec(dllexport)
#endif
    std::unique_ptr<xir::Graph> xir_deserialize_cif(
        const std::string& pb_fname) {
  return xir::Graph::deserialize(pb_fname);
}
}
