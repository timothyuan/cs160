#include "visitor.h"
#include <ostream>

// A visitor that prints the given expression to the given stream
struct PrintVisitor final : public Visitor {
  // The output stream for printing
  std::ostream & out;

  explicit PrintVisitor(std::ostream & out_) : out(out_) {}
  
  virtual void visitAddition(const Addition & add);
  virtual void visitMultiplication(const Multiplication & mul);
  virtual void visitDivision(const Division & div);
  virtual void visitInteger(const Integer & n);
  virtual void visitVariable(const Variable & x);
};
