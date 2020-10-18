#include <optional>

#include "visitor.h"
#include <unordered_map>

// A visitor that evaluates the given expression using the given
// variable mapping.
struct EvalVisitor final : public Visitor {
  // A field to keep intermediate values during evaluation. Sometimes
  // we don't have a result (e.g. when looking up undefined variables
  // or when trying to divide by zero) so the result is represented
  // using an optional.
  std::optional<int> accumulator = 0;

  // The mapping of variable names to values
  const std::unordered_map<std::string, int> var_to_value;

  explicit EvalVisitor(std::unordered_map<std::string, int> var_to_value_) :
    accumulator(std::nullopt),
    var_to_value(var_to_value_) {}
  
  virtual void visitAddition(const Addition & add);
  virtual void visitMultiplication(const Multiplication & mul);
  virtual void visitDivision(const Division & div);
  virtual void visitInteger(const Integer & n);
  virtual void visitVariable(const Variable & x);
};