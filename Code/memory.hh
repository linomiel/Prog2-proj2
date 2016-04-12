#pragma once

#include "object.hh"
#include <vector>


class Memory {
  private:
    static std::vector < Object > mem;
  public:
    Memory();
    static Object allocate();
    static void clean(Object supp);
    static void free_all();
};
