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

    void main(const vector<string>& btcode)
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
                    try
                    {
                        double value_double = stod(value);
                        registers[regName].setDoubleValue(value_double);
                    }
                    catch(const std::exception& e)
                    {
                        std::cout << "Error: expected a double " << '\n';
                    }
                }
                else if (valueType == "int")
                {
                    try
                    {
                        int value_int = stoi(value);
                        registers[regName].setIntValue(value_int);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << "Error: expected an intiger"<< '\n';
                    }
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
            // Arithmetec operations
            //-----------------------------------

            if (instruction == "add" || instruction == "sub" || instruction == "mul" || instruction == "div")
            {
                if (counter + 4 >= btcode.size())
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
                if (counter + 3 >= btcode.size())
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
                if (counter + 2 >= btcode.size())
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
                if (counter + 1 >= btcode.size())
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

            // pop 
            if (instruction == "pop")
            {
                if(counter + 1 >= btcode.size())
                {
                    cout << "Error: pop missing arguments.";
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
                    intStack.pop_back();
                }
                else if (type == "char")
                {
                    if (charStack.empty())
                    {
                        cout << "Error: char stack is empty.";
                        break;
                    }
                    charStack.pop_back();
                }
                else if (type == "double")
                {
                    if (doubleStack.empty())
                    {
                        cout << "Error: double stack is empty.";
                        break;
                    }
                    doubleStack.pop_back();
                }
                else
                {
                    cout << "Error: Invalid data type";
                    break;
                }
                counter += 2;
                continue;
            }

            // Arithmetic operations on stack values
            {
            if (instruction == "adds")
            {
                if (counter + 1 >= btcode.size())
                {
                    cout << "Error: adds missing arguments.";
                    break;
                }
                string type = btcode[counter + 1];
                if (type == "int")
                {
                    if (intStack.size() < 2)
                    {
                        cout << "Error: not enough values in int stack.";
                        break;
                    }
                    int a = intStack.back(); intStack.pop_back();
                    int b = intStack.back(); intStack.pop_back();
                    intStack.push_back(a + b);
                }
                else if (type == "char")
                {
                    cout << "Error: Cannot perform arthmetic operations on char type.";
                    break;
                }
                else if (type == "double")
                {
                    if (doubleStack.size() < 2)
                    {
                        cout << "Error: not enough values in double stack.";
                        break;
                    }
                    double a = doubleStack.back(); doubleStack.pop_back();
                    double b = doubleStack.back(); doubleStack.pop_back();
                    doubleStack.push_back(a + b);
                }
                else
                {
                    cout << "Error: Invalid data type";
                    break;
                }
                counter += 2;
                continue;
            }
 
            if (instruction == "subs")
            {
                if (counter + 1 >= btcode.size())
                {
                    cout << "Error: subs missing arguments.";
                    break;
                }
                string type = btcode[counter + 1];
                if (type == "int")
                {
                    if (intStack.size() < 2)
                    {
                        cout << "Error: not enough values in int stack.";
                        break;
                    }
                    int a = intStack.back(); intStack.pop_back();
                    int b = intStack.back(); intStack.pop_back();
                    intStack.push_back(b - a);
                }
                else if (type == "char")
                {
                    cout << "Error: Cannot perform arthmetic operations on char type.";
                    break;
                }
                else if (type == "double")
                {
                    if (doubleStack.size() < 2)
                    {
                        cout << "Error: not enough values in double stack.";
                        break;
                    }
                    double a = doubleStack.back(); doubleStack.pop_back();
                    double b = doubleStack.back(); doubleStack.pop_back();
                    doubleStack.push_back(b - a);
                }
                else
                {
                    cout << "Error: Invalid data type";
                    break;
                }
                counter += 2;
                continue;
            }

            if (instruction == "muls")
            {
                if (counter + 1 >= btcode.size())
                {
                    cout << "Error: muls missing arguments.";
                    break;
                }
                string type = btcode[counter + 1];
                if (type == "int")
                {
                    if (intStack.size() < 2)
                    {
                        cout << "Error: not enough values in int stack.";
                        break;
                    }
                    int a = intStack.back(); intStack.pop_back();
                    int b = intStack.back(); intStack.pop_back();
                    intStack.push_back(a * b);
                }
                else if (type == "char")
                {
                    cout << "Error: Cannot perform arthmetic operations on char type.";
                    break;
                }
                else if (type == "double")
                {
                    if (doubleStack.size() < 2)
                    {
                        cout << "Error: not enough values in double stack.";
                        break;
                    }
                    double a = doubleStack.back(); doubleStack.pop_back();
                    double b = doubleStack.back(); doubleStack.pop_back();
                    doubleStack.push_back(a * b);
                }
                else
                {
                    cout << "Error: Invalid data type";
                    break;
                }
                counter += 2;
                continue;
            }

            if (instruction == "divs")
            {
                if (counter + 1 >= btcode.size())
                {
                    cout << "Error: divs missing arguments.";
                    break;
                }
                string type = btcode[counter + 1];
                if (type == "int")
                {
                    if (intStack.size() < 2)
                    {
                        cout << "Error: not enough values in int stack.";
                        break;
                    }
                    int a = intStack.back(); intStack.pop_back();
                    int b = intStack.back(); intStack.pop_back();
                    if (a == 0)
                    {
                        cout << "Error: Division by zero.";
                        break;
                    }
                    intStack.push_back(b / a);
                }
                else if (type == "char")
                {
                    cout << "Error: Cannot perform arthmetic operations on char type.";
                    break;
                }
                else if (type == "double")
                {
                    if (doubleStack.size() < 2)
                    {
                        cout << "Error: not enough values in double stack.";
                        break;
                    }
                    double a = doubleStack.back(); doubleStack.pop_back();
                    double b = doubleStack.back(); doubleStack.pop_back();
                    if (a == 0.0)
                    {
                        cout << "Error: Division by zero.";
                        break;
                    }
                    doubleStack.push_back(b / a);
                }
                else
                {
                    cout << "Error: Invalid data type";
                    break;
                }
                counter += 2;
                continue;
            }
            }

            // Send top to register
            if (instruction == "topToReg")
            {
                if (counter + 2 >= btcode.size())
                {
                    cout << "Error: topToReg missing arguments.";
                    break;
                }
                string type = btcode[counter + 1];
                string regName = btcode[counter + 2];
                if (!registerExists(regName))
                {
                    cout << "Error: Register does not exist.\n";
                    break;
                }
                if (type == "int")
                {
                    if (intStack.empty())
                    {
                        cout << "Error: int stack is empty.";
                        break;
                    }
                    registers[regName].setIntValue(intStack.back());
                    intStack.pop_back();
                }
                else if (type == "char")
                {
                    if (charStack.empty())
                    {
                        cout << "Error: char stack is empty.";
                        break;
                    }
                    registers[regName].setCharValue(charStack.back());
                    charStack.pop_back();
                }
                else if (type == "double")
                {
                    if (doubleStack.empty())
                    {
                        cout << "Error: double stack is empty.";
                        break;
                    }
                    registers[regName].setDoubleValue(doubleStack.back());
                    doubleStack.pop_back();
                }
                else
                {
                    cout << "Error: Invalid data type";
                    break;
                }
                
                counter +=3;
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
