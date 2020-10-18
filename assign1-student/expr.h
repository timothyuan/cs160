#pragma once

#include <memory>
#include <string>

// In this example, we use `struct` instead of `class` to make
// everything public by default.

// We have the following grammar for arithmetic expressions, and the
// class hierarchy below encodes this grammar.
//
// e ∈ Expression = n | add | mul | div | var
//
// add ∈ Addition = e₁ + e₂
// mul ∈ Multiplication = e₁ × e₂
// div ∈ Division = e₁ ÷ e₂
// x ∈ Variable
// n ∈ ℤ

// Forward declaration of visitors
struct Visitor;

// This is an abstract class for all expressions
struct Expression {
  // Accept the given visitor object
  virtual void accept(Visitor & visitor) const = 0;

  // We need a virtual destructor because of the virtual class
  // hierarchy
  virtual ~Expression() {}
};

// All of the classes below are complete so they are marked final to
// make the compiler catch any missing method implementations

struct Addition final : public Expression {
  // The left-hand side and right-hand sides of this addition
  //
  // Note that we used a unique_ptr because Expression is abstract and
  // this addition owns its subexpressions
  const std::unique_ptr<Expression> lhs;
  const std::unique_ptr<Expression> rhs;

  Addition(
      std::unique_ptr<Expression> lhs,
      std::unique_ptr<Expression> rhs)
      : lhs(std::move(lhs)), rhs(std::move(rhs)) {}

  
  
  void accept(Visitor & visitor) const override;
};

struct Multiplication final : public Expression {
  // The left-hand side and right-hand sides of this multiplication
  //
  // Note that we used a unique_ptr because Expression is abstract and
  // this multiplication owns its subexpressions
  const std::unique_ptr<Expression> lhs;
  const std::unique_ptr<Expression> rhs;

  Multiplication(
      std::unique_ptr<Expression> lhs,
      std::unique_ptr<Expression> rhs)
      : lhs(std::move(lhs)), rhs(std::move(rhs)) {}
  
  void accept(Visitor & visitor) const override;
};

struct Division final : public Expression {
  // The left-hand side and right-hand sides of this division
  //
  // Note that we used a unique_ptr because Expression is abstract and
  // this division owns its subexpressions
  const std::unique_ptr<Expression> lhs;
  const std::unique_ptr<Expression> rhs;
  
  Division(
      std::unique_ptr<Expression> lhs,
      std::unique_ptr<Expression> rhs)
      : lhs(std::move(lhs)), rhs(std::move(rhs)) {}

  void accept(Visitor & visitor) const override;
};

struct Integer final : public Expression {
  // The value of this integer
  const int value;

  // We declare an explicit constructor to prevent C++ from
  // automatically cast ints to Integers
  explicit Integer(int value_) : value(value_) {}
  
  void accept(Visitor & visitor) const override;
};

struct Variable final : public Expression {
  // The name of this variable
  const std::string name;

  // We declare an explicit constructor to prevent C++ from
  // automatically cast strings to Variables
  explicit Variable(std::string x) : name(x) {}
  
  void accept(Visitor & visitor) const override;
};
