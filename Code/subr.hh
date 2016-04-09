#pragma once

#include "object.hh"
#include "env.hh"

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

Object apply_subr(string subr_name, Object lvals);

Object do_plus(Object lvals);
Object do_times(Object lvals);
Object do_minus(Object lvals);
Object do_concat(Object lvals);
Object do_car(Object lvals);
Object do_cdr(Object lvals);
Object do_cons(Object lvals);
Object do_eq(Object lvals);
Object do_read(Object lvals);
Object do_print(Object lvals);
Object do_newline(Object lvals);
Object do_end(Object lvals);

Object do_null(Object lvals);
Object do_stringp(Object lvals);
Object do_numberp(Object lvals);
Object do_symbolp(Object lvals);
Object do_listp(Object lvals);

Object do_eval(Object lvals);
Object do_apply(Object lvals);
Object do_error(Object lvals);

