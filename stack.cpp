#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include "register.h"
#include "stack.h"

using std::string, std::vector, std::cout, std::map;

bool StackManager::push(int &counter, const vector<string> &btcode)
{
    if (counter + 2 >= btcode.size())
    {
        cout << "Error: push missing arguments.";
        return false;
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
        catch (const std::exception &e)
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
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    else
    {
        cout << "Error: Invalid data type";
        return false;
    }

    counter += 3;
    return true;
}

bool StackManager::top(int &counter, const vector<string> &btcode)
{
    if (counter + 1 >= btcode.size())
    {
        cout << "Error: top missing arguments.";
        return false;
    }

    string type = btcode[counter + 1];

    if (type == "int")
    {
        if (intStack.empty())
        {
            cout << "Error: int stack is empty.";
            return false;
        }
        cout << intStack.back() << "\n";
    }
    else if (type == "char")
    {
        if (charStack.empty())
        {
            cout << "Error: char stack is empty.";
            return false;
        }
        cout << charStack.back() << "\n";
    }
    else if (type == "double")
    {
        if (doubleStack.empty())
        {
            cout << "Error: double stack is empty.";
            return false;
        }
        cout << doubleStack.back() << "\n";
    }
    else
    {
        cout << "Error: Invalid data type";
        return false;
    }

    counter += 2;
    return true;
}

bool StackManager::pop(int &counter, const vector<string> &btcode)
{
    if (counter + 1 >= btcode.size())
    {
        cout << "Error: pop missing arguments.";
        return false;
    }
    string type = btcode[counter + 1];
    if (type == "int")
    {
        if (intStack.empty())
        {
            cout << "Error: int stack is empty.";
            return false;
        }
        intStack.pop_back();
    }
    else if (type == "char")
    {
        if (charStack.empty())
        {
            cout << "Error: char stack is empty.";
            return false;
        }
        charStack.pop_back();
    }
    else if (type == "double")
    {
        if (doubleStack.empty())
        {
            cout << "Error: double stack is empty.";
            return false;
        }
        doubleStack.pop_back();
    }
    else
    {
        cout << "Error: Invalid data type";
        return false;
    }
    counter += 2;
    return true;
}

bool StackManager::topToReg(int &counter, const vector<string> &btcode, map<string, Register> &registers)
{
    if (counter + 2 >= btcode.size())
    {
        cout << "Error: topToReg missing arguments.";
        return false;
    }

    string regName = btcode[counter + 1];
    string dType = btcode[counter + 2];

    if (registers.find(regName) == registers.end())
    {
        cout << "Error: Register does not exist.\n";
        return false;
    }

    if (dType == "int")
    {
        if (intStack.empty())
        {
            cout << "Error: int stack is empty.";
            return false;
        }
        registers[regName].intValue = intStack.back();
        intStack.pop_back();
    }
    else if (dType == "char")
    {
        if (charStack.empty())
        {
            cout << "Error: char stack is empty.";
            return false;
        }
        registers[regName].charValue = charStack.back();
        charStack.pop_back();
    }
    else if (dType == "double")
    {
        if (doubleStack.empty())
        {
            cout << "Error: double stack is empty.";
            return false;
        }
        registers[regName].doubleValue = doubleStack.back();
        doubleStack.pop_back();
    }
    else
    {
        cout << "Error: Invalid data type";
        return false;
    }

    counter += 3;
    return true;
}

bool StackManager::dup(int &counter, const vector<string> &btcode)
{
    if (counter + 1 >= btcode.size())
    {
        cout << "Error: dup missing arguments.";
        return false;
    }
    string type = btcode[counter + 1];
    if (type == "int")
    {
        if (intStack.empty())
        {
            cout << "Error: int stack is empty.";
            return false;
        }
        intStack.push_back(intStack.back());
    }
    else if (type == "char")
    {
        if (charStack.empty())
        {
            cout << "Error: char stack is empty.";
            return false;
        }
        charStack.push_back(charStack.back());
    }
    else if (type == "double")
    {
        if (doubleStack.empty())
        {
            cout << "Error: double stack is empty.";
            return false;
        }
        doubleStack.push_back(doubleStack.back());
    }
    else
    {
        cout << "Error: Invalid data type";
        return false;
    }

    counter += 2;
    return true;
}

bool StackManager::handleArithematic(int &counter, const vector<string> &btcode, map<string, Register> &registers, const string &instruction)
{

    if (instruction == "adds")
    {
        if (counter + 1 >= btcode.size())
        {
            cout << "Error: adds missing arguments.";
            return false;
        }
        string type = btcode[counter + 1];
        if (type == "int")
        {
            if (intStack.size() < 2)
            {
                cout << "Error: not enough values in int stack.";
                return false;
            }
            int a = intStack.back();
            intStack.pop_back();
            int b = intStack.back();
            intStack.pop_back();
            intStack.push_back(a + b);
        }
        else if (type == "char")
        {
            cout << "Error: Cannot perform arthmetic operations on char type.";
            return false;
        }
        else if (type == "double")
        {
            if (doubleStack.size() < 2)
            {
                cout << "Error: not enough values in double stack.";
                return false;
            }
            double a = doubleStack.back();
            doubleStack.pop_back();
            double b = doubleStack.back();
            doubleStack.pop_back();
            doubleStack.push_back(a + b);
        }
        else
        {
            cout << "Error: Invalid data type";
            return false;
        }
        counter += 2;
        return true;
    }

    else if (instruction == "subs")
    {
        if (counter + 1 >= btcode.size())
        {
            cout << "Error: subs missing arguments.";
            return false;
        }
        string type = btcode[counter + 1];
        if (type == "int")
        {
            if (intStack.size() < 2)
            {
                cout << "Error: not enough values in int stack.";
                return false;
            }
            int a = intStack.back();
            intStack.pop_back();
            int b = intStack.back();
            intStack.pop_back();
            intStack.push_back(b - a);
        }
        else if (type == "char")
        {
            cout << "Error: Cannot perform arthmetic operations on char type.";
            return false;
        }
        else if (type == "double")
        {
            if (doubleStack.size() < 2)
            {
                cout << "Error: not enough values in double stack.";
                return false;
            }
            double a = doubleStack.back();
            doubleStack.pop_back();
            double b = doubleStack.back();
            doubleStack.pop_back();
            doubleStack.push_back(b - a);
        }
        else
        {
            cout << "Error: Invalid data type";
            return false;
        }
        counter += 2;
        return true;
    }

    else if (instruction == "muls")
    {
        if (counter + 1 >= btcode.size())
        {
            cout << "Error: muls missing arguments.";
            return false;
        }
        string type = btcode[counter + 1];
        if (type == "int")
        {
            if (intStack.size() < 2)
            {
                cout << "Error: not enough values in int stack.";
                return false;
            }
            int a = intStack.back();
            intStack.pop_back();
            int b = intStack.back();
            intStack.pop_back();
            intStack.push_back(a * b);
        }
        else if (type == "char")
        {
            cout << "Error: Cannot perform arthmetic operations on char type.";
            return false;
        }
        else if (type == "double")
        {
            if (doubleStack.size() < 2)
            {
                cout << "Error: not enough values in double stack.";
                return false;
            }
            double a = doubleStack.back();
            doubleStack.pop_back();
            double b = doubleStack.back();
            doubleStack.pop_back();
            doubleStack.push_back(a * b);
        }
        else
        {
            cout << "Error: Invalid data type";
            return false;
        }
        counter += 2;
        return true;
    }

    else if (instruction == "divs")
    {
        if (counter + 1 >= btcode.size())
        {
            cout << "Error: divs missing arguments.";
            return false;
        }
        string type = btcode[counter + 1];
        if (type == "int")
        {
            if (intStack.size() < 2)
            {
                cout << "Error: not enough values in int stack.";
                return false;
            }
            int a = intStack.back();
            intStack.pop_back();
            int b = intStack.back();
            intStack.pop_back();
            if (a == 0)
            {
                cout << "Error: Division by zero.";
                return false;
            }
            intStack.push_back(b / a);
        }
        else if (type == "char")
        {
            cout << "Error: Cannot perform arthmetic operations on char type.";
            return false;
        }
        else if (type == "double")
        {
            if (doubleStack.size() < 2)
            {
                cout << "Error: not enough values in double stack.";
                return false;
            }
            double a = doubleStack.back();
            doubleStack.pop_back();
            double b = doubleStack.back();
            doubleStack.pop_back();
            if (a == 0.0)
            {
                cout << "Error: Division by zero.";
                return false;
            }
            doubleStack.push_back(b / a);
        }
        else
        {
            cout << "Error: Invalid data type";
            return false;
        }
        counter += 2;
        return true;
    }
}
