#include "Complex.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

using namespace std;

/**< Complex constructor */
Complex::Complex(int r, int i)
{
    this->real = r;
    this->imag = i;
    this->answer = "";
}

Complex::~Complex()
{

}

/**< operator overload method - adds real & imaginary values */
Complex Complex::operator+(Complex const&obj)
{
    Complex res;
    res.real = real + obj.real;
    res.imag = imag + obj.imag;
    return res;
}

/**< operator overload method - subtracts real & imaginary values */
Complex Complex::operator-(Complex const&obj)
{
    Complex res;
    res.real = real - obj.real;
    res.imag = imag - obj.imag;
    return res;
}

/**< operator overload method - multiplies real & imaginary values */
Complex Complex::operator*(Complex const&obj)
{
    Complex res;
    double real1, real2, imag1, imag2;
    real1 = real * obj.real;
    real2 = imag * obj.imag * -1;
    imag1 = real * obj.imag;
    imag2 = imag * obj.real;
    res.real = real1 + real2;
    res.imag = imag1 + imag2;
    return res;
}

/**< prints the complex expression e.g.) 3 + 4i*/
void Complex::print()
{
    if (imag > 0)
    {
        if (real != 0)
        {
            cout << real << "+" << imag << "i";
        }
        else
        {
            cout << imag << "i";
        }
    }
    else if (imag == 0)
    {
        cout << real;
    }
    else
    {
        if (real != 0)
        {
            cout << real << imag << "i";
        }
        else
        {
            cout << imag << "i";
        }
    }
}

/**< creates an answer string of the complex expression */
void Complex::answerStr()
{
    if (imag > 0)
    {
        if (real != 0)
        {
            answer = std::to_string(real) + "+" + std::to_string(imag) + "i";
        }
        else
        {
            answer = std::to_string(imag) + "i";
        }
    }
    else if (imag == 0)
    {
        answer = std::to_string(real);
    }
    else
    {
        if (real != 0)
        {
            answer = std::to_string(real) + std::to_string(imag) + "i";
        }
        else
        {
            answer = std::to_string(imag) + "i";
        }
    }
}

/**<  Uses answerStr to compare with the parameters in order to return the equality
of both the strings thus telling the player if their answer was correct or wrong */
bool Complex::checkCorrect(std::string ans)
{
    answerStr();
    int result = answer.compare(ans);
    if (result == 0)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << "                                 CORRECT!" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        return true;
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "                                  WRONG!" << endl;
        cout << "                             Correct Answer = " << answer << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        return false;
    }
}
