#include <iostream>
#include <fstream>

#include "database/InputBuffer.hpp"

int main(int argc, char* argv[]){
    std::unique_ptr<InputBuffer> input_buffer = std::make_unique<InputBuffer>();
    std::fstream dataFile;
    dataFile.open("log.txt", std::ios::in | std::ios::out | std::ios::app);
    dataFile << "<Begin>" << "\n";
    while(true){
        input_buffer->print_db();
        input_buffer->read_input(input_buffer.get());

        if(input_buffer->get_buffer() == ".exit"){
            break;
        }

        if(input_buffer->get_buffer()[0] == '.'){
            
        }

        if(input_buffer->get_buffer().find("insert") != std::string::npos){ //has issues with being able to query, also idk comparison functions in c++, insertion will happen by only. use .find to get a valid index and ensure its not nothing, then write. 
            //insert ** into ** 
            //dataFile.write(input_buffer->get_buffer().c_str(), input_buffer->get_buffer().size()); //instead of writing, store in a buffer and only write at the end?
            dataFile << input_buffer->get_buffer() << "\n";
            dataFile.flush();
        } 
        //Statement statement;
        //switch(prepare_statement(input_buffer, &statement)){

        //}
    }

    dataFile << "<End>" << "\n";
    dataFile.close();
    //dataFile.write();
    //std::cout << input_buffer;

};