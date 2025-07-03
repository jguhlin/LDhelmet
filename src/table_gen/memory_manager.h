#ifndef LDHELMET_TABLE_GEN_MEMORY_MANAGER_H_
#define LDHELMET_TABLE_GEN_MEMORY_MANAGER_H_

#include <stdint.h>

#include <cstdlib>
#include <string>
#include <vector>

#include "table_gen/solve_scc.h"
#include "common/vector_definitions.h"

class TableGenMemoryManager {
 public:
  TableGenMemoryManager(Vec8 *table, uint32_t max_degree);
  ~TableGenMemoryManager();

  void FillDegreeFromFile(uint32_t degree);
  void WriteDegreeToFile(uint32_t degree);

  inline void LoadDegrees(uint32_t degree) {
    if (degree >= 1) { FillDegreeFromFile(degree - 1); }
    if (degree >= 2) { FillDegreeFromFile(degree - 2); }
  }

  inline void FreeDegree(uint32_t degree) {
    if (degree < table_->size()) {
      std::vector<double>().swap((*table_)[degree]);
    }
  }

  Vec8 *table_;
  uint32_t const max_degree_;
  std::string tmp_dir_;
  std::vector<std::string> file_list_;
};

#endif  // LDHELMET_TABLE_GEN_MEMORY_MANAGER_H_
