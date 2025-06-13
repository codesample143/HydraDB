#include <string>

class InputBuffer{
    public:
        InputBuffer* new_input_buffer();
        void print_db();
        void read_input(InputBuffer* input_buffer);
    private:
        std::string buffer;
        size_t buffer_length;
        std::ptrdiff_t input_length;
};