#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include "stack.h"
#include "register.h"

using std::string, std::vector, std::cout, std::map;

struct VM
{
    map<string, Register> registers;
    map<string, int> Labels;
    vector<int> SavedCounters;
    StackManager stack;

    void createRegister(string name)
    {
        Register reg;
        registers[name] = reg;
    }

    bool registerExists(string name)
    {
        return registers.find(name) != registers.end();
    }

    void run(const vector<string> &btcode)
    {
        // Find labels and store their positions
        for (int i = 0; i < btcode.size();)
        {
            if (btcode[i] == ":")
            {
                Labels[btcode[i + 1]] = i + 2;
                i += 2;
            }
            else
            {
                i++;
            }
        }

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

            else if (instruction == "set")
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
                    catch (const std::exception &e)
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
                    catch (const std::exception &e)
                    {
                        std::cerr << "Error: expected an intiger" << '\n';
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

            else if (instruction == "print")
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

            else if (instruction == "add" || instruction == "sub" || instruction == "mul" || instruction == "div")
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

            else if (instruction == "mov")
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
            else if (instruction == "push")
            {
                if (!stack.push(counter, btcode))
                {
                    break;
                }
                continue;
            }

            // top
            else if (instruction == "top")
            {
                if (!stack.top(counter, btcode))
                {
                    break;
                }
                continue;
            }

            // pop
            else if (instruction == "pop")
            {
                if (!stack.pop(counter, btcode))
                {
                    break;
                }
                continue;
            }

            // Arithmetic operations on stack values
            else if (instruction == "adds" || instruction == "subs" || instruction == "muls" || instruction == "divs")
            {
                if (!stack.handleArithematic(counter, btcode, registers, instruction))
                {
                    break;
                }
                continue;
            }

            // Send top to register
            else if (instruction == "topToReg")
            {
                if (!stack.topToReg(counter, btcode, registers))
                {
                    break;
                }
                continue;
            }

            // Duplicate top value
            else if (instruction == "dup")
            {
                if (!stack.dup(counter, btcode))
                {
                    break;
                }
                continue;
            }

            // Swap top two values
            else if (instruction == "swap")
            {
                if (!stack.swap(counter, btcode))
                {
                    break;
                }
                continue;
            }

            // Jump_ifs
            else if (instruction == "jump_ifs")
            {
                if (!stack.handleJumpIf(counter, btcode))
                {
                    break;
                }
                continue;
            }

            else if (instruction == "jump_ifs_not")
            {
                if (stack.handleJumpIfNot(counter, btcode))
                {
                    break;
                }
            }

            // ----stack end---//

            //-----------------------------------
            // Comparison operations
            //-----------------------------------

            else if (instruction == "equal_to")
            {
                if (counter + 4 >= btcode.size())
                {
                    cout << "Error: Equal missing arguments.";
                    break;
                }

                string type = btcode[counter + 1];
                string reg1 = btcode[counter + 2];
                string reg2 = btcode[counter + 3];
                string resultReg = btcode[counter + 4];

                if (!registerExists(reg1) || !registerExists(reg2) || !registerExists(resultReg))
                {
                    cout << "Error: One or more registers do not exist.\n";
                    break;
                }

                if (type == "int")
                {
                    if (registers[reg1].intValue == registers[reg2].intValue)
                    {
                        registers[resultReg].intValue = 1;
                    }
                    else
                    {
                        registers[resultReg].intValue = 0;
                    }
                }
                else if (type == "char")
                {
                    if (registers[reg1].charValue == registers[reg2].charValue)
                    {
                        registers[resultReg].intValue = 1;
                    }
                    else
                    {
                        registers[resultReg].intValue = 0;
                    }
                }
                else if (type == "double")
                {
                    if (registers[reg1].doubleValue == registers[reg2].doubleValue)
                    {
                        registers[resultReg].intValue = 1;
                    }
                    else
                    {
                        registers[resultReg].intValue = 0;
                    }
                }
                else
                {
                    cout << "Error: Invalid type.\n";
                    break;
                }

                counter += 5;
                continue;
            }

            else if (instruction == "greater_than")
            {
                if (counter + 4 >= btcode.size())
                {
                    cout << "Error: greater_than missing arguments.";
                    break;
                }

                string type = btcode[counter + 1];
                string reg1 = btcode[counter + 2];
                string reg2 = btcode[counter + 3];
                string resultReg = btcode[counter + 4];

                if (!registerExists(reg1) || !registerExists(reg2) || !registerExists(resultReg))
                {
                    cout << "Error: One or more registers do not exist.\n";
                    break;
                }

                if (type == "int")
                {
                    if (registers[reg1].intValue > registers[reg2].intValue)
                    {
                        registers[resultReg].intValue = 1;
                    }
                    else
                    {
                        registers[resultReg].intValue = 0;
                    }
                }
                else if (type == "char")
                {
                    if (registers[reg1].charValue > registers[reg2].charValue)
                    {
                        registers[resultReg].intValue = 1;
                    }
                    else
                    {
                        registers[resultReg].intValue = 0;
                    }
                }
                else if (type == "double")
                {
                    if (registers[reg1].doubleValue > registers[reg2].doubleValue)
                    {
                        registers[resultReg].intValue = 1;
                    }
                    else
                    {
                        registers[resultReg].intValue = 0;
                    }
                }
                else
                {
                    cout << "Error: Invalid type.\n";
                    break;
                }

                counter += 5;
                continue;
            }

            else if (instruction == "less_than")
            {
                if (counter + 4 >= btcode.size())
                {
                    cout << "Error: less_than missing arguments.";
                    break;
                }

                string type = btcode[counter + 1];
                string reg1 = btcode[counter + 2];
                string reg2 = btcode[counter + 3];
                string resultReg = btcode[counter + 4];

                if (!registerExists(reg1) || !registerExists(reg2) || !registerExists(resultReg))
                {
                    cout << "Error: One or more registers do not exist.\n";
                    break;
                }

                if (type == "int")
                {
                    if (registers[reg1].intValue < registers[reg2].intValue)
                    {
                        registers[resultReg].intValue = 1;
                    }
                    else
                    {
                        registers[resultReg].intValue = 0;
                    }
                }
                else if (type == "char")
                {
                    if (registers[reg1].charValue < registers[reg2].charValue)
                    {
                        registers[resultReg].intValue = 1;
                    }
                    else
                    {
                        registers[resultReg].intValue = 0;
                    }
                }
                else if (type == "double")
                {
                    if (registers[reg1].doubleValue < registers[reg2].doubleValue)
                    {
                        registers[resultReg].intValue = 1;
                    }
                    else
                    {
                        registers[resultReg].intValue = 0;
                    }
                }
                else
                {
                    cout << "Error: Invalid type.\n";
                    break;
                }

                counter += 5;
                continue;
            }

            //-----------------------------------
            // Jump
            //-----------------------------------
            else if (instruction == "jump")
            {
                if (counter + 1 >= btcode.size())
                {
                    cout << "Error: jump missing arguments.";
                    break;
                }

                if (Labels.find(btcode[counter + 1]) != Labels.end())
                {
                    counter = Labels[btcode[counter + 1]];
                    continue;
                }

                try
                {
                    int jump_to = std::stoi(btcode[counter + 1]);

                    if (!(jump_to < 0 || jump_to >= btcode.size()))
                    {
                        counter = jump_to;
                        continue;
                    }
                    else
                    {
                        cout << "Error: position doesnt exits;";
                        break;
                    }
                }
                catch (const std::exception &e)
                {
                    cout << "Error: expected an int.";
                    break;
                }
            }

            //-----------------------------------
            // Jump_if and jump_if_not (with label support)
            //-----------------------------------
            else if (instruction == "jump_if")
            {
                if (counter + 2 >= btcode.size())
                {
                    cout << "Error: jump_if missing arguments.";
                    break;
                }
                string regName = btcode[counter + 1];
                string jump_to = btcode[counter + 2];

                if (Labels.find(jump_to) != Labels.end())
                {
                    if (registers[regName].intValue == 1)
                    {
                        counter = Labels[jump_to];
                        continue;
                    }
                    else
                    {
                        counter += 3;
                        continue;
                    }
                }

                if (!registerExists(regName))
                {
                    cout << "Error: Register does not exist.\n";
                    break;
                }

                if (registers[regName].intValue == 1)
                {
                    try
                    {
                        int target = std::stoi(jump_to);
                        if (target < 0 || target >= btcode.size())
                        {
                            cout << "Error: invalid position provided.";
                            break;
                        }

                        counter = target;
                        continue;
                    }
                    catch (const std::exception &e)
                    {
                        std::cout << "Error: Expected an intiger." << '\n';
                        break;
                    }
                }

                counter += 3;
                continue;
            }

            else if (instruction == "jump_if_not")
            {
                if (counter + 2 >= btcode.size())
                {
                    cout << "Error: jump_if_not missing arguments.";
                    break;
                }
                string regName = btcode[counter + 1];
                string jump_to = btcode[counter + 2];

                if (Labels.find(jump_to) != Labels.end())
                {
                    if (registers[regName].intValue == 0)
                    {
                        counter = Labels[jump_to];
                        continue;
                    }
                    else
                    {
                        counter += 3;
                        continue;
                    }
                }

                if (!registerExists(regName))
                {
                    cout << "Error: Register does not exist.\n";
                    break;
                }

                if (registers[regName].intValue == 0)
                {
                    try
                    {
                        int target = std::stoi(jump_to);
                        if (target < 0 || target >= btcode.size())
                        {
                            cout << "Error: invalid position provided.";
                            break;
                        }

                        counter = target;
                        continue;
                    }
                    catch (const std::exception &e)
                    {
                        std::cout << "Error: Expected an intiger." << '\n';
                        break;
                    }
                }

                counter += 3;
                continue;
            }

            //-----------------------------------
            // Lables
            //-----------------------------------
            else if (instruction == ":")
            {
                counter += 2;
                continue;
            }

            //-----------------------------------
            // Input
            //-----------------------------------
            else if (instruction == "input")
            {
                if (counter + 2 >= btcode.size())
                {
                    cout << "Error: input missing arguments.";
                    break;
                }

                string regName = btcode[counter + 1];
                string type = btcode[counter + 2];

                if (!registerExists(regName))
                {
                    cout << "Error: Register does not exist.\n";
                    break;
                }

                if (type == "int")
                {
                    int input_int;

                    std::cin >> input_int;

                    if (std::cin.fail())
                    {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');

                        cout << "Error: expected an integer.\n";
                        break;
                    }

                    registers[regName].setIntValue(input_int);
                }

                else if (type == "double")
                {
                    double input_double;

                    std::cin >> input_double;

                    if (std::cin.fail())
                    {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');

                        cout << "Error: expected a double.\n";
                        break;
                    }

                    registers[regName].setDoubleValue(input_double);
                }

                else if (type == "char")
                {
                    char input_char;

                    std::cin >> input_char;

                    if (std::cin.fail())
                    {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');

                        cout << "Error: expected a char.\n";
                        break;
                    }

                    registers[regName].setCharValue(input_char);
                }

                else
                {
                    cout << "Error: Invalid type.\n";
                    break;
                }

                counter += 3;
                continue;
            }

            //-----------------------------------
            // Exit
            //-----------------------------------

            else if (instruction == "EXIT")
                break;

            //-----------------------------------
            // ret and call
            //-----------------------------------
            else if (instruction == "call")
            {
                if (counter + 1 >= btcode.size())
                {
                    cout << "Error: call missing arguments.";
                    break;
                }
                string label = btcode[counter + 1];

                if (Labels.find(label) == Labels.end())
                {
                    cout << "Error: Label does not exist.\n";
                    break;
                }
                SavedCounters.push_back(counter + 2);
                counter = Labels[label];
                continue;
            }
            
            else if (instruction == "ret")
            {
                if (SavedCounters.empty())
                {
                    counter++; 
                    continue;
                }
                counter = SavedCounters.back();
                SavedCounters.pop_back();
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
