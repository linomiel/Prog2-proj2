#include "object.hh"
#include "env.hh"
#include "eval.hh"
#include "subr.hh"
#include <stdio.h>
#include <cassert>
#include <cstdlib> 
#include "toplevel.hh"

extern Object just_read;
extern "C" int yyparse();
extern "C" FILE *yyin;

void yyrestart(FILE *new_file);

using namespace std;

extern bool debug;

int main() {
  Environment env;
  env_init_subr(env);
  debug = false;
  
  try {
    top_level(env);
  }
  catch (Lisp_Exit) {}
  cout << "May Lisp be with you!" << endl;
  return 0;
}

