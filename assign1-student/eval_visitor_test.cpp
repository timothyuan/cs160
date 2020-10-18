#define CATCH_CONFIG_MAIN

#include "catch2/catch.hpp"
#include "eval_visitor.h"

TEST_CASE("Base cases", "[eval visitor]") {
  SECTION("variables") {
    // Create an EvalVisitor with mapping x ↦ 2, y ↦ 3
    EvalVisitor eval_visitor({{"x", 2}, {"y", 3}});

    std::unique_ptr<Expression> x = std::make_unique<Variable>("x");
    std::unique_ptr<Expression> y = std::make_unique<Variable>("y");
    std::unique_ptr<Expression> z = std::make_unique<Variable>("z");

    // Variables in the mapping should get their values
    x->accept(eval_visitor);
    REQUIRE(eval_visitor.accumulator == std::optional{2});
    y->accept(eval_visitor);
    REQUIRE(eval_visitor.accumulator == std::optional{3});

    // Variables not in the mapping should evaluate to nothing
    z->accept(eval_visitor);
    REQUIRE(eval_visitor.accumulator == std::nullopt);
  }

  SECTION("integers") {
    // Create an EvalVisitor with an empty mapping
    EvalVisitor eval_visitor({});

    std::unique_ptr<Expression> n1 = std::make_unique<Integer>(-3);
    std::unique_ptr<Expression> n2 = std::make_unique<Integer>(0);
    std::unique_ptr<Expression> n3 = std::make_unique<Integer>(22);

    // Variables in the mapping should get their values
    n1->accept(eval_visitor);
    REQUIRE(eval_visitor.accumulator == std::optional{-3});
    n2->accept(eval_visitor);
    REQUIRE(eval_visitor.accumulator == std::optional{0});
    n3->accept(eval_visitor);
    REQUIRE(eval_visitor.accumulator == std::optional{22});
  }
}

TEST_CASE("Addition", "[eval visitor]") {
  SECTION("Simple addition") {
    EvalVisitor eval_visitor({});

    Addition expr(std::make_unique<Integer>(2),
		  std::make_unique<Integer>(2));
    expr.accept(eval_visitor);
    REQUIRE(eval_visitor.accumulator == std::optional{4});
  }

  SECTION("Nested addition") {
    EvalVisitor eval_visitor({});

    // (4 + 8) + ((15 + 16) + (23 + 42))
    Addition expr(
		  std::make_unique<Addition>(
					     std::make_unique<Integer>(4),
					     std::make_unique<Integer>(8)),
		  std::make_unique<Addition>(
					     std::make_unique<Addition>(
									std::make_unique<Integer>(15),
									std::make_unique<Integer>(16)),
					     std::make_unique<Addition>(
									std::make_unique<Integer>(23),
									std::make_unique<Integer>(42))
					     ));
    expr.accept(eval_visitor);
    REQUIRE(eval_visitor.accumulator == std::optional{108});
  }
}

TEST_CASE("Multiplication", "[eval visitor]") {
  SECTION("Simple multiplication") {
    EvalVisitor eval_visitor({});

    Multiplication expr(std::make_unique<Integer>(3),
			std::make_unique<Integer>(3));
    expr.accept(eval_visitor);
    REQUIRE(eval_visitor.accumulator == std::optional{9});
  }

  SECTION("Nested multiplication") {
    EvalVisitor eval_visitor({});

    // 6! = (6 * 4) * ((2 * 1) * (3 * 5))
    Multiplication expr(
			std::make_unique<Multiplication>(
							 std::make_unique<Integer>(6),
							 std::make_unique<Integer>(4)),
			std::make_unique<Multiplication>(
							 std::make_unique<Multiplication>(
											  std::make_unique<Integer>(2),
											  std::make_unique<Integer>(1)),
							 std::make_unique<Multiplication>(
											  std::make_unique<Integer>(3),
											  std::make_unique<Integer>(5))
							 ));
    expr.accept(eval_visitor);
    REQUIRE(eval_visitor.accumulator == std::optional{720});
  }
}

TEST_CASE("Division", "[eval visitor]") {
  SECTION("Simple division") {
    EvalVisitor eval_visitor({});

    Division expr(std::make_unique<Integer>(65535),
		  std::make_unique<Integer>(-257));
    expr.accept(eval_visitor);
    REQUIRE(eval_visitor.accumulator == std::optional{-255});
  }

  SECTION("Division by zero") {
    EvalVisitor eval_visitor({});

    Division expr(std::make_unique<Integer>(33),
		  std::make_unique<Integer>(0));
    expr.accept(eval_visitor);
    REQUIRE(eval_visitor.accumulator == std::nullopt);
  }

  SECTION("Nested division") {
    EvalVisitor eval_visitor({});
    // (64 / 10) / (22 / 11) = 3 (using integer division)
    Division expr(
		  std::make_unique<Division>(
					     std::make_unique<Integer>(64),
					     std::make_unique<Integer>(10)),
		  std::make_unique<Division>(
					     std::make_unique<Integer>(22),
					     std::make_unique<Integer>(11))
		  );
  expr.accept(eval_visitor);
  REQUIRE(eval_visitor.accumulator == std::optional{3});
}
}
