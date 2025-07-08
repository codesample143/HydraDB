#include "InputBuffer.hpp"

InputBuffer::InputBuffer(){
    buffer = "";
    buffer_length = 0;
    input_length = 0;
};

void InputBuffer::print_db(){
    std::cout << "Hydra > ";
}


void InputBuffer::read_input(InputBuffer* input_buffer){
    std::getline(std::cin, buffer);
    input_buffer->input_length = buffer.size() - 1;
    input_buffer->buffer[buffer.size()] = 0; //unsure if this works or not
    //std::cout << input_buffer->buffer << std::endl;
    //check for errors in getline
    //set input_length, buffer_length
};


std::string InputBuffer::get_buffer(){
    return buffer;
}


std::string InputBuffer::set_buffer(InputBuffer* input_buffer){

}