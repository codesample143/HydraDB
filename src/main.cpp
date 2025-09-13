#include <iostream>
#include <fstream>
#include <memory>

#include "SQLParser.h"
#include "sql/statements.h"
#include "util/sqlhelper.h"
#include "database/InputBuffer.hpp"

int main(int argc, char* argv[]){
    std::fstream db("mydatabase.db", std::ios::in | std::ios::out | std::ios::binary); //more of an experiment than anything
    if (!db){
        db.open("mydatabase.db", std::ios::out | std::ios::binary);
    }
    //may need to clean up this logic eventually
    std::unique_ptr<InputBuffer> input_buffer = std::make_unique<InputBuffer>();
    std::fstream logFile;
    logFile.open("log.txt", std::ios::in | std::ios::out | std::ios::app);
    hsql::SQLParserResult result;

    logFile << "<Begin>" << "\n";
    //add logic for reversing the logfile in case there was some kind of exception

    std::fstream metadata_file("metadata.dat", std::ios::in | std::ios::out | std::ios::binary);
    if(!metadata_file.is_open()) {

    }

    while(true){
        input_buffer->print_db();
        input_buffer->read_input(input_buffer.get());
        hsql::SQLParser::parse(input_buffer.get()->get_buffer(), &result);

        if(input_buffer->get_buffer() == ".exit"){
            break;
        }
        const hsql::SQLStatement* statement = result.getStatement(0);
        
        // --- CREATE TABLE ---
        if(statement->isType(hsql::kStmtCreate)){
            const auto* createStatement = static_cast<const hsql::CreateStatement*>(statement);
            //
            std::string table_name = createStatement->tableName;

            uint32_t root_page_id = 1;
            size_t page_capacity = 4;
            metadata_file.seekp(0, std::ios::end);
            uint32_t id = root_page_id;
            size_t len = table_name.size();
            metadata_file.write(reinterpret_cast<char*>(&id), sizeof(id)); //4 bytes
            metadata_file.write(reinterpret_cast<char*>(&len), sizeof(len)); //32 bytes
            metadata_file.write(table_name.c_str(), len); //len bytes
            //getting information about tables
            // everything between // should be placed into a seperate function later

        } else if(statement->isType(hsql::kStmtSelect)){ //replace with more SQL logic 
            const auto* selectStatement = static_cast<const hsql::SelectStatement*>(statement);
            //
            
            //everything between // should be placed into a seperate function later
        } else {
            fprintf(stderr, "Given string is not a valid SQL query or not supported at this time.\n");
            fprintf(stderr, "%s (L%d:%d)\n",
                    result.errorMsg(),
                    result.errorLine(),
                    result.errorColumn());
        }

    }

    logFile << "<End>" << "\n";
    logFile.close();
    //dataFile.write();
    //std::cout << input_buffer;

};