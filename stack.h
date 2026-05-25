#pragma once

#include <vector>
#include <map>
#include <string>

#include "register.h"

using std::string;
using std::vector;
using std::map;

struct StackManager
{
    vector<int> intStack;
    vector<char> charStack;
    vector<double> doubleStack;

    bool push(int& counter, const vector<string>& btcode);

    bool top(int& counter, const vector<string>& btcode);

    bool pop(int& counter, const vector<string>& btcode);

    bool topToReg(
        int& counter,
        const vector<string>& btcode,
        map<string, Register>& registers
    );

    bool dup(
        int& counter,
        const vector<string>& btcode
    );

    bool handleArithematic(
        int& counter,
        const vector<string>& btcode,
        map<string, Register>& registers,
        const string& instruction
    );
};
