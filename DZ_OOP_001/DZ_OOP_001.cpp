#include <iostream>
#include <cmath>
using namespace std;
#define SIZE 5

//Задание 1

class Power
{
public:
    double a;
    double b;

    void calculate()
    {
        cout << "Your result a^b is: " << pow(a, b) << endl;
    }    
};

//Задание 2

class RGBA
{
public:
    uint8_t m_red;
    uint8_t m_green;
    uint8_t m_blue;
    uint8_t m_alpha;

    RGBA(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 255)
        : m_red(red), m_green(green), m_blue(blue), m_alpha(alpha)
    {

    }

    void print()
    {
        cout << "Your result is: ";
        //Несколько способов вывода переменной uint8_t
        cout << +m_red << " " << +m_green << " " << unsigned(m_blue) << " " << static_cast<int>(m_alpha) << endl;
    }
};

//Задание 3

class Stack
{
    int m_Arr[SIZE] = { 0 };
    size_t top = 0;

public:
    bool isempty()
    {
        if (top == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void reset()
    {
        top = 0;
        for (size_t i = 0; i < SIZE; i++) {
            m_Arr[i] = 0;
        }
    }
    void push(int x)
    {
        if (top == SIZE)
        {
            cout << "Stack is full!" << endl;
        }
        else
        {
            m_Arr[top] = x;
            top++;
        }
    }
    void pop()
    {
        if (isempty())
        {
            cout << "Stack is empty" << endl;
        }
        else
        {
            top--;
            m_Arr[top] = 0;
        }
    }
    void print()
    {
        if (isempty())
        {
            cout << "Stack is empty" << endl;
        }
        else
        {
            for (size_t i = 0; i < top; i++)
            {
                cout << m_Arr[i] << " ";
                
            }
            cout << endl;
        }
    }
};


int main()
{
    //Задание 1
    cout << "Exercise 1" << endl << endl;
    Power set { 3, 4 };
        
    set.calculate();
    cout << endl;

    //Задание 2
    cout << "Exercise 2" << endl << endl;
    RGBA rgba(11, 14, 21, 30);

    rgba.print();
    cout << endl;

    //Задание 3
    cout << "Exercise 3" << endl << endl;
    Stack stack;

    stack.reset();
    stack.print();

    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();

    stack.pop();
    stack.print();

    stack.pop();
    stack.pop();
    stack.print();

    return 0;
}

