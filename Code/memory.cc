#include <iostream>
#include <cassert>
#include "memory.hh"

using namespace std;

std::vector < Object > Memory::mem(0,NULL);

Object Memory::allocate() {
  mem.push_back(new Cell());
  return mem.back();
}

void Memory::clean(Object supp) {
  for (std::vector< Object >::iterator i = mem.begin() ; i != mem.end(); ++i) {
    if (*i == supp) {
      std::cout << "Memory clean" << std::endl;
      delete (*i);
      mem.erase(i);
      return;
    }
  }
}

void Memory::free_all() {
  for (std::vector< Object >::iterator i = mem.begin() ; i != mem.end(); ++i) {
    delete (*i);
  }
}
