#include <iostream>

#include "database/InputBuffer.hpp"

int main(int argc, char* argv[]){
    //std::unique_ptr<InputBuffer> input_buffer = std::make_unique<InputBuffer>();    
    std::unique_ptr<InputBuffer> input_buffer = std::make_unique<InputBuffer>();
    while(true){
        input_buffer->print_db();
        input_buffer->read_input(input_buffer.get());
        if(input_buffer->get_buffer() == ".exit"){
            break;
        }
    }
    //std::cout << input_buffer;
};