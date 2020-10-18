#pragma once

#include "expr.h"

// This is the abstract class for all visitors. It has one method for
// each type of expression, mimicking the "if expr is addition do this
// ..." part of the recursive algorithm structure.
struct Visitor {
  // We need a virtual destructor because of the virtual class
  // hierarchy
  virtual ~Visitor() {}
  
  virtual void visitAddition(const Addition & add) = 0;
  virtual void visitMultiplication(const Multiplication & mul) = 0;
  virtual void visitDivision(const Division & div) = 0;
  virtual void visitInteger(const Integer & n) = 0;
  virtual void visitVariable(const Variable & x) = 0;
};
