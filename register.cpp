#include "register.h"

Register::Register()
{
    charValue = ' ';
    doubleValue = 0.0;
    intValue = 0;
};

void Register::setCharValue(char value)
{
    charValue = value;
};

void Register::setDoubleValue(double value)
{
    doubleValue = value;
}

void Register::setIntValue(int value)
{
    intValue = value;
}
