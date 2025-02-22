#pragma once

#include <cuda_runtime.h>
#include <vector>
#include "core/conversion/conversion.h"
#include "core/ir/ir.h"
#include "core/partitioning/partitioning.h"
#include "core/runtime/runtime.h"
#include "torch/csrc/jit/api/module.h"

namespace trtorch {
namespace core {

struct CompileSpec {
  CompileSpec(std::vector<ir::Input> inputs) : convert_info(std::move(inputs)) {}
  conversion::ConversionInfo convert_info;
  partitioning::PartitionInfo partition_info;
};

bool CheckMethodOperatorSupport(const torch::jit::script::Module& mod, std::string method_name);

std::string ConvertGraphToTRTEngine(const torch::jit::script::Module& mod, std::string method_name, CompileSpec cfg);

torch::jit::script::Module CompileGraph(const torch::jit::script::Module& module, CompileSpec cfg);

torch::jit::script::Module EmbedEngineInNewModule(const std::string& engine, runtime::CudaDevice cuda_device);

void set_device(const int gpu_id);

} // namespace core
} // namespace trtorch
