#include <iostream>
#include <fstream>

#include "SQLParser.h"
#include "sql/statements.h"
#include "util/sqlhelper.h"

#include "database/InputBuffer.hpp"
#include "database/BTree.hpp"

int main(int argc, char* argv[]){
    std::fstream db("mydatabase.db", std::ios::in | std::ios::out | std::ios::binary);
    if (!db){
        db.open("mydatabase.db", std::ios::out | std::ios::binary);
    }

    std::unique_ptr<InputBuffer> input_buffer = std::make_unique<InputBuffer>();
    std::fstream logFile;
    logFile.open("log.txt", std::ios::in | std::ios::out | std::ios::app);
    hsql::SQLParserResult result;

    logFile << "<Begin>" << "\n";


    std::fstream metadata_file("metadata.dat", std::ios::in | std::ios::out | std::ios::binary);
    if(!metadata_file.is_open()) {
        metadata_file.open("metadata.dat", std::ios::out | std::ios::binary);
        metadata_file.close();
        metadata_file.open("metadata.dat", std::ios::in | std::ios::out | std::ios::binary);
    }

    while(true){
        input_buffer->print_db();
        input_buffer->read_input(input_buffer.get());
        hsql::SQLParser::parse(input_buffer.get()->get_buffer(), &result);

        if(input_buffer->get_buffer() == ".exit"){
            break;
        }
        const hsql::SQLStatement* statement = result.getStatement(0);
        
        if(result.isValid() && result.size() > 0){
            // --- CREATE TABLE ---
            if(statement->isType(hsql::kStmtCreate)){
                const auto* create = static_cast<const hsql::CreateStatement*>(statement);
                //
                uint32_t root_page_id = 1;
                size_t page_capacity = 4;
                metadata_file.seekp(0, std::ios::end);
                //getting information about tables
                std::string table_name = create->tableName;
                std::vector<std::string> results;
                // everything between // should be placed into a seperate function later

            } else if(statement->isType(hsql::kStmtInsert)){ //replace with more SQL logic 
                const auto* insertStmt = static_cast<const hsql::InsertStatement*>(statement);
            } else {
                fprintf(stderr, "Given string is not a valid SQL query or not supported at this time.\n");
                fprintf(stderr, "%s (L%d:%d)\n",
                        result.errorMsg(),
                        result.errorLine(),
                        result.errorColumn());
            }

        }

    }

    logFile << "<End>" << "\n";
    logFile.close();
    //dataFile.write();
    //std::cout << input_buffer;

};