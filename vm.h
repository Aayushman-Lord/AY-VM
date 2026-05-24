#pragma once
#include <iostream>
#include <vector>

struct Register
{
    char charValue;
    double doubleValue;
    int intValue;

    Register(){}

    void setCharValue(char value) 
    {
        charValue = value; 
    }
    void setDoubleValue(double value) 
    {
        doubleValue = value; 
    }
    void setIntValue(int value) 
    {
        intValue = value; 
    }
};

struct VM
{
    std::vector<Register> registers; 

    void createRegister()
    {
        Register reg;

        reg.charValue = ' ';
        reg.doubleValue = 0.0;
        reg.intValue = 0;

        registers.push_back(reg);
    }

    void main()
    {

    }
};  
