#pragma once

#include "cell.hh"
#include "env.hh"
#include <vector>

struct memory_cell {
  Cell cell;
  bool marked;
};

class Memory {
  private:
    static std::vector < struct memory_cell > mem;
  public:
    Memory();
    static int allocate();
    static void clean(const Environment env);
    static void free_all();
    static void printmem();
};
