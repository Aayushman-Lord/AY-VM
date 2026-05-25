#pragma once

struct Register
{
    char charValue;
    double doubleValue;
    int intValue;

    Register();
    
    void setCharValue(char value);

    void setDoubleValue(double value);

    void setIntValue(int value);
};
