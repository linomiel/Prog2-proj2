#include <iostream>
#include <cassert>
#include <string>
#include "object.hh"
#include "memory.hh"

using namespace std;

Object nil() {
  return Cell::nil();
}

bool null(Object l) {
  return l == nil();
}

Object cons(Object a, Object l) {
  Object p = Memory::allocate();
  p -> make_cell_pair(a, l);
  //std::cout << "New cons " << p << std::endl;
  return p;
}

Object car(Object l) {
  assert(!null(l));
  return l -> to_pair_item();
}

Object cdr(Object l) {
  assert(!null(l));
  return l -> to_pair_next();
}

Object empty() {
  return nil();;
}

bool is_empty(Object l) {
  return null(l);
}

bool eqp(Object a, Object b) {
  return a->is_eq(b);
}

Object number_to_Object(int n) {
  Object p = Memory::allocate();
  p -> make_cell_number(n);
  //std::cout << "New number " << p << std::endl;
  return p;
}

Object string_to_Object(string s) {
  Object p = Memory::allocate();
  p -> make_cell_string(s);
  //std::cout << "New string " << p << std::endl;
  return p;
}

Object symbol_to_Object(string s) {
  Object p = Memory::allocate();
  p -> make_cell_symbol(s);
  //std::cout << "New symbol " << p << std::endl;
  return p;
}

Object subr_to_Object(string s) {
  Object p = Memory::allocate();
  p -> make_cell_subr(s);
  //std::cout << "New subr " << p << std::endl;
  return p;
}

int Object_to_number(Object l) {
  return l -> to_number();
}

string Object_to_string(Object l) {
  assert(l -> is_string() || l -> is_symbol() || l -> is_subr());
  if (l -> is_string()) return l -> to_string();
  if (l -> is_symbol()) return l -> to_symbol();
  if (l -> is_subr()) return l -> to_subr();
  assert(false);
}
