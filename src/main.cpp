#include <iostream>
#include <fstream>
#include "SQLParser.h"
#include "database/InputBuffer.hpp"

int main(int argc, char* argv[]){
    std::unique_ptr<InputBuffer> input_buffer = std::make_unique<InputBuffer>();
    std::fstream logFile;
    logFile.open("log.txt", std::ios::in | std::ios::out | std::ios::app);
    hsql::SQLParserResult result;

    logFile << "<Begin>" << "\n";
    while(true){
        input_buffer->print_db();
        input_buffer->read_input(input_buffer.get());
        hsql::SQLParser::parse(input_buffer.get()->get_buffer(), &result);

        if(input_buffer->get_buffer() == ".exit"){
            break;
        }

        if(result.isValid() && result.size() > 0){
            const hsql::SQLStatement* statement = result.getStatement(0);
            if(statement->isType(hsql::kStmtSelect)){
                const auto* select = static_cast<const hsql::SelectStatement*>(statement);
            }

        }

    }

    logFile << "<End>" << "\n";
    logFile.close();
    //dataFile.write();
    //std::cout << input_buffer;

};