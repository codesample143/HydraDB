#include <string>
#include <iostream>
#include <memory>

class InputBuffer{
    public:
        InputBuffer();
        void print_db();
        void read_input(InputBuffer* input_buffer);
    private:
        std::string buffer;
        size_t buffer_length;
        std::ptrdiff_t input_length;
};

