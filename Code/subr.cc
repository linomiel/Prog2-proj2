#include "subr.hh"
#include "eval.hh"
extern Object just_read;
extern "C" int yyparse();
extern "C" FILE *yyin;

void env_init_subr(Environment &env) {
  env.add_new_binding("+", subr());
  env.add_new_binding("*", subr());
  env.add_new_binding("-", subr());
  env.add_new_binding("concat", subr());
  env.add_new_binding("car", subr());
  env.add_new_binding("cdr", subr());
  env.add_new_binding("cons", subr());
  env.add_new_binding("eq", subr());
  env.add_new_binding("=", subr());
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
  else if (subr_name == "concat") {
    return do_concat(lvals);
  }
  else if (subr_name == "car") {
    return do_car(lvals);
  }
  else if (subr_name == "cdr") {
    return do_cdr(lvals);
  }
  else if (subr_name == "cons") {
    return do_cons(lvals);
  }
  else if (subr_name == "=" || subr_name == "eq") {
    return do_eq(lvals);
  }
  else if (subr_name == "read") {
    return do_read(lvals);
  }
  else if (subr_name == "print") {
    return do_print(lvals);
  }
  else if (subr_name == "newline") {
    return do_newline(lvals);
  }
  else if (subr_name == "end") {
    return do_end(lvals);
  }
  else if (subr_name == "null") {
    return do_null(lvals);
  }
  else if (subr_name == "stringp") {
    return do_stringp(lvals);
  }
  else if (subr_name == "numberp") {
    return do_numberp(lvals);
  }
  else if (subr_name == "symbolp") {
    return do_symbolp(lvals);
  }
  else if (subr_name == "listp") {
    return do_listp(lvals);
  }
  else if (subr_name == "error") {
    return do_error(lvals);
  }
  else {
    return nil();
  }
}

Object do_plus(Object lvals) {
  if (is_empty(lvals) || is_empty(cdr(lvals)))
    throw Subroutine_Evaluation_Exception("+", "Not enough arguments");
  Object a = car(lvals);
  Object b = cadr(lvals);
  if (!numberp(a) || !numberp(b))
    throw Subroutine_Evaluation_Exception("+", "Arguments must be numbers");
  return number_to_Object(Object_to_number(a) + Object_to_number(b));
}
Object do_times(Object lvals) {
  if (is_empty(lvals) || is_empty(cdr(lvals)))
    throw Subroutine_Evaluation_Exception("*", "Not enough arguments");
  Object a = car(lvals);
  Object b = cadr(lvals);
  if (!numberp(a) || !numberp(b))
    throw Subroutine_Evaluation_Exception("*", "Arguments must be numbers");
  return number_to_Object(Object_to_number(a) * Object_to_number(b));
}
Object do_minus(Object lvals) {
  if (is_empty(lvals) || is_empty(cdr(lvals)))
    throw Subroutine_Evaluation_Exception("-", "Not enough arguments");
  Object a = car(lvals);
  Object b = cadr(lvals);
  if (!numberp(a) || !numberp(b))
    throw Subroutine_Evaluation_Exception("-", "Arguments must be numbers");
  return number_to_Object(Object_to_number(a) - Object_to_number(b));
}
Object do_concat(Object lvals) {
  if (is_empty(lvals) || is_empty(cdr(lvals)))
    throw Subroutine_Evaluation_Exception("concat", "Not enough arguments");
  Object a = car(lvals);
  Object b = cadr(lvals);
  if (!stringp(a) || !stringp(b))
    throw Subroutine_Evaluation_Exception("concat", "Arguments must be strings");
  return string_to_Object(Object_to_string(a) + Object_to_string(b));
}
Object do_car(Object lvals) {
  if (is_empty(lvals))
    throw Subroutine_Evaluation_Exception("car", "Not enough arguments");
  Object a = car(lvals);
  return a;
}
Object do_cdr(Object lvals) {
  if (is_empty(lvals))
    throw Subroutine_Evaluation_Exception("cdr", "Not enough arguments");
  Object c = cdr(lvals);
  return c;
}
Object do_cons(Object lvals) {
  if (is_empty(lvals) || is_empty(cdr(lvals)))
    throw Subroutine_Evaluation_Exception("cons", "Not enough arguments");
  Object a = car(lvals);
  Object b = cadr(lvals);
  return cons(a, b);
}
Object do_eq(Object lvals) {
  if (is_empty(lvals) || is_empty(cdr(lvals)))
    throw Subroutine_Evaluation_Exception("eq", "Not enough arguments");
  Object a = car(lvals);
  Object b = cadr(lvals);
  if (eqp(a, b)) {
    return string_to_Object("t");
  }
  else {
    return nil();
  }
}
Object do_read(Object lvals) {
  std::cout << std::endl;
  yyparse();
  return just_read;
}
Object do_print(Object lvals){
  if (is_empty(lvals))
    throw Subroutine_Evaluation_Exception("print", "Not enough arguments");
  Object c = car(lvals);
  std::cout << c << std::flush;
  return c;
}
Object do_newline(Object lvals) {
  std::cout << std::endl;
  return nil();
}
Object do_end(Object lvals) {
  throw Lisp_Exit();
  return nil();
}

Object do_null(Object lvals) {
  if (is_empty(lvals))
    throw Subroutine_Evaluation_Exception("null", "Not enough arguments");
  Object c = car(lvals);
  if (null(c)) {
    return string_to_Object("t");
  }
  else {
    return nil();
  }
}
Object do_stringp(Object lvals) {
  if (is_empty(lvals))
    throw Subroutine_Evaluation_Exception("stringp", "Not enough arguments");
  Object c = car(lvals);
  if (stringp(c)) {
    return string_to_Object("t");
  }
  else {
    return nil();
  }
}
Object do_numberp(Object lvals) {
  if (is_empty(lvals))
    throw Subroutine_Evaluation_Exception("numberp", "Not enough arguments");
  Object c = car(lvals);
  if (numberp(c)) {
    return string_to_Object("t");
  }
  else {
    return nil();
  }
}
Object do_symbolp(Object lvals) {
  if (is_empty(lvals))
    throw Subroutine_Evaluation_Exception("symbolp", "Not enough arguments");
  Object c = car(lvals);
  if (symbolp(c)) {
    return string_to_Object("t");
  }
  else {
    return nil();
  }
}
Object do_listp(Object lvals) {
  if (is_empty(lvals))
    throw Subroutine_Evaluation_Exception("listp", "Not enough arguments");
  Object c = car(lvals);
  if (listp(c)) {
    return string_to_Object("t");
  }
  else {
    return nil();
  }
}

/*Object do_apply(Object lvals, Environment &env) {
  if (is_empty(lvals) || is_empty(cdr(lvals)))
    throw Subroutine_Evaluation_Exception("apply", "Not enough arguments");
  Object a = car(lvals);
  Object b = cadr(lvals);
  if (!symbolp(a) && !subrp(a))
    throw Subroutine_Evaluation_Exception("apply", "First argument must be a symbol");
  return apply(a, b, env);
}*/

Object do_error(Object lvals) {
  if (is_empty(lvals))
    throw Subroutine_Evaluation_Exception("error", "Not enough arguments");
  Object c = car(lvals);
  if (!stringp(c))
    throw Subroutine_Evaluation_Exception("error", "Argument must be a string");
  throw User_Error(Object_to_string(c));
  return nil();
}


