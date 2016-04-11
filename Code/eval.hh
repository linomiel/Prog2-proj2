#pragma once

#include "object.hh"
#include "env.hh"
#include "subr.hh"

using namespace std;

bool numberp(Object l);
bool stringp(Object l);
bool symbolp(Object l);
bool listp(Object l);
bool subrp(Object l);

Object cadr(Object l);
Object cddr(Object l);
Object caddr(Object l);
Object cdddr(Object l);
Object cadddr(Object l);

class Evaluation_Exception: public runtime_error {
private:
  Object obj;
  Environment env;
  string message;
public:
  Evaluation_Exception(Object _obj, Environment _env, string _message):
    runtime_error("Evaluation error:" + _message) {
    obj = _obj;
    env = _env;
    message = _message;
  }
  virtual ~Evaluation_Exception() throw () {}
};

Object eval(Object l, Environment &env);
Object apply(Object f, Object lvals, Environment &env);
Object eval_list(Object largs, Environment env);

Object do_progn(Object l, Environment &env);
Object do_cond(Object l, Environment &env);
Object do_andthen(Object l, Environment &env);
