#include "subr.hh"

void env_init_subr(Environment &env) {
  env.add_new_binding("+", subr());
  env.add_new_binding("*", subr());
  env.add_new_binding("-", subr());
  env.add_new_binding("concat", subr());
  env.add_new_binding("car", subr());
  env.add_new_binding("cdr", subr());
  env.add_new_binding("cons", subr());
  env.add_new_binding("eq", subr());
  env.add_new_binding("read", subr());
  env.add_new_binding("print", subr());
  env.add_new_binding("newline", subr());
  env.add_new_binding("end", subr());
  env.add_new_binding("null", subr());
  env.add_new_binding("stringp", subr());
  env.add_new_binding("numberp", subr());
  env.add_new_binding("symbolp", subr());
  env.add_new_binding("listp", subr());
  env.add_new_binding("eval", subr());
  env.add_new_binding("apply", subr());
  env.add_new_binding("error", subr());
}

Object apply_subr(string subr_name, Object lvals) {
  if (subr_name == "+") {
    return do_plus(lvals);
  }
  else if (subr_name == "*") {
    return do_times(lvals);
  }
  else if (subr_name == "-") {
    return do_minus(lvals);
  }
  else {
    return nil();
  }
}

Object do_plus(Object lvals) {
  if (is_empty(lvals) || is_empty(cdr(lvals)))
    throw Subroutine_Evaluation_Exception("+", "Not enough arguments");
  int a = Object_to_number(car(lvals));
  int b = Object_to_number(car(cdr(lvals)));
  return number_to_Object(a + b);
}
Object do_times(Object lvals) {
  if (is_empty(lvals) || is_empty(cdr(lvals)))
    throw Subroutine_Evaluation_Exception("*", "Not enough arguments");
  int a = Object_to_number(car(lvals));
  int b = Object_to_number(car(cdr(lvals)));
  return number_to_Object(a * b);
}
Object do_minus(Object lvals) {
  if (is_empty(lvals) || is_empty(cdr(lvals)))
    throw Subroutine_Evaluation_Exception("-", "Not enough arguments");
  int a = Object_to_number(car(lvals));
  int b = Object_to_number(car(cdr(lvals)));
  return number_to_Object(a - b);
}
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


