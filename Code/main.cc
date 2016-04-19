#include "object.hh"
#include "env.hh"
#include "eval.hh"
#include "subr.hh"
#include <stdio.h>
#include <cassert>
#include "memory.hh"
#include <cstdlib> 
extern Object just_read;
extern "C" int yyparse();
extern "C" FILE *yyin;

using namespace std;

bool in_debug = false;

bool handle_directive (Object l, Environment &env) {
  if (listp(l)){
    Object f = car(l);
    if (symbolp(f)) {
      string instruct = Object_to_string(f);
      if (instruct == "define") {
        assert(!is_empty(cdr(l)));
        assert(!is_empty(cddr(l)));
        Object symb = cadr(l);
        Object value = caddr(l);
        env.add_new_binding(Object_to_string(symb), eval(value, env));
        return true;
      }
      if (instruct == "setq") {
        assert(!is_empty(cdr(l)));
        assert(!is_empty(cddr(l)));
        Object symb = cadr(l);
        Object value = caddr(l);
        env.modify_env(Object_to_string(symb), eval(value, env));
        return true;
      }
      if (instruct == "debug") {
        debug = !debug;
      }
      //for later : defun (procrastinate)
    }
  }
  return false;
}

extern struct memory_cell void_cell;

int main() {
  void_cell.marked = false;
  Environment env;
  env_init_subr(env);
  Memory::printmem();
  std::cout << env << std::endl;
  
  try {
    do {
      cout << "Lisp? " << flush;
      yyparse();
      Object l = just_read;
      try {
        if (!handle_directive(l, env)) {
          cout << eval(l, env) << endl;
        }
      }
      catch (User_Error(e)) {std::clog << e.what() << std::endl;}
      catch (Subroutine_Evaluation_Exception(e)) {std::clog << e.what() << std::endl;}
      catch (No_Binding_Exception(e)) {std::clog << e.what() << std::endl;}
      catch (Evaluation_Exception(e)) {std::clog << e.what() << std::endl;}
      Memory::clean(env);
    } while (!feof(yyin));
  }
  catch (Lisp_Exit) {}
  cout << "Good bye." << endl;
  Memory::free_all();
  return 0;
}

