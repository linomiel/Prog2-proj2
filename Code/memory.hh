#pragma once

#include "cell.hh"
#include "env.hh"
#include <vector>

struct memory_cell {
  Cell cell;
  bool marked;
};

class FullMemory: public runtime_error {
public:
FullMemory():
  runtime_error("Memory error! Not enough memory.") {}
  virtual ~FullMemory() throw () {}
};

class Memory {
  private:
    static std::vector < struct memory_cell > mem;
  public:
    Memory();
    static Object allocate();
    static void clean(const Environment &env);
    static void rec_mark(const Object &obj);
    static void free_all();
    static void printmem();
};
