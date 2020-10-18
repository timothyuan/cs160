#include "frontend/lexer.h"
#include <iostream>
#include <fstream>

using namespace cs160::frontend;

void usage(char const * programName) {
  std::cerr << "Usage: " << programName << " program.cb\n\n"
    << "This program reads given program and prints the list of tokens outputted by the lexer";
}

int main(int argc, char * argv[]) {
  if (argc != 2) {
    usage(argv[0]);
    return 1;
  }

  // Check that the file exists
  std::ifstream programFile{argv[1]};
  if (! programFile.is_open()) {
    std::cerr << "'" << argv[1] << "' does not exist or is not a regular file.\n\n";
    usage(argv[0]);
  }

  // Read the file
  std::string programText{std::istreambuf_iterator<char>(programFile), std::istreambuf_iterator<char>()};

  // Run the lexer
  Lexer lexer;
  auto tokens = lexer.tokenize(programText);

  // Print the tokens
  std::cout << "Tokens produced by the lexer:\n";
  for (auto & token : tokens) {
    std::cout << token << "\n";
  }

  return 0;
}
