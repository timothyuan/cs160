#define CATCH_CONFIG_MAIN

#include "catch2/catch.hpp"
#include "frontend/lexer.h"

using namespace cs160::frontend;
using Catch::Matchers::Equals;
using Catch::Matchers::Message;

TEST_CASE("Single-token tests", "[lexer]") {
  CHECK_THAT(Lexer{}.tokenize("x") , Equals(std::vector{Token::makeId("x")}));
  CHECK_THAT(Lexer{}.tokenize("y") , Equals(std::vector{Token::makeId("y")}));
  CHECK_THAT(Lexer{}.tokenize("3") , Equals(std::vector{Token::makeNum(3)}));
  CHECK_THAT(Lexer{}.tokenize("-42") , Equals(std::vector{Token::makeNum(-42)}));
  CHECK_THAT(Lexer{}.tokenize("int") , Equals(std::vector{Token::makeType("int")}));
  CHECK_THAT(Lexer{}.tokenize("uint") , Equals(std::vector{Token::makeId("uint")}));
  CHECK_THAT(Lexer{}.tokenize("if") , Equals(std::vector{Token::makeIf()}));
  CHECK_THAT(Lexer{}.tokenize("else") , Equals(std::vector{Token::makeElse()}));
  CHECK_THAT(Lexer{}.tokenize("while") , Equals(std::vector{Token::makeWhile()}));
  CHECK_THAT(Lexer{}.tokenize("def") , Equals(std::vector{Token::makeDef()}));
  CHECK_THAT(Lexer{}.tokenize("return") , Equals(std::vector{Token::makeReturn()}));
  CHECK_THAT(Lexer{}.tokenize("output") , Equals(std::vector{Token::makeOutput()}));
  CHECK_THAT(Lexer{}.tokenize("for") , Equals(std::vector{Token::makeFor()}));
  CHECK_THAT(Lexer{}.tokenize("from") , Equals(std::vector{Token::makeFrom()}));
  CHECK_THAT(Lexer{}.tokenize("to") , Equals(std::vector{Token::makeTo()}));
  CHECK_THAT(Lexer{}.tokenize("+") , Equals(std::vector{Token::makeArithOp(ArithOp::Plus)}));
  CHECK_THAT(Lexer{}.tokenize("-") , Equals(std::vector{Token::makeArithOp(ArithOp::Minus)}));
  CHECK_THAT(Lexer{}.tokenize("*") , Equals(std::vector{Token::makeArithOp(ArithOp::Times)}));
  CHECK_THAT(Lexer{}.tokenize("<") , Equals(std::vector{Token::makeRelOp(RelOp::LessThan)}));
  CHECK_THAT(Lexer{}.tokenize("<=") , Equals(std::vector{Token::makeRelOp(RelOp::LessEq)}));
  CHECK_THAT(Lexer{}.tokenize("=") , Equals(std::vector{Token::makeRelOp(RelOp::Equal)}));
  CHECK_THAT(Lexer{}.tokenize("&&") , Equals(std::vector{Token::makeLBinOp(LBinOp::And)}));
  CHECK_THAT(Lexer{}.tokenize("||") , Equals(std::vector{Token::makeLBinOp(LBinOp::Or)}));
  CHECK_THAT(Lexer{}.tokenize("!") , Equals(std::vector{Token::makeLNeg()}));
  CHECK_THAT(Lexer{}.tokenize("(") , Equals(std::vector{Token::makeLParen()}));
  CHECK_THAT(Lexer{}.tokenize(")") , Equals(std::vector{Token::makeRParen()}));
  CHECK_THAT(Lexer{}.tokenize("{") , Equals(std::vector{Token::makeLBrace()}));
  CHECK_THAT(Lexer{}.tokenize("}") , Equals(std::vector{Token::makeRBrace()}));
  CHECK_THAT(Lexer{}.tokenize(";") , Equals(std::vector{Token::makeSemicolon()}));
  CHECK_THAT(Lexer{}.tokenize(":=") , Equals(std::vector{Token::makeAssign()}));
  CHECK_THAT(Lexer{}.tokenize(":") , Equals(std::vector{Token::makeHasType()}));
  CHECK_THAT(Lexer{}.tokenize(",") , Equals(std::vector{Token::makeComma()}));
  CHECK_THAT(Lexer{}.tokenize("["), Equals(std::vector{Token::makeLBracket()}));
  CHECK_THAT(Lexer{}.tokenize("]"), Equals(std::vector{Token::makeRBracket()}));
  CHECK_THAT(Lexer{}.tokenize("if	else"), Equals(std::vector{Token::makeIf(), Token::makeElse()}));
  CHECK_THAT(Lexer{}.tokenize("://foo\n=\n\n"), Equals(std::vector{Token::makeSemicolon(), Token::makeRelOp(RelOp::Equal)}));
}

TEST_CASE("Simple invalid token tests", "[lexer]") {
  REQUIRE_THROWS_AS(Lexer{}.tokenize("&"), InvalidLexemeError);
  REQUIRE_THROWS_AS(Lexer{}.tokenize("&&&"), InvalidLexemeError);
  REQUIRE_THROWS_AS(Lexer{}.tokenize("|"), InvalidLexemeError);
  REQUIRE_THROWS_AS(Lexer{}.tokenize(">"), InvalidLexemeError);
  REQUIRE_THROWS_AS(Lexer{}.tokenize("_"), InvalidLexemeError);
  REQUIRE_THROWS_AS(Lexer{}.tokenize("_"), InvalidLexemeError);
}

TEST_CASE("Simple whitespace and comment tests", "[lexer]") {
  CHECK_THAT(Lexer{}.tokenize("x ("), Equals(std::vector{Token::makeId("x"), Token::makeLParen()}));
  CHECK_THAT(Lexer{}.tokenize("\nwhile//\n;"), Equals(std::vector{Token::makeWhile(), Token::makeSemicolon()}));
  CHECK_THAT(Lexer{}.tokenize("  def\n\nif"), Equals(std::vector{Token::makeDef(), Token::makeIf()}));
}
