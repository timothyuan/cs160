CXX=g++-10
CXXFLAGS=-std=c++17 -Wall -I. -fPIC -g
LDFLAGS=

PRINT_SRC= print_visitor_test.cpp print_visitor.cpp
PRINT_I = print_visitor.h

EVAL_SRC = eval_visitor_test.cpp eval_visitor.cpp
EVAL_I = eval_visitor.h

EXPR_SRC = expr.cpp
EXPR_I = expr.h

VISITOR_I = visitor.h

.PHONY: test clean all

all: build/eval_visitor_test build/print_visitor_test

build/eval_visitor_test: $(EVAL_SRC) $(EVAL_I) $(VISITOR_I) $(EXPR_SRC) $(EVAL_I)
	$(CXX) $(CXXFLAGS) $(EVAL_SRC) $(EXPR_SRC) -o build/eval_visitor_test

build/print_visitor_test: $(PRINT_SRC) $(PRINT_I) $(VISITOR_I) $(EXPR_SRC) $(EVAL_I)
	$(CXX) $(CXXFLAGS) $(PRINT_SRC) $(EXPR_SRC) -o build/print_visitor_test

test: build/print_visitor_test build/eval_visitor_test
	./build/print_visitor_test
	./build/eval_visitor_test

clean:
	rm build/*
