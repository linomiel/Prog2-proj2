#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "object.hh"
#include "memory.hh"

using namespace std;

class Binding {
private:
  string name;
  Object value;
public:
  Binding(string _name, Object _value);
  string get_name() const;
  Object get_value() const;
  void set_value(Object value);
};

class No_Binding_Exception: public runtime_error {
private:
  string name;
public:
  No_Binding_Exception(string _name): runtime_error("No binding for name: " + _name), name(_name) {}
  virtual ~No_Binding_Exception() throw () {}
};

class Environment {
private:
  vector<Binding> contents;
public:
  Environment();
  void add_new_binding(string name, Object value);
  void modify_env(string name, Object value);
  void extend_env(Object lpars, Object lvals);
  Object find_value(string name);
  void print(ostream& s);
};

ostream& operator << (ostream& s, Environment& env);
