#include <iostream>
#include <fstream>

#include "database/InputBuffer.hpp"

int main(int argc, char* argv[]){
    std::unique_ptr<InputBuffer> input_buffer = std::make_unique<InputBuffer>();
    std::fstream dataFile;
    dataFile.open("log.txt", std::ios::in | std::ios::out | std::ios::app);
    while(true){
        input_buffer->print_db();
        input_buffer->read_input(input_buffer.get());
        if(input_buffer->get_buffer() == ".exit"){
            break;
        }

        if(input_buffer->get_buffer()[0] == '.'){
            
        }

        if(tolower(input_buffer->get_buffer()[0]) == 'insert'){

        }
        //Statement statement;
        //switch(prepare_statement(input_buffer, &statement)){

        //}
    }
    //std::cout << input_buffer;
};