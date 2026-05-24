#pragma once
#include <iostream>
#include <vector>
#include <map>

using std::string, std::vector, std::cout, std::map;

struct Register
{
    char charValue;
    double doubleValue;
    int intValue;

    Register()
    {
        charValue = ' ';
        doubleValue = 0.0;
        intValue = 0;
    }

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
    map<string, Register> registers;

    void createRegister(string name)
    {
        Register reg;
        registers[name] = reg;
    }

    bool registerExists(string name)
    {
        return registers.find(name) != registers.end();
    }

    void main(vector<string> btcode)
    {
        int counter = 0;

        while (counter < btcode.size())
        {
            string instruction = btcode[counter];

            //-----------------------------------
            // CREATE
            //-----------------------------------

            if (instruction == "create")
            {
                if (counter + 1 >= btcode.size())
                {
                    cout << "Error: create instruction requires a register name.\n";
                    break;
                }

                string regName = btcode[counter + 1];

                createRegister(regName);

                counter += 2;
                continue;
            }

            //-----------------------------------
            // SET
            //-----------------------------------

            if (instruction == "set")
            {
                if (counter + 3 >= btcode.size())
                {
                    cout << "Error: set instruction requires a register name, value type, and value.\n";
                    break;
                }

                string regName = btcode[counter + 1];
                string valueType = btcode[counter + 2];
                string value = btcode[counter + 3];

                if (value == "\\n")value = "\n";
                else if (value == "\\t")value = "\t";
                else if (value == "\\\\")value = "\\";

                if (!registerExists(regName))
                {
                    cout << "Error: Register " << regName << " does not exist.\n";
                    break;
                }

                if (valueType == "char")
                {
                    registers[regName].setCharValue(value[0]);
                }
                else if (valueType == "double")
                {
                    registers[regName].setDoubleValue(stod(value));
                }
                else if (valueType == "int")
                {
                    registers[regName].setIntValue(stoi(value));
                }
                else
                {
                    cout << "Error: Invalid value type.\n";
                    break;
                }

                counter += 4;
                continue;
            }

            //-----------------------------------
            // PRINT
            //-----------------------------------

            if (instruction == "print")
            {
                if (counter + 2 >= btcode.size())
                {
                    cout << "Error: print missing arguments.\n";
                    break;
                }

                string regName = btcode[counter + 1];
                string dType = btcode[counter + 2];

                if (!registerExists(regName))
                {
                    cout << "Error: Register does not exist.\n";
                    break;
                }

                if (dType == "int")
                {
                    cout << registers[regName].intValue;
                }
                else if (dType == "char")
                {
                    cout << registers[regName].charValue;
                }
                else if (dType == "double")
                {
                    cout << registers[regName].doubleValue;
                }
                else
                {
                    cout << "Error: Invalid Dtype.\n";
                    break;
                }

                counter += 3;
                continue;
            }

            //-----------------------------------
            // UNKNOWN
            //-----------------------------------

            cout << "Error: Unknown instruction -> "
                 << instruction << "\n";
            break;
        }
    }
};
