#include <iostream>
#include <cassert>
#include "memory.hh"

using namespace std;
struct memory_cell void_cell;

vector < struct memory_cell > Memory::mem;

Cell* Memory::allocate() {
  mem.resize(mem.size() + 1);
  mem.back().marked = false;
  return &(mem.back().cell);
}

void Memory::clean(const Environment env) {
  env.mark(mem);
  for (vector < struct memory_cell >::iterator j = mem.begin() ; j != mem.end(); j++) {
    std::cout << (j - mem.begin()) << " # ?  " << &((*j).cell) << std::endl;
    if (!(*j).marked) {
      std::cout << "Memory clean of " << &((*j).cell) << std::endl;
      mem.erase(j);
    }
  }
  /*for (std::vector< Object >::iterator i = mem.begin() ; i != mem.end(); ++i) {
    if (*i == supp) {
      std::cout << "Memory clean" << std::endl;
      delete (*i);
      mem.erase(i);
      return;
    }
  }*/
}

void Memory::free_all() {
  mem.clear();
}

void Memory::printmem() {
  for (vector < struct memory_cell >::iterator j = mem.begin() ; j != mem.end(); j++) {
    std::cout << (j - mem.begin()) << " # ?  " << &((*j).cell) << "(at " << (void*) &((*j).cell) << ")" << std::endl;
  }
}
