# CS 160 Assignment 2: Lexer for C♭

**Assignment due: Thursday, Oct 22 11:59 PM**

Read the relevant section of [the lecture
notes](https://cs.ucsb.edu/~emre/cs160/lecture-notes.html) for the
late submission and slip day policy.

In this assignment, you are going to implement the lexer for your
compiler.

## What is provided

We provide you with a `Token` class that represents the tokens your
lexer needs to create, and a minimal set of unit tests for sanity
checking purposes. You are encouraged to test your assignments with
other test cases as well.

The token interface is defined in `frontend/token.h` and you do not
need to worry about the implementation details in `frontend/token.cpp`
although you are free to read it. Here is an overview of tokens:
  - Each token has a type (a value of type `TokenType` like
    `TokenType::If`), you can get the type of a token using `type()`
    method.
  - Each token may have a value, different token types carry different
    values. You can get the value inside a token using
    `stringValue()`, `intValue()`, ... methods. Note that, if you call
    one of these methods but token does not hold a value of that kind
    then the method throws an exception (e.g., if you call
    `stringValue()` on a token of type `TokenType::Num`, an exception
    is thrown).
  - You can compare tokens for equality or print them using C++ I/O
    streams (e.g. `cout`).
  - You need to construct Tokens using static builder methods named
    `Token::makeXXX`. For example, to build an identifier token with
    value `x`, you should call `Token::makeId("x")`.

Besides `Token` class, you are given the enumerations `TokenType`,
`ArithOp`, `RelOp`, and `LBinOp`. `TokenType` enumerates different
types of tokens. The other three enumerations list different cases for
their corresponding token types so we can distinguish different
arithmetic operators, for example. These enumerations are scoped so
when you need to access an element of them, you need to specify the
full name of the enum. For example, `TokenType::LParen`,
`ArithOp::Plus` are valid but `LParen`, `Plus` are invalid.

The interface for your lexer is defined in `frontend/lexer.h` and your
implementation of the lexer should go into this file and
`frontend/lexer.cpp`.
  
`token_test.cpp` file contains tests for `Token` class which
demonstrate how to use the aforementioned methods. Similarly,
`lexer_test.cpp` contains some simple tests for `Lexer` class.

## What you need to implement

You need to implement the `tokenize` method of `Lexer` class. This
function takes a program text like the following as input:

```
if (1 < 2) {
  output x + 3;
}
```

and returns the result of tokenizing this input program as a vector of
tokens like

```
<If>
<LParen>
<Num,1>
<RelOp,<>
<Num,2>
<RParen>
<LBrace>
<Output>
<Id,x>
<ArithOp,+>
<Num,3>
<Semicolon>
<RBrace>
```

as output. To implement this method, you need to do the following:

1. Build the NFA for each lexeme and connect them to build a final
   NFA, as demonstrated in Lecture 4, example 1.
2. Then you need to implement this NFA. You have several options:
  - Convert the NFA to a DFA using powerset construction
    (a.k.a. Thompson's construction) by hand, then implement the DFA
    in code, like the examples in lecture 4.
  - Implement the NFA directly using Thompson's construction (by
   maintaining a set of states after consuming each symbol rather than
   a single state). You *should not* implement the NFA using the naive
   backtracking algorithm as it has exponential-time worst-case
   behavior.
  
  You also need to resolve ambiguities in your implementation using
  the following heuristics:
  - Longest match heuristic: `whileelse` should correspond to the
    token `<Id, whileelse>`
  - Keywords are prioritized over identifiers: `while` should yield
    token `<While>`.

The list of lexemes as regular expressions, and corresponding tokens
is posted as a handout on Slack. The handout also lists the rules for
whitespace and comments you should skip. The slides also give the
pseudocode for the lexer.

## How to build the assignment

 - To build all the tests and executables, simply run `make`.
 - To build and run the tests, run `make test`.
 - To clean up the files created during the build, run `make clean`.

You can also give `make` argument `-jN` to run up to `N` processes
while building your code. This can reduce build times especially if
you just ran `make clean`.

The `Makefile` provided to you uses `g++` as the C++ compiler. You can
use any compatible C++ compiler like Clang by changing the first line
of `Makefile`. We will use `g++` to compile your code on
GradeScope. The template we provided works on CSIL as is so you do not
need to change the compiler on CSIL. The specific versions of GCC we
are using are:

- GCC 10.2 on CSIL
- GCC 10.1 on GradeScope

## How to test your lexer

We included some simple unit tests for both `Token` class and `Lexer`
class.  These unit tests are for sanity checking and are not
comprehensive by any means, see below for how we are planning to test
your submissions for grading purposes.  To run the tests, simply run
`make test`. In the template given to you, all lexer tests fail with a
failure message like the following (once you implement your lexer, it
should pass all tests):

```
frontend/lexer_test.cpp:11: FAILED:
  CHECK_THAT( Lexer{}.tokenize("x"), Equals(std::vector{Token::makeId("x")}) )
with expansion:
  {  } Equals: { <Id,x> }
```

Here, the first two lines gives the check that failed and its location
in the test file. The last line means that the lexer produced an empty
vector (`{ }`) but it was expected to produce a vector containing
token `<Id,x>` (`{ <Id,x> }`).

### Testing with custom inputs

If you have custom C♭ programs that you want to test your assignment
with, build the lexer by invoking `make` first. Then you can run your
lexer on arbitrary programs by running `build/c1 <program>`. For
example, suppose a file named `test1.cb` has the following contents:

```
output x + 3
```

Then, running `build/c1 test1.cb` will print the list of tokens
outputted by your lexer and you should get the following output if
your lexer is working correctly:

```
<Output>
<Id,x>
<ArithOp,+>
<Num,3>
```

### Testing via GradeScope

Later this week, we will enable submission via GradeScope and your
assignments will be tested against a comprehensive and much larger
test suite. Auto-grader on GradeScope will give you feedback on your
assignment as well. You will be able to submit your assignment
multiple times and get feedback before submitting a final solution.

The autograder has a 1 hour time limit: Once you submit your homework,
and got feedback from the autograder (in terms of number of passing
tests), you

## What to submit

You are going to submit your whole assignment through GradeScope. We
are going to consider only your changes to `lexer.h` and `lexer.cpp`
while grading and ignore changes in other files and additional
files. We are going to clarify submission instructions once GradeScope
is online.

Your submitted `lexer.h` and `lexer.cpp` need to compile with the
skeleton code given to you, otherwise you automatically fail the
assignment.
