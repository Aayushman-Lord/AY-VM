#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

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
    vector<int> intStack;
    vector<char> charStack;
    vector<double> doubleStack;

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

                if (value == "\\n")
                    value = "\n";
                else if (value == "\\t")
                    value = "\t";
                else if (value == "\\\\")
                    value = "\\";
                else if (value == "\\sp")
                    value = " ";

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
            // Arthmetic operations
            //-----------------------------------

            if (instruction == "add" || instruction == "sub" || instruction == "mul" || instruction == "div")
            {
                if (counter + 5 > btcode.size())
                {
                    cout << "Error: arthamatic operation missing arguments.";
                    break;
                }

                string reg1 = btcode[counter + 1];
                string reg2 = btcode[counter + 2];
                string resultReg = btcode[counter + 3];
                string type = btcode[counter + 4];

                if (!registerExists(reg1) || !registerExists(reg2) || !registerExists(resultReg))
                {
                    cout << "Error: One or more registers do not exist.\n";
                    break;
                }

                if (instruction == "add")
                {
                    if (type == "int")
                    {
                        registers[resultReg].setIntValue(registers[reg1].intValue + registers[reg2].intValue);
                    }
                    else if (type == "double")
                    {
                        registers[resultReg].setDoubleValue(registers[reg1].doubleValue + registers[reg2].doubleValue);
                    }
                    else
                    {
                        cout << "Error: Invalid type.\n";
                        break;
                    }
                }

                else if (instruction == "sub")
                {
                    if (type == "int")
                    {
                        registers[resultReg].setIntValue(registers[reg1].intValue - registers[reg2].intValue);
                    }
                    else if (type == "double")
                    {
                        registers[resultReg].setDoubleValue(registers[reg1].doubleValue - registers[reg2].doubleValue);
                    }
                    else
                    {
                        cout << "Error: Invalid type.\n";
                        break;
                    }
                }

                else if (instruction == "mul")
                {
                    if (type == "int")
                    {
                        registers[resultReg].setIntValue(registers[reg1].intValue * registers[reg2].intValue);
                    }
                    else if (type == "double")
                    {
                        registers[resultReg].setDoubleValue(registers[reg1].doubleValue * registers[reg2].doubleValue);
                    }
                    else
                    {
                        cout << "Error: Invalid type.\n";
                        break;
                    }
                }

                else if (instruction == "div")
                {
                    if (type == "int")
                    {
                        if (registers[reg2].intValue == 0)
                        {
                            cout << "Error: Division by zero.\n";
                            break;
                        }
                        registers[resultReg].setIntValue(registers[reg1].intValue / registers[reg2].intValue);
                    }
                    else if (type == "double")
                    {
                        if (registers[reg2].doubleValue == 0.0)
                        {
                            cout << "Error: Division by zero.\n";
                            break;
                        }
                        registers[resultReg].setDoubleValue(registers[reg1].doubleValue / registers[reg2].doubleValue);
                    }
                    else
                    {
                        cout << "Error: Invalid type.\n";
                        break;
                    }
                }

                counter += 5;
                continue;
            }

            //-----------------------------------
            // MOVE
            //-----------------------------------

            if (instruction == "mov")
            {
                if (counter + 4 > btcode.size())
                {
                    cout << "Error: mov missing arguments.";
                    break;
                }

                string sourceReg = btcode[counter + 1];
                string distReg = btcode[counter + 2];
                string type = btcode[counter + 3];

                if (!registerExists(sourceReg) || !registerExists(distReg))
                {
                    cout << "Error: One or more registers do not exist.\n";
                    break;
                }

                if (type == "int")
                {
                    registers[distReg].intValue = registers[sourceReg].intValue;
                }
                else if (type == "char")
                {
                    registers[distReg].charValue = registers[sourceReg].charValue;
                }
                else if (type == "double")
                {
                    registers[distReg].doubleValue = registers[sourceReg].doubleValue;
                }
                else
                {
                    cout << "Error: Invalid Data Type.";
                    break;
                }

                counter += 4;
                continue;
            }

            //-----------------------------------
            // Handle Stack
            //-----------------------------------

            // push
            if (instruction == "push")
            {
                if (counter + 3 > btcode.size())
                {
                    cout << "Error: push missing arguments.";
                    break;
                }

                string type = btcode[counter + 1];
                string value = btcode[counter + 2];

                if (type == "int")
                {
                    try
                    {
                        int value_int = std::stoi(value);
                        intStack.push_back(value_int);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                                  
                }
                else if (type == "char")
                {
                    charStack.push_back(value[0]);
                }
                else if (type == "double")
                {
                    try
                    {
                        double value_double = std::stod(value);
                        doubleStack.push_back(value_double);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }

                }
                else
                {
                    cout << "Error: Invalid data type";
                    break;
                }
                
                counter += 3;
                continue;
            }

            // top
            if (instruction == "top")
            {
                if (counter + 2 > btcode.size())
                {
                    cout << "Error: top missing arguments.";
                    break;
                }
                
                string type = btcode[counter + 1];
                
                if (type == "int")
                {
                    if (intStack.empty())
                    {
                        cout << "Error: int stack is empty.";
                        break;
                    }
                    cout << intStack.back();
                }
                else if (type == "char")
                {
                    if (charStack.empty())
                    {
                        cout << "Error: char stack is empty.";
                        break;
                    }
                    cout << charStack.back();
                }
                else if (type == "double")
                {
                    if (doubleStack.empty())
                    {
                        cout << "Error: double stack is empty.";
                        break;
                    }
                    cout << doubleStack.back();
                }
                else
                {
                    cout << "Error: Invalid data type";
                    break;
                }
                counter +=2;
                continue;
            }

            //-----------------------------------
            // UNKNOWN
            //-----------------------------------

            cout << "Error: Unknown instruction: "
                 << instruction << "\n";
            break;
        }
    }
};
