#include "subr.hh"
#include "eval.hh"

extern Object just_read;
extern "C" int yyparse();
extern "C" FILE *yyin;

void add_subr(Environment &env, string name) {
  Object p = subr_to_Object(name);
  env.add_new_binding(name, p);
}

void env_init_subr(Environment &env) {
  add_subr(env, "+");
  add_subr(env, "*");
  add_subr(env, "-");
  add_subr(env, "concat");
  add_subr(env, "car");
  add_subr(env, "cdr");
  add_subr(env, "cons");
  add_subr(env, "eq");
  add_subr(env, "=");
  add_subr(env, "read");
  add_subr(env, "print");
  add_subr(env, "newline");
  add_subr(env, "end");
  add_subr(env, "null");
  add_subr(env, "stringp");
  add_subr(env, "numberp");
  add_subr(env, "symbolp");
  add_subr(env, "listp");
  add_subr(env, "eval");
  add_subr(env, "apply");
  add_subr(env, "error");
}

Object apply_subr(Object subr, Object lvals, Environment &env) {
  string subr_name = Object_to_string(subr);
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
    return do_read();
  }
  else if (subr_name == "print") {
    return do_print(lvals);
  }
  else if (subr_name == "newline") {
    return do_newline();
  }
  else if (subr_name == "end") {
    return do_end();
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
  else if (subr_name == "eval") {
    return do_eval(lvals, env);
  }
  else if (subr_name == "apply") {
    return do_apply(lvals, env);
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
Object do_read() {
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
Object do_newline() {
  std::cout << std::endl;
  return nil();
}
Object do_end() {
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

Object do_eval(Object lvals, Environment &env) {
  if (is_empty(lvals))
    throw Subroutine_Evaluation_Exception("eval", "Not enough arguments");
  Object a = car(lvals);
  return eval(a, env);
}

Object do_apply(Object lvals, Environment &env) {
  if (is_empty(lvals) || is_empty(cdr(lvals)))
    throw Subroutine_Evaluation_Exception("apply", "Not enough arguments");
  Object a = car(lvals);
  Object b = cadr(lvals);
  if (!symbolp(a) && !subrp(a))
    throw Subroutine_Evaluation_Exception("apply", "First argument must be a symbol");
  return apply(a, b, env);
}

Object do_error(Object lvals) {
  if (is_empty(lvals))
    throw Subroutine_Evaluation_Exception("error", "Not enough arguments");
  Object c = car(lvals);
  if (!stringp(c))
    throw Subroutine_Evaluation_Exception("error", "Argument must be a string");
  throw User_Error(Object_to_string(c));
  return nil();
}


