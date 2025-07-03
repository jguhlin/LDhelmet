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

#ifndef LDHELMET_TABLE_GEN_TABLE_MANAGEMENT_H_
#define LDHELMET_TABLE_GEN_TABLE_MANAGEMENT_H_

#include <stdint.h>

#include "common/conf.h"
#include "common/vector_definitions.h"

// Allocate memory to table.
// Allocates memory to invalid configurations as well, and initializes them to
// 0.0.  Returns the number of configurations allocated for the degree.
uint64_t AllocateMemoryToTable(Vec8 *table, uint32_t degree);

Conf GetCanon(Conf conf);

// Set the probability of the given configuration in the table.
void SetTable(Vec8 *table, Conf const &in_conf, double value);

// Get the probability of the given configuration from table.
// table also contains entries for invalid configurations.
double GetTable(Vec8 const &table, Conf const &in_conf);

#endif  // LDHELMET_TABLE_GEN_TABLE_MANAGEMENT_H_
