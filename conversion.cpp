// C++ Program to Demonstrate the working
// of conversion operator
#include <iostream>
using namespace std;

class Fraction {
private:
    int num, den;

public:
    Fraction(int n, int d)
    {
        num = n;
        den = d;
    }

    // Conversion operator: return float value of fraction
    operator float()
    {
        return float(num) / float(den);
    }
};

int main()
{
    Fraction f(2, 5);
    float val = f;
    cout << val << '\n';
    return 0;
}