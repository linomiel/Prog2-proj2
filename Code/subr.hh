#pragma once

#include "object.hh"
#include "env.hh"

class Lisp_Exit: public runtime_error {
public:
Lisp_Exit():
  runtime_error("Exiting Lisp.") {}
  virtual ~Lisp_Exit() throw () {}
};

class User_Error: public runtime_error {
public:
User_Error(string _message):
  runtime_error("Lisp error! " + _message) {}
  virtual ~User_Error() throw () {}
};

class Subroutine_Evaluation_Exception: public runtime_error {
private:
  string name;
  string message;
public:
Subroutine_Evaluation_Exception(string _name, string _message):
  runtime_error("Subroutine Evaluation error: " + _message), name(_name), message(_message) {}
  virtual ~Subroutine_Evaluation_Exception() throw () {}
};

void env_init_subr(Environment &env);

Object apply_subr(Object subr, Object lvals, Environment &env);

Object do_plus(Object lvals);
Object do_times(Object lvals);
Object do_minus(Object lvals);
Object do_concat(Object lvals);
Object do_car(Object lvals);
Object do_cdr(Object lvals);
Object do_cons(Object lvals);
Object do_eq(Object lvals);
Object do_read();
Object do_print(Object lvals);
Object do_newline();
Object do_end();

Object do_null(Object lvals);
Object do_stringp(Object lvals);
Object do_numberp(Object lvals);
Object do_symbolp(Object lvals);
Object do_listp(Object lvals);

Object do_eval(Object lvals, Environment &env);
Object do_apply(Object lvals, Environment &env);
Object do_error(Object lvals);

