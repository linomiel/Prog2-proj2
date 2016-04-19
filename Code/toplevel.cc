#include "toplevel.hh"

bool debug;

bool handle_directive (Object l, Environment &env) {
  try {
    if (listp(l)){
      Object f = car(l);
      if (symbolp(f)) {
        string instruct = Object_to_string(f);
        if (instruct == "define") {
          if (is_empty(cdr(l)) || is_empty(cddr(l)))
            throw Directive_Exception("define","Not enough arguments");
          Object symb = cadr(l);
          Object value = caddr(l);
          env.add_new_binding(Object_to_string(symb), eval(value, env));
          return true;
        }
        if (instruct == "setq") {
          if (is_empty(cdr(l)) || is_empty(cddr(l)))
            throw Directive_Exception("setq","Not enough arguments");
          Object symb = cadr(l);
          Object value = caddr(l);
          env.modify_env(Object_to_string(symb), eval(value, env));
          return true;
        }
        if (instruct == "debug") {
          debug = !debug;
          if (debug) {
            cout << "Debug active" << endl;
          }
          else {
            cout << "Debug inactive" << endl;
          }
          return true;
        }
        if (instruct == "load") {
          if (is_empty(cdr(l)))
            throw Directive_Exception("load","Not enough arguments");
          if (!stringp(cadr(l)))
            throw Directive_Exception("load","File name must be a string");
          FILE *fh = fopen(Object_to_string(cadr(l)).c_str(),"r");
          if (!fh) {
            perror("load");
            return true;
          }
          yyrestart(fh);
          top_level(env);
          yyrestart(stdin);
          return true;
        }
      }
    }
  }
  catch (Directive_Exception(e)) {
    std::clog << e.what() << std::endl;
    return true;
  }
  return false;
}

void top_level(Environment &env) {
  int stop = 0;
  do {
    cout << "Lisp? " << flush;
    stop = yyparse();
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
  } while (!stop/*!feof(yyin)*/);
}
