/* Copyright 2018 Stanford
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

#ifndef _FLEXFLOW_CONFIG_H_
#define _FLEXFLOW_CONFIG_H_
#include <cstring>
#include "legion.h"

// ========================================================
// Define Runtime Constants
// ========================================================
#define MAX_NUM_INPUTS 6
#define MAX_NUM_LOCALS 3
#define MAX_NUM_WORKERS 16
#define MAX_DIM 4
#define MAX_FILENAME 200
#define MAX_OPNAME 64
// DataLoader
#define MAX_SAMPLES_PER_LOAD 64
#define MAX_FILE_LENGTH 128

using namespace Legion;

struct ParallelConfig {
  int nDims, dim[MAX_DIM];
  int gpu[MAX_NUM_WORKERS];
};

class FFConfig {
public:
  int epochs, batchSize, numIterations, printFreq;
  int inputHeight, inputWidth;
  int numNodes, loadersPerNode, workersPerNode;
  float learningRate, weightDecay;
  size_t workSpaceSize;
  Context lg_ctx;
  Runtime* lg_hlr;
  FieldSpace field_space;
  bool syntheticInput, profiling;
  std::string datasetPath, strategyFile;
  std::map<std::string, ParallelConfig> strategies;
  bool load_strategy_file(std::string filename);
  bool save_strategy_file(std::string filename);
};

struct ParaConfigCompare {
  bool operator()(const ParallelConfig& a, const ParallelConfig& b) const {
    if (a.nDims != b.nDims)
      return a.nDims < b.nDims;
    for (int i = 0; i < a.nDims; i++)
      if (a.dim[i] != b.dim[i])
        return a.dim[i] < b.dim[i];
    return false;
  }
};
#endif//_FLEXFLOW_CONFIG_H_
