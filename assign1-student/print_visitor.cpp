#include "print_visitor.h"

void PrintVisitor::visitAddition(const Addition & add) {
  out << "(";
  add.lhs->accept(*this);
  out << ") + (";
  add.rhs->accept(*this);
  out << ")";
}
void PrintVisitor::visitMultiplication(const Multiplication & mul) {
  out << "(";
  mul.lhs->accept(*this);
  out << ") * (";
  mul.rhs->accept(*this);
  out << ")";
}
void PrintVisitor::visitDivision(const Division & div) {
  out << "(";
  div.lhs->accept(*this);
  out << ") / (";
  div.rhs->accept(*this);
  out << ")";
}
void PrintVisitor::visitInteger(const Integer & n) {
  out << n.value;
}
void PrintVisitor::visitVariable(const Variable & x) {
  out << x.name;
}
