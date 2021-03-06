#include <iostream>
#include <iomanip>
#include <cassert>
#include "memory.hh"
#include "eval.hh"

using namespace std;
struct memory_cell void_cell;

vector < struct memory_cell > Memory::mem(1000, void_cell);

Object Memory::allocate() {
  for (vector < struct memory_cell >::iterator j = mem.begin() ; j != mem.end(); j++) {
    if (!(*j).marked) {
      (*j).marked = true;
      return &((*j).cell);
    }
  }
  //there is no free memory cell
  std::clog << "More memory needed." << std::endl;
  throw FullMemory();
  mem.resize(mem.size() + 1);
  mem.back().marked = true;
  return &(mem.back().cell);
}

void Memory::clean(const Environment &env) {
  for (vector < struct memory_cell >::iterator j = mem.begin() ; j != mem.end(); j++) {
    (*j).marked = false;
  }
  env.mark(mem);
}

void Memory::rec_mark(const Object &obj) {
  for (vector < struct memory_cell >::iterator j = mem.begin() ; j != mem.end(); j++) {
    if (obj == &((*j).cell)) {
      (*j).marked = true;
    }
  }
  if (listp(obj)) {
    rec_mark(car(obj));
    rec_mark(cdr(obj));
  }
}

void Memory::free_all() {
  mem.clear();
}

void Memory::printmem() {
  for (vector < struct memory_cell >::iterator j = mem.begin() ; j != mem.end(); j++) {
    std::cout << std::setw(6) << (j - mem.begin());
    if ((*j).marked) {
      std::cout << " [*]|";
    }
    else {
      std::cout << " [ ]|";
    }
    if ((int) (j - mem.begin()) % 10 == 9) {
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;
}
