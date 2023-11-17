#include <iostream>

#include <fstream>
#include <istream>

#include "hanparser.h"

int main(int argc, char** argv)
{
    HanParser p;

    std::ifstream fileInput;
    std::istream* stream = &std::cin;

    if (argc == 2) {
        fileInput.open(argv[1]);
        stream = &fileInput;
    }

    std::string line;
    while (*stream) {
        std::getline(*stream, line);
        p.appendLine(line);
    }

    return 0;
}
