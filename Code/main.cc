#include "object.hh"
#include "env.hh"
#include "eval.hh"
#include "subr.hh"
#include <stdio.h>
#include <cassert>
extern Object just_read;
extern "C" int yyparse();
extern "C" FILE *yyin;

using namespace std;

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
      }
    }
  }
  return false;
}

int main() {
  Environment env;
  env_init_subr(env);
  
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
    } while (!feof(yyin));
  }
  catch (Lisp_Exit) {}
  cout << "Good bye." << endl;
  return 0;
}






