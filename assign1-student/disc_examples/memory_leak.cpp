#include <cstring>
#include <memory>

#define BUF_SIZE 409600

// This function leaks data
void raw_pointer_fn(){
    char* str = new char [BUF_SIZE];  
    std::memset(str, 'c', BUF_SIZE);
    //delete[] str; // Oops, we forgot to call delete! 
}

// This function cleans up after itself
void smart_pointer_fn(){
    std::unique_ptr<char[]> str = std::make_unique<char[]>(BUF_SIZE);  
    std::memset(str.get(), 'c', BUF_SIZE);

    // auto a = str[409600*5]; // smart pointers aren't THAT smart, won't bounds check
    // as soon as  str goes out of scope, the memory will be freed
}

int main(){
    for(int i = 0; i < 4096; i++){
        raw_pointer_fn();
        //smart_pointer_fn();
    }

    while(1){}
}