#ifndef LDHELMET_TABLE_GEN_MEMORY_MANAGER_INL_H_
#define LDHELMET_TABLE_GEN_MEMORY_MANAGER_INL_H_

#include <stdint.h>
#include <stdio.h>

#include <string>

#include <boost/lexical_cast.hpp>

#include "table_gen/memory_manager.h"

inline TableGenMemoryManager::TableGenMemoryManager(Vec8 *table,
                                                    uint32_t max_degree)
    : table_(table), max_degree_(max_degree) {
  char tmp_dir_name_template[] = "tmp_table_gen_XXXXXX";
  tmp_dir_ = mkdtemp(tmp_dir_name_template);
  if (tmp_dir_ == "") {
    fprintf(stderr, "Unable to create temporary directory.\n");
    std::exit(1);
  }
  file_list_.resize(max_degree_ + 1);
}

inline TableGenMemoryManager::~TableGenMemoryManager() {
  printf("Removing temporary files.\n");
  for (size_t i = 0; i < file_list_.size(); ++i) {
    if (file_list_[i] != "") {
      unlink(file_list_[i].c_str());
    }
  }
  rmdir(tmp_dir_.c_str());
}

inline void TableGenMemoryManager::FillDegreeFromFile(uint32_t degree) {
  if (degree > max_degree_) { return; }
  if ((*table_)[degree].size() != 0) { return; }
  std::string tmp_file = "tmp_deg_" + boost::lexical_cast<std::string>(degree);
  std::string tmp_path = tmp_dir_ + "/" + tmp_file;
  FILE *fp = fopen(tmp_path.c_str(), "rb");
  if (fp == NULL) {
    fprintf(stderr,
            "Could not open temporary file for reading: %s.\n",
            tmp_path.c_str());
    std::exit(1);
  }
  uint64_t num_confs = ComputeNumConfs(degree);
  (*table_)[degree] = std::vector<double>(num_confs);
  size_t num_read = fread(reinterpret_cast<char *>(&(*table_)[degree][0]),
                          sizeof(double), num_confs, fp);
  if (num_read != num_confs) {
    fprintf(stderr, "Error reading temporary file.\n");
    std::exit(1);
  }
  fclose(fp);
}

inline void TableGenMemoryManager::WriteDegreeToFile(uint32_t degree) {
  if (degree > max_degree_ || (*table_)[degree].size() == 0) { return; }
  std::string tmp_file = "tmp_deg_" + boost::lexical_cast<std::string>(degree);
  std::string tmp_path = tmp_dir_ + "/" + tmp_file;
  FILE *fp = fopen(tmp_path.c_str(), "wb");
  if (fp == NULL) {
    fprintf(stderr,
            "Could not open temporary file for writing: %s.\n",
            tmp_path.c_str());
    std::exit(1);
  }
  file_list_[degree] = tmp_path;
  size_t num_confs = (*table_)[degree].size();
  size_t num_written = fwrite(reinterpret_cast<char *>(&(*table_)[degree][0]),
                              sizeof(double), num_confs, fp);
  if (num_written != num_confs) {
    fprintf(stderr, "Error writing temporary file.\n");
    std::exit(1);
  }
  fclose(fp);
}

#endif  // LDHELMET_TABLE_GEN_MEMORY_MANAGER_INL_H_
