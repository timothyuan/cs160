#include "eval_visitor.h"

void EvalVisitor::visitAddition(const Addition & add) {
  add.lhs->accept(*this);
  std::optional<int> left = accumulator;
  add.rhs->accept(*this);
  std::optional<int> right = accumulator;
  accumulator = left && right ? std::optional<int>{left.value()+right.value()} : std::nullopt;

}
void EvalVisitor::visitMultiplication(const Multiplication & mul) {
  mul.lhs->accept(*this);
  std::optional<int> left = accumulator;
  mul.rhs->accept(*this);
  std::optional<int> right = accumulator;
  accumulator = left && right ? std::optional<int>{left.value()*right.value()} : std::nullopt;
}
void EvalVisitor::visitDivision(const Division & div) {
  div.lhs->accept(*this);
  std::optional<int> left = accumulator;
  div.rhs->accept(*this);
  std::optional<int> right = accumulator;
  accumulator = left && right.value_or(0)!=0 ? std::optional<int>{left.value()/right.value()} : std::nullopt;
}
void EvalVisitor::visitInteger(const Integer & n) {
  accumulator = n.value;
}
void EvalVisitor::visitVariable(const Variable & x) {
  try {
    accumulator = var_to_value.at(x.name);
  } catch (...){
    accumulator = std::nullopt;
  }
}
