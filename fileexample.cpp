#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    ifstream inputFile;
    inputFile.open("numbers.txt");
    ofstream  outFile;
    outFile.open("numbersManipulated.txt");
    while (!inputFile.eof())
    {
        int number;
        inputFile >> number;
        outFile << "Number: " << number << endl;
    }
}