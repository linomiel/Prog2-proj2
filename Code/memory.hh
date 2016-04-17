#pragma once

#include "object.hh"
#include "env.hh"
#include <vector>

struct memory_cell {
  Object obj;
  bool marked;
};

class Memory {
  private:
    static std::vector < struct memory_cell > mem;
  public:
    Memory();
    static Object allocate();
    static void clean(const Environment env);
    static void free_all();
};
