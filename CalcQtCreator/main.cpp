#include <math.h>
#include <iostream>
#define MAX_SIZE 1024

using namespace std;


double eval(char *strExp);
double number(char *strExp, unsigned *index);
double expr(char *strExp, unsigned *index);
double term(char *strExp, unsigned *index);
double factor(char *strExp, unsigned *index);

int main()
{
    int exit = 1;
    while (exit != 0) {
        char strExp[MAX_SIZE];

        cout << "Your expression: ";
        cin.getline(strExp, MAX_SIZE);

        cout << "Result: " << eval(strExp) << endl;
        cout << "Write 0 for exit ";
        cin >> exit;
        cin.get();
    }
    return 0;
}

double eval(char *strExp)
{
    unsigned i = 0;

    return expr(strExp, &i);
}

double number(char *strExp, unsigned *index)
{
    double result = 0.0;
    double div = 10.0;
    int sign = 1;

    if (strExp[*index] == '-')
    {
        sign = -1;
        ++*index;
    }

    while (strExp[*index] >= '0' && strExp[*index] <= '9')
    {
        result = result * 10.0 + (strExp[*index] - '0');

        ++*index;
    }

    if (strExp[*index] == '.')
    {
        ++*index;

        while (strExp[*index] >= '0' && strExp[*index] <= '9')
        {
            result = result + (strExp[*index] - '0') / div;
            div *= 10.0;

            ++*index;
        }
    }

    return sign * result;
}

double expr(char *strExp, unsigned *index)
{
    double result = term(strExp, index);

    while (strExp[*index] == '+' || strExp[*index] == '-')
    {
        switch (strExp[*index])
        {
        case '+':
            ++*index;

            result += term(strExp, index);

            break;
        case '-':
            ++*index;

            result -= term(strExp, index);

            break;
        }
    }

    return result;
}

double term(char *strExp, unsigned *index)
{
    double result = factor(strExp, index);
    double div;

    while (strExp[*index] == '*' || strExp[*index] == '/')
    {
        switch (strExp[*index])
        {
        case '*':
            ++*index;

            result *= factor(strExp, index);

            break;
        case '/':
            ++*index;

            div = factor(strExp, index);

            if (div != 0.0)
            {
                result /= div;
            }
            else
            {
                cout << "Division by zero!\n";
                exit(-1);
            }

            break;
        }
    }

    return result;
}

double factor(char *strExp, unsigned *index)
{
    double result;
    int sign = 1;

    if (strExp[*index] == '-')
    {
        sign = -1;

        ++*index;
    }

    if (strExp[*index] == '(')
    {
        ++*index;

        result = expr(strExp, index);

        if (strExp[*index] != ')')
        {
            cout << "forgot the braces!" << endl;
            exit(-2);
        }

        ++*index;
    }
    else
        result = number(strExp, index);

    if (strExp[*index] == '^')
    {
        ++*index;

        result = pow(result, factor(strExp, index));
    }

    return sign * result;
}
