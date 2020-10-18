#include <optional>
#include <iostream>

int maybe_return_int(bool b){ // -1 means no value
    if(b){
        return 5;
    }else{
        return -1;
    }
}

std::optional<std::string> optional_return_string(bool b){ //will return an empty optional on failure
    if(b){
        return "Some String";
    }else{
        return std::nullopt;
    }
}


int main(){
    
    // One way to call
    std::cout << "Calling optional return with argument false "  << optional_return_string(false).value_or("Empty") << std::endl;
    std::cout << "Calling optional return with argument true  "  << optional_return_string(true).value_or("Empty") << std::endl;


    // Can also use the return as a guard on function returns
    if(std::optional<std::string> a = optional_return_string(false)){
        std::cout << "won't get here" << std::endl;
    }

    if(std::optional<std::string> b = optional_return_string(true)){
        std::cout << "will get here" << std::endl;
    }



}