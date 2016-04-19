#include "object.hh"
#include "env.hh"
#include "eval.hh"
#include "subr.hh"
#include <stdio.h>
#include <cassert>
#include <cstdlib> 
#include "memory.hh"
#include "toplevel.hh"

using namespace std;

extern bool debug;

extern struct memory_cell void_cell;

int main() {
  void_cell.marked = false;
  Environment env;
  env_init_subr(env);
  debug = false;
  
  try {
    top_level(env);
  }
  catch (Lisp_Exit) {}
  cout << "May Lisp be with you!" << endl;
  Memory::free_all();
  return 0;
}

