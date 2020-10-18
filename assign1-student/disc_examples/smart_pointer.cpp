#include <memory>
#include <stdio.h>

// In c++ structs are full on classes, only with public access by default
struct ExampleClass{
    int x;
    char c;
    ExampleClass(int x, char c):x(x), c(c) {}
};

int main() {
    // Examples pointing to an int
    //========================================================================    
    printf("Primitive Examples \n\n"); 
    int* raw = new int; //request a single int be allocated for you on the heap
    std::unique_ptr<int> un(new int);
    printf("raw address: %p, unique_ptr address: %p \n", raw, un.get());

    printf("before assignment: raw value: %i, unique_ptr: %i \n", *raw, *un);
    *raw = 5;
    *un = 6;
    printf("after assigment: raw value: %i, unique_ptr: %i \n", *raw, *un);
    printf("unique_ptr raw dereference: %i \n", *(un.get()) ); // don't do this

    // Example pointing to an object
    //========================================================================
    printf("Object Examples \n\n");

    ExampleClass* raw2 = new ExampleClass(1, 'r');
    std::unique_ptr<ExampleClass> un2 = std::make_unique<ExampleClass>(4,'u'); //you don't NEED to use make_unique, you could use a new ExampleClass in the constructor.. but this is reccomended pracrtice.

    printf("After Construction: raw2->x: %i, un2->x: %i \n", raw2->x, un2->x);
    raw2->x = 7;
    un2->x = 8;
    printf("After Construction: raw2->x: %i, un2->x: %i \n", raw2->x, un2->x);
}