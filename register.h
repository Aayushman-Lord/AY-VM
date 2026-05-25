#pragma once

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
