#include "object.hh"
#include "env.hh"
#include "eval.hh"
#include <stdio.h>
#include <cassert>
extern Object just_read;
extern "C" int yyparse();
extern "C" FILE *yyin;

using namespace std;

bool handle_directive (Object l, Environment &env) {
  if (listp(l)){
    cout << "tic" << endl;
    Object f = car(l);
    if (Object_to_string(f) == "define") {
      assert(!is_empty(cdr(l)));
      assert(!is_empty(cddr(l)));
      Object symb = cadr(l);
      Object value = caddr(l);
      env.add_new_binding(Object_to_string(symb), eval(value, env));
      return true;	
    }
    if (Object_to_string(f) == "setq") {
      assert(!is_empty(cdr(l)));
      assert(!is_empty(cddr(l)));
      Object symb = cadr(l);
      Object value = caddr(l);
      env.modify_env(Object_to_string(symb), eval(value, env));
      return true;
    }
    //for later : defun (procrastinate)
  }
  return false;
}

int main() {
  Object a =  symbol_to_Object("a");
  Object b =  symbol_to_Object("b");
  Object one = number_to_Object(1);
  Object two = number_to_Object(2);

  Environment env;
  env.add_new_binding("+", subr());
  env.add_new_binding("*", subr());
  env.add_new_binding(Object_to_string(a), one);
  env.add_new_binding(Object_to_string(a), two);
  
  do {
    cout << "Lisp? " << flush;
    yyparse();
    Object l = just_read;
    if (!handle_directive(l, env)){ 
      cout << eval(l, env) << endl;
    }
  } while (!feof(yyin));
}






