#pragma once
#include "frontend/token.h"
#include <vector>
#include <stdexcept>
#include <unordered_map>

namespace cs160::frontend {

class DFA{
public:
  DFA();
  std::unordered_map<int, std::unordered_map<char, int> > transitions;
  std::unordered_map<int, std::optional<TokenType> > accept;
  void add_transitions(char a, char b, int start, int end);
  int delta(int state, char a);
  bool isAccepted(int state);
};

// The lexer should throw this exception if the input program contains invalid lexemes.
struct InvalidLexemeError : public std::runtime_error {
  InvalidLexemeError() : runtime_error("Invalid lexeme in input program") {}
};

// This is the lexer class you need to implement. The function you need to implement is the tokenize() method. You can define other class members such as fields or helper functions.
class Lexer final {
 public:
  // The entry point of the lexer you need to implement. It takes the program text as the argument and produces a vector of tokens as the result of lexing the program text.
  //
  // If the input program contains invalid lexemes (lexemes that are outside our specification), this method should throw InvalidLexemeError.
  //
  // The implementation of this method should go into lexer.cpp
  std::vector<Token> tokenize(const std::string & programText);
};

}  // namespace cs160::frontend
