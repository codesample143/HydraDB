#include <string>
#include <cstdlib>
#include <filesystem>

int main(){
    std::string PATH = "/usr/local/bin/";

    #ifndef _WIN32

    #elif __APPLE__
        std::string PATH = "/usr/local/bin/";
        std::system(PATH);

    #else

    #endif
}