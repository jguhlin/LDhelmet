// Copyright (C) 2012  Andrew H. Chan, Paul A. Jenkins, Yun S. Song
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// <http://www.gnu.org/licenses/>
//
//

#include "table_gen/table_management.h"

#include <stdint.h>
#include <algorithm>

#include "common/conf.h"
#include "common/vector_definitions.h"
#include "table_gen/solve_scc.h"

namespace {

// Compute the flat index of a configuration in the contiguous table.
size_t ConfIndex(Conf const& in_conf) {
  Conf conf = GetCanon(in_conf);
  uint32_t a_mar = conf.a_ + conf.ab_ + conf.aB_;
  uint32_t A_mar = conf.A_ + conf.Ab_ + conf.AB_;
  uint32_t b_mar = conf.b_ + conf.ab_ + conf.Ab_;
  uint32_t B_mar = conf.B_ + conf.aB_ + conf.AB_;
  uint32_t degree = a_mar + A_mar + b_mar + B_mar;

  size_t offset = 0;
  for (uint32_t a = 0; a <= degree; ++a) {
    for (uint32_t A = 0; A <= degree - a; ++A) {
      for (uint32_t b = 0; b <= std::min(degree - a - A, a); ++b) {
        uint32_t B = degree - a - A - b;
        if (b == a && B > A) {
          continue;
        }
        if (a == a_mar && A == A_mar && b == b_mar && B == B_mar) {
          IndexTables tables = ComputeIndexTables(a_mar, A_mar, b_mar, B_mar);
          return offset + ConfToIndex(tables, conf);
        }
        offset += ComputeNumConfsSCC(a, A, b, B);
      }
    }
  }
  return offset;  // should never reach here
}

}  // namespace

uint64_t AllocateMemoryToTable(Vec8 *table, uint32_t degree) {
  uint64_t num_confs = ComputeNumConfs(degree);
  (*table)[degree] = std::vector<double>(num_confs, 0.0);
  return num_confs;
}

Conf GetCanon(Conf conf) {
  uint32_t a_mar = conf.a_ + conf.ab_ + conf.aB_;
  uint32_t A_mar = conf.A_ + conf.Ab_ + conf.AB_;
  uint32_t b_mar = conf.b_ + conf.ab_ + conf.Ab_;
  uint32_t B_mar = conf.B_ + conf.aB_ + conf.AB_;
  if (!(a_mar == b_mar ? A_mar >= B_mar : a_mar > b_mar)) {
    std::swap(conf.aB_, conf.Ab_);
    std::swap(conf.a_, conf.b_);
    std::swap(conf.A_, conf.B_);
  }
  return conf;
}

void SetTable(Vec8 *table, Conf const &in_conf, double value) {
  Conf conf = GetCanon(in_conf);
  uint32_t degree = conf.ComputeDegree();
  size_t index = ConfIndex(conf);
  (*table)[degree][index] = value;
}

double GetTable(Vec8 const &table, Conf const &in_conf) {
  Conf conf = GetCanon(in_conf);
  uint32_t degree = conf.ComputeDegree();
  size_t index = ConfIndex(conf);
  return table[degree][index];
}

