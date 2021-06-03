#ifndef COMPLEX_H
#define COMPLEX_H
#include <string>

class Complex
{
    private:

        int real,//holds a real integer
            imag;//holds the integer part of the imaginary number

        std::string answer;//holds the entire complex expression of the answer e.g.) "4+7i"

    public:
        Complex(int r = 0, int i = 0);
        virtual ~Complex();

        Complex operator + (Complex const&obj);//operator overloader
        Complex operator - (Complex const&obj);//operator overloader
        Complex operator * (Complex const&obj);//operator overloader
        void print();//prints the complex expression e.g.) 3 + 4i
        bool checkCorrect(std::string ans);//tells the player if their answer was correct or wrong
        void answerStr();//creates an answer string of the complex expression
};

#endif // COMPLEX_H
