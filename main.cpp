#include <iostream>
#include "vm.h"
#include <vector>
#include <fstream>

using std::string , std::ifstream , std::getline, std::vector, std::cout;


int main(int argc, char* argv[])
{
    vector<string> btcode;

    ifstream file(argv[1]);
    string line = "";

    if (file.is_open()) 
    {
        while (file >> line) 
        {
            btcode.push_back(line);
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file: " << argv[1] << "\n";
        return 1;
    }

    VM vm;
    vm.main(btcode);

    return 0;    
}
