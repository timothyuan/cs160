#define CATCH_CONFIG_MAIN

#include <sstream>

#include "catch2/catch.hpp"
#include "print_visitor.h"

TEST_CASE("Base cases", "[print visitor]") {
  SECTION("variables") {
    // Create an PrintVisitor that prints to the given string stream
    std::stringstream out;
    PrintVisitor print_visitor(out);

    std::unique_ptr<Expression> x = std::make_unique<Variable>("x");
    std::unique_ptr<Expression> y = std::make_unique<Variable>("y");

    x->accept(print_visitor);
    REQUIRE(out.str() == "x");

    // reset the output
    out.str("");
    
    y->accept(print_visitor);
    REQUIRE(out.str() == "y");
  }

  SECTION("integers") {
    std::stringstream out;
    PrintVisitor print_visitor(out);

    std::unique_ptr<Expression> n1 = std::make_unique<Integer>(-3);
    std::unique_ptr<Expression> n2 = std::make_unique<Integer>(0);
    std::unique_ptr<Expression> n3 = std::make_unique<Integer>(22);

    // Variables in the mapping should get their values
    n1->accept(print_visitor);
    REQUIRE(out.str() == "-3");
    // reset the output
    out.str("");

    n2->accept(print_visitor);
    REQUIRE(out.str() == "0");
    // reset the output
    out.str("");

    n3->accept(print_visitor);
    REQUIRE(out.str() == "22");
  }
}

TEST_CASE("Addition", "[print visitor]") {
  SECTION("Simple addition") {
    std::stringstream out;
    PrintVisitor print_visitor(out);

    Addition expr(std::make_unique<Integer>(2),
		  std::make_unique<Integer>(2));
    expr.accept(print_visitor);
    REQUIRE(out.str() == "(2) + (2)");
  }

  SECTION("Nested addition") {
    std::stringstream out;
    PrintVisitor print_visitor(out);

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
    expr.accept(print_visitor);
    REQUIRE(out.str() == "((4) + (8)) + (((15) + (16)) + ((23) + (42)))");
  }
}

TEST_CASE("Multiplication", "[print visitor]") {
  SECTION("Simple multiplication") {
    std::stringstream out;
    PrintVisitor print_visitor(out);

    Multiplication expr(std::make_unique<Integer>(3),
			std::make_unique<Integer>(3));
    expr.accept(print_visitor);
    REQUIRE(out.str() == "(3) * (3)");
  }

  SECTION("Nested multiplication") {
    std::stringstream out;
    PrintVisitor print_visitor(out);

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
    expr.accept(print_visitor);
    REQUIRE(out.str() == "((6) * (4)) * (((2) * (1)) * ((3) * (5)))");
  }
}

TEST_CASE("Division", "[print visitor]") {
  SECTION("Simple division") {
    std::stringstream out;
    PrintVisitor print_visitor(out);

    Division expr (std::make_unique<Integer>(65535),
		   std::make_unique<Integer>(-257));
    expr.accept(print_visitor);
    REQUIRE(out.str() == "(65535) / (-257)");
  }

  SECTION("Nested division") {
    std::stringstream out;
    PrintVisitor print_visitor(out);

    // (64 / 10) / (22 / 11)
    Division expr {
		   std::make_unique<Division>(
					      std::make_unique<Integer>(64),
					      std::make_unique<Integer>(10)),
		   std::make_unique<Division>(
					      std::make_unique<Integer>(22),
					      std::make_unique<Integer>(11))
    };
    expr.accept(print_visitor);
    REQUIRE(out.str() == "((64) / (10)) / ((22) / (11))");
  }
}
