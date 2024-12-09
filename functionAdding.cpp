#include<iostream>
// C++ program to demonstrate operator overloading
// using dot operator
#include <iostream>
using namespace std;

class ComplexNumber {
private:
    double real;
    double imaginary;

public:
    ComplexNumber(double real, double imaginary)
    {
        this->real = real;
        this->imaginary = imaginary;
    }
    void print() {
        cout << real << " + i" << imaginary << endl;
    }

    ComplexNumber operator+(ComplexNumber c2)
    {
        ComplexNumber c3(0, 0);
        c3.real = this->real + c2.real;
        c3.imaginary = this->imaginary + c2.imaginary;
        return c3;
    }

    ComplexNumber add(ComplexNumber c2)
    {
        ComplexNumber result(0, 0);
        result.real = this->real + c2.real;
        result.imaginary = this->imaginary + c2.imaginary;
        return result;
    }
};



int main()
{
    ComplexNumber c1(3, 5);
    ComplexNumber c2(2, 4);

    //Using Operator overloading
    ComplexNumber c3 = c1 + c2;
    c3.print();

    ComplexNumber c4(9, 5);
    ComplexNumber c5(3.5, 4);
    //Without Operator Overloading
    c3 = c4.add(c5);
    c3.print();
    return 0;
}