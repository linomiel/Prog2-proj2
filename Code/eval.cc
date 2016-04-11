#include <stdexcept>
#include <string>
#include <cassert>
#include "eval.hh"

using namespace std;

bool numberp(Object l) {
  return l -> is_number();
}

bool stringp(Object l) {
  return l -> is_string();
}

bool symbolp(Object l) {
  return l -> is_symbol();
}

bool listp(Object l) {
  return l -> is_pair();
}

bool subrp(Object l) {
  return l -> is_subr();
}

Object cadr(Object l) {
  return car(cdr(l));
}

Object cddr(Object l) {
  return cdr(cdr(l));
}

Object caddr(Object l) {
  return car(cddr(l));
}

Object cdddr(Object l) {
  return cdr(cddr(l));
}

Object cadddr(Object l) {
  return car(cdddr(l));
}

Object eval(Object l, Environment &env);
Object apply(Object f, Object lvals, Environment &env);
Object eval_list(Object largs, Environment env);

unsigned int level = 0;

Object show_return_eval(Object o) {
  level--;
  clog << "\t";
  for (unsigned int i = 0; i < level; i++) {
    clog << " ";
  }
  clog << level << " <-- " << o << endl;
  return o;
}

Object eval_f(Object l, Environment &env) {
  if (null(l)) return l;
  if (numberp(l)) return l;
  if (stringp(l)) return l;
  if (symbolp(l)) return env.find_value(Object_to_string(l));
  assert(listp(l));
  Object f = car(l);
  if (symbolp(f)) {
    if (Object_to_string(f) == "lambda") {return l;}
    if (Object_to_string(f) == "quote") {return cadr(l);}
    if (Object_to_string(f) == "if") {
      Object test_part = cadr(l);
      Object then_part = caddr(l);
      Object else_part = cadddr(l);
      Object test_value = eval(test_part, env);
      if (null(test_value)) return eval(else_part, env);
      return eval(then_part, env);
    }
    if (Object_to_string(f) == "printenv") {
      cout << env;
      return nil();
    }
    if (Object_to_string(f) == "progn") {
      return do_progn(cdr(l), env);
    }
    if (Object_to_string(f) == "cond") {
      return do_cond(cdr(l), env);
    }
    if (Object_to_string(f) == "andthen") {
      return do_andthen(cdr(l), env);
    }
  }
  // It is a function applied to arguments
  clog << "\t";
  for (unsigned int i = 0; i < level; i++) {
    clog << " ";
  }
  clog << level << " --> " << f << env << endl;
  level++;
  Object vals = eval_list(cdr(l), env);
  return show_return_eval(apply(f, vals, env));
}

Object eval(Object l, Environment &env) {
  clog << "\t";
  for (unsigned int i = 0; i < level; i++) {
    clog << " ";
  }
  clog << level << " --> " << l << env << endl;
  level++;
  return show_return_eval(eval_f(l, env));
}

Object eval_list(Object largs, Environment env) {
  if (null(largs)) return largs;
  return cons(eval(car(largs), env), eval_list(cdr(largs), env));
}

Object apply(Object f, Object lvals, Environment &env) {
  //clog << "\tapply: " << f << " " << lvals << env << endl;

  if (null(f)) throw Evaluation_Exception(f, env, "Cannot apply nil");
  if (numberp(f)) throw Evaluation_Exception(f, env, "Cannot apply a number");
  if (stringp(f)) throw Evaluation_Exception(f, env, "Cannot apply a string");
  else if (symbolp(f)) {
    Object new_f = env.find_value(Object_to_string(f));
    return apply(new_f, lvals, env);
  }
  else if (subrp(f)) {
    Object new_f = env.find_value(Object_to_string(f));
    return apply_subr(new_f, lvals, env);
  }
  assert(listp(f));
  if (Object_to_string(car(f)) == "lambda") {
    Object lpars = cadr(f);
    Object body = caddr(f);
    Environment new_env = env;
    new_env.extend_env(lpars, lvals);
    return eval(body, new_env);
  }
  throw Evaluation_Exception(f, env, "Cannot apply a list");
  assert(false);
}

Object do_progn(Object l, Environment &env) {
  if (null(l)) return nil();
  else {
    Object a = car(l);
    if (null(cdr(l))) {
      return eval(a, env);
    }
    else {
      eval(a, env);
      return do_progn(cdr(l), env);
    }
    
  }
}

Object do_cond(Object l, Environment &env) {
  if (null(l)) return nil();
  else {
    Object a = car(l); // First condition
    Object r = eval(car(a), env);
    if (!null(r)) {
      return eval(cadr(a), env);
    }
    else {
      return do_cond(cdr(l), env);
    }
  }
}

Object do_andthen(Object l, Environment &env) {
  if (null(l) || null(cdr(l))) throw Evaluation_Exception(string_to_Object("andthen"), env, "Not enough arguments");
  else {
    Object r = eval(car(l), env);
    if (!null(r)) {
      return eval(cadr(l), env);
    }
    else {
      return nil();
    }
  }
}
