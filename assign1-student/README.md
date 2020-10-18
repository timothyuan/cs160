# CS 160 Assignment 1: C++ and Visitor Pattern Ramp-up

**Assignment due: Thursday, April 16 11:30 PM**

Read the relevant section of [the lecture
notes](https://cs.ucsb.edu/~emre/cs160/lecture-notes.html) for the
late submission and slip day policy.

We recommend using [cppreference.com](https://en.cppreference.com/w/)
as a C++ reference.

In this assignment, you are going to learn how to:

1. use some modern C++ features such as smart pointers, 
2. implement traversals over tree-shaped data structures with visitor
design pattern, and
3. to read/write some simple unit tests with a unit testing
   framework (this part is optional and not graded).

## Smart pointers and other helper classes

Manual memory management is hard, so C++ comes with certain classes
classes that abstract away memory management and represent certain
cases that would be handled with pointers. Ideally, you should not
need to write `new` or `delete` at all. There are 4 ways that we are
going to represent references to an object, you are already familiar
with some of them:

1. C++ References (ex: `int&`): These point to *an existing
   object owned by another piece of code*. You should use them in
   places when you are sure that *the owner lives longer than the
   reference*.
2. Unique Pointers (`unique_ptr<int>`): These pointers **own** the
   object they point to. Since there can be only one owner of an
   object, unique pointers cannot be copied. When the pointer goes out
   of scope, the object is deleted so we don't need to deal with
   managing memory for them. We are going to use them in cases where
   we need to have a pointer, and we are responsible
3. Shared pointers (`shared_ptr<int>`): These pointers are like unique
   pointers, but they can be copied. Shared pointers maintain a count
   of how many references to an object exist. When the last reference
   is destroyed and the count goes to zero, the object is
   destroyed. These are useful in cases where you want an object in
   memory to be pointed by multiple locations and there is no clear
   ownership scheme. You need to be careful when using these with
   cyclic data structures. A cycle of shared pointers will never be
   destroyed, and it will leak resources like memory. You should use
   `weak_ptr` to break cycles in these cases. We are not going to deal
   with cyclic data structures for most of this class so weak pointers
   are not covered in this assignment.
4. Old school C++ pointers (`int*`): These are useful in places where
   we need a reference but the value can be null. We are trying to
   avoid using them in this class, and use references instead.

For more details on how to use shared pointers and unique pointers,
please refer to the following links:

- https://en.cppreference.com/w/cpp/memory/unique_ptr 
- https://en.cppreference.com/w/cpp/memory/shared_ptr

For this assignment, we are going to use only references and unique
pointers.
   
### Optional Values

Sometimes we have a value that may or may not be present. For example,
when we are representing an `if` statement in a compiler, there may or
may not be an `else` branch. `std::optional` represents such
values. In our hypothetical example, we can represent the if statement
like so:

```
// An abstract class for statements
class Statement { /* ... */ };

// A block is a sequence of statements
using Block = std::vector<std::unique_ptr<Statement>>;

// An assignment statement
class Assignment : public Statement { /* ... */ };

// An if statement
class If : public Statement {
 public:
  // the condition of the if statement
  RelationalExpr guard;
  // the true branch
  Block true_branch;
  // the false branch, which may or may not exist
  std::optional<Block> false_branch;
};
```

We can check if an optional has a value by using it like a Boolean (it
acts like true if it has a value, otherwise it acts like false). To
access the value inside the optional, we use `operator *` and
`operator ->`, just like a normal pointer.  We can create an empty
optional using `std::nullopt`. For example,

```
void deleteFalseBranch(If & ifStmt) {
  ifStmt.false_branch = std::nullopt;
}

void printNumberOfStatements(const If & ifStmt) {
  size_t stmtCount = 0;
  
  stmtCount += ifStmt.true_branch.size();
  
  // check if there is a false branch
  if (ifStmt.false_branch) {
	stmtCount += ifStmt.false_branch->size();
	// The following would also work:
	// stmtCount += (*ifStmt.false_branch).size();
  }
  
  std::cout << "The conditional has " << stmtCount << " statements in its branches";
}
```

For more details, see https://en.cppreference.com/w/cpp/utility/optional

### Choosing between `uniq_ptr` and `optional`

Both optionals and unique pointers can represent values that are
owned, and may not exist. The general rule of thumb is: prefer
optionals for values that the size is known in compile time
(non-abstract classes) and use `unique_ptr` otherwise. The reasons for
this strategy are:

- Optionals allocate value in place, so the value is more likely to be
  in the cache when you are accessing it, making your programs faster.
- Since the values are allocated in place, optionals need to know the
  size of the object at compile time. This is not possible for cases
  with abstract classes. To give an example, consider the following
  class hierarchy for some arithmetic expressions:
  
```c++
//    Expression
//      /  \
//     /    \
// Number   Addition
 
class Expression {}

class Number : public Expression {
  int value;
}

class Addition : public Expression {
  unique_ptr<Expression> leftHandSide;
  unique_ptr<Expression> rightHandSide;
}
```

We don't know the size of an expression object at compile time because
it can be a number or an addition and they have different sizes. So,
we need to use pointers to represent abstract expression objects.

## Visitor pattern

A lot of the algorithms we are going to go over later in class (such
as code generation and type checking) work by recursively traversing
the input program. So, we need to have a way of recursively going into
parts of a program and inspecting them. Other languages like Scala,
Rust, OCaml, and Haskell provide a mechanism called *pattern matching*
that allows us writing such recursive algorithms. In object oriented
languages like C++, we use the [visitor design
pattern](https://en.wikipedia.org/wiki/Visitor_pattern) to achieve
this goal.

For this assignment, you are going to implement two visitors that
recursively traverse arithmetic expressions (like `3 + 4`, `x * 2`,
`32`). The overall structure of these recursive algorithms are like:

```
let foo(expr) =
  if expr is an addition -> do ...
  if expr is a number -> do ...
  ...
```

Normally, we can implement such functions as virtual methods for each
case. For example, if we have the class hierarchy above, we can add
`virtual std::string toString() const` to each of these classes to
implement a recursive `toString` function. However, this requires
adding methods to a large class hierarchy when we have lots of
functions. The idea behind the visitor pattern is to reify the notion
of recursive traversal so we can implement new visitors without
modifying the original class hierachy, so we maintain modularity in
our code.

See `expr.h` for the definition of arithmetic expressions, and
`visitor.h` for the definition of the abstract visitor. The way the
visitors work will be covered in the discussion section.

Also, note that `EvalVisitor` has an accumulator to return
values. Writing a generic abstract visitor in C++ that allows visitors
returning different types of values is tricky and requires use of
`std::any` and extra indirection. So, we are going to use accumulators
to keep things simple. As a note, this problem is easier to solve in
Java because of its object representation and its generics system
being more relaxed than C++ templates.

## What you need to implement

You need to implement the visitors in `eval_visitor.cpp` and
`print_visitor.cpp`.

Before starting implementing the visitors, you should read `expr.h`
and `visitor.h`, and the associated `.cpp` files.

## How to build the assignment

 - To build all the tests and executables, simply run `make`.
 - To build and run the tests, run `make test`.
 - To clean up the files created during the build, run `make clean`.

You can also give `make` argument `-jN` to run up to `N` processes
while building your code. This can reduce build times especially if
you just ran `make clean`.

### GCC Versions

The `Makefile` provided to you uses `g++` as the C++ compiler. You can
use any compatible C++ compiler like Clang by changing the first line
of `Makefile` but we encourage using the same compiler as the one on
GradeScope. We will use `g++` to compile your code on GradeScope. The
template we provided works on CSIL as is so you do not need to change
the compiler on CSIL.

CSIL and GradeScope use GCC 10.2 and 10.1 respectively, so we
encourage you to install and use GCC 10 (you may get different
behavior with different compilers and versions if your code has
undefined behavior, which it should not). Please check your GCC
version especially on macOS because the default installation runs
Clang when invoking the `g++` command. You can install GCC 10 on macOS
using Homebrew (then you may need to use the `g++-10` command). It is
also available on Linux distros sometimes through additional package
repositories.

## How to test your code

We included some simple unit tests for all the classes you need to
implement.  These unit tests are for sanity checking and are not
comprehensive by any means, see below for how we are planning to test
your submissions for grading purposes.  To run the tests, simply run
`make test`. In the template given to you, all the tests fail with a
failure message like the following (once you completed the assignment
correctly, it should pass all tests):

```
eval_visitor_test.cpp:113: FAILED:
  REQUIRE( eval_visitor.accumulator == std::optional{-255} )
with expansion:
  {?} == {?}
```

Here, the first two lines gives the check that failed and its location
in the test file. The last line means that the test library does not
know how to print the values on the left-hand side and the right-hand
side (it does not know how to print optionals). For this case, it may
help to print the values right before to debug the case.

### Testing with custom inputs

You can add more test cases in `_test.cpp` files
(e.g. `eval_visitor_test.cpp`) and run them with `make test`. Please
read the documentation of Catch2 to learn how to write your own
tests--doing so is not a necessary part of the assignment but it can
increase your confidence in your code.

### Testing via GradeScope

Later this week, we will enable submission via GradeScope and your
assignments will be tested against a more comprehensive and larger
test suite. Auto-grader on GradeScope will give you feedback on your
assignment as well. You will be able to submit your assignment
multiple times and get feedback before submitting a final solution.

We will explain the details on the auto-grader once it is online.

## What to submit

You are going to submit your whole assignment through GradeScope. We
are going to consider only your changes to the following files
while grading and ignore changes in other files and additional
files:

- `eval_visitor.cpp`
- `print_visitor.cpp`

We are going to clarify submission instructions once GradeScope
is online.

Your submitted C++ files (the ones listed above) need to compile with
the skeleton code given to you, otherwise you automatically fail the
assignment.

## A note if you are using version control

If you are using services like GitHub and GitLab, please create
private repositories. There have been incidents of plagiarism in the
past where some students copied others' solutions from public
repositories. It can be hard to judge who copied from whom in some of
these cases, so we urge you to be safe and keep your code in a private
repository.
