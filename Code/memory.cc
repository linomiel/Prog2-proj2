#include <iostream>
#include <cassert>
#include "memory.hh"

using namespace std;

struct memory_cell void_cell;

vector < struct memory_cell > Memory::mem(0, void_cell);

Object Memory::allocate() {
  mem.push_back(void_cell);
  mem.back().obj = new Cell();
  //cout << mem.size() << " # " << flush;
  return mem.back().obj;
}

void Memory::clean(const Environment env) {
  env.mark(mem);
  for (vector < struct memory_cell >::iterator j = mem.begin() ; j != mem.end(); j++) {
    //std::cout << (j - mem.begin()) << " # ?  " << (*j).obj << std::endl;
    if (!(*j).marked) {
      //std::cout << "Memory clean of " << (*j).obj << std::endl;
      delete (*j).obj;
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
  for (vector < struct memory_cell >::iterator i = mem.begin() ; i != mem.end(); i++) {
    delete (*i).obj;
  }
}
