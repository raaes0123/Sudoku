#ifndef DIGITS_H
#define DIGITS_H
#include <string>
using namespace std;


class Digits
{
    public:
        // 9x9 position of the digit
        int x;
        int y;
        // Value of the digit
        int num;
        // Flag to determine if the number is from file
        bool flag = 0;
        void setPosition(int, int);
        void setVal(int);
};

#endif