#include <iostream>
#include <cassert>
#include <string>
#include <cstring> // For strdup
#include "cell.hh"
#include <cstdlib> 

using namespace std;

void Cell::check() {} // To be filled up!

Cell::cell_sort Cell::get_sort() const {
  return sort;
}

bool Cell::is_number() const {
  return sort == NUMBER;
}
bool Cell::is_string() const {
  return sort == STRING;
}
bool Cell::is_symbol() const {
  return sort == SYMBOL;
}
bool Cell::is_pair() const {
  return sort == PAIR;
}
bool Cell::is_subr() const {
  return sort == SUBR;
}

int Cell::to_number() const {
  assert(is_number());
  return value.as_number;
}

string Cell::to_string() const {
  assert(is_string());
  return string(value.as_string);
}

string Cell::to_symbol() const {
  assert(is_symbol());
  return string(value.as_symbol);
}

string Cell::to_subr() const {
  assert(is_subr());
  return string(value.as_subr);
}

Cell *Cell::to_pair_item() const {
  assert(is_pair());
  return value.as_pair.item;
}

Cell *Cell::to_pair_next() const {
  assert(is_pair());
  return value.as_pair.next;
}

Cell *Cell::nil() {
  return &cell_nil;
}

Cell::Cell() {
  make_cell_number(42); //For instance. Why not? :-)
  check();
}

Cell::Cell(Cell const &c) {
  sort = c.get_sort();
  value = c.value;
  value.as_number = 42;
  if (sort == STRING) {
    value.as_string = strdup(c.value.as_string);
  }
  else if (sort == SYMBOL) {
    value.as_symbol = strdup(c.value.as_symbol);
  }
  else if (sort == SUBR) {
    value.as_subr = strdup(c.value.as_subr);
  }
  else {
    value = c.value;
  }
}

Cell::~Cell() {
  if (sort == STRING) {
    std::free(value.as_string);
  }
  if (sort == SYMBOL) {
    std::free(value.as_symbol);
  }
  if (sort == SUBR) {
    std::free(value.as_subr);
  }
}

void Cell::make_cell_number(int a) {
  sort = NUMBER;
  value.as_number = a;
}

void Cell::make_cell_string(string s) {
  sort = STRING;
  char *p = strdup(s.c_str());	// Watch it! Allocated by malloc
  value.as_string = p;
}

void Cell::make_cell_symbol(string s) {
  sort = SYMBOL;
  char *p = strdup(s.c_str());	// Watch it! Allocated by malloc
  value.as_symbol = p;
}

void Cell::make_cell_subr(string s) {
  sort = SUBR;
  char *p = strdup(s.c_str());	// Watch it! Allocated by malloc
  value.as_subr = p;
}

void Cell::make_cell_pair(Cell* p, Cell* q) {
  sort = PAIR;
  cell_pair c;
  c.item = p;
  c.next = q;
  value.as_pair = c;
}

bool Cell::is_eq(Cell* p) {
  if (p == this) {
    return true;
  }
  if (is_symbol() || p->is_symbol() || is_subr() || p->is_subr()) {
    return false;
  }
  if (sort != p->sort) {
    return false;
  }
  else if (sort == NUMBER) {
    return (value.as_number == p->value.as_number);
  }
  else if (sort == STRING) {
    return (value.as_string == p->value.as_string);
  }
  return false;
}

Cell Cell::cell_nil = Cell();

static ostream& print_cell_pointer(ostream& s, const Cell *p);

static ostream& print_cell_pointer_aux(ostream& s, const Cell *p) {
  assert(p -> is_pair());
  for (const Cell *pp = p;; pp = pp -> to_pair_next()) {
    if (pp == Cell::nil()) break;
    print_cell_pointer(s, pp -> to_pair_item());
    if (pp -> to_pair_next() == Cell::nil()) break;
    s << " " << flush;
  }
  return s;
}

static ostream& print_cell_pointer(ostream& s, const Cell *p) {
  s << "[" << (p -> get_sort()) << "] ";
  if (p == Cell::nil()) return s << "nil" << flush;
  if (p -> is_number()) return s << p -> to_number() << flush;
  if (p -> is_string()) return s << p -> to_string() << flush;
  if (p -> is_symbol()) return s << p -> to_symbol() << flush;
  if (p -> is_subr()) return s << "<subr>" << flush;
  if (p -> is_pair()) {
    s << "(" << flush;
    print_cell_pointer_aux(s, p);
    s << ")" << flush;
    return s;
  }
  return (s << "unknown (at " << &p << ")"<< flush);
  assert(false);
}

ostream& operator << (ostream& s, const Cell *p) {
  return print_cell_pointer(s, p);
}
