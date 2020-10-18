#include "expr.h"
#include "visitor.h"

// This file contains the implementation of the acceptor methods for
// arithmetic expressions to make the visitor pattern work


void Addition::accept(Visitor & visitor) const {
  visitor.visitAddition(*this);
}

void Multiplication::accept(Visitor & visitor) const {
  visitor.visitMultiplication(*this);
}

void Division::accept(Visitor & visitor) const {
  visitor.visitDivision(*this);
}

void Integer::accept(Visitor & visitor) const {
  visitor.visitInteger(*this);
}

void Variable::accept(Visitor & visitor) const {
  visitor.visitVariable(*this);
}
