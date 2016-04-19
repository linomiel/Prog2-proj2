#pragma once

#include "object.hh"
#include "env.hh"
#include "eval.hh"
#include "subr.hh"
#include <stdio.h>
#include <cassert>
#include <cstdlib> 

extern Object just_read;
extern "C" int yyparse();
extern "C" FILE *yyin;

void yyrestart(FILE *new_file);

extern bool debug;

class Directive_Exception: public runtime_error {
private:
  string name;
  string message;
public:
Directive_Exception(string _name, string _message):
  runtime_error("Directive error! " + _name + ": " + _message), name(_name), message(_message) {}
  virtual ~Directive_Exception() throw () {}
};

bool handle_directive (Object l, Environment &env);
void top_level(Environment &env);
