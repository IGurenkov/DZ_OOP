#include <iostream>
#include <string>

using namespace std;

/*1. Написать шаблонную функцию div, которая должна вычислять результат деления двух параметров и запускать исключение DivisionByZero,
если второй параметр равен 0. В функции main выводить результат вызова функции div в консоль, а также ловить исключения.*/
template <typename T1, typename T2>
void div1(T1 a, T2 b)
{
    if (b == 0.0)
    {
        throw " ERROR! The denominator value cannot be 0!";
    }

    cout << "   Result is: " << a * 1.0 / b << endl << endl;
}

/*2. Написать класс Ex, хранящий вещественное число x и имеющий конструктор по вещественному числу,
инициализирующий x значением параметра. Написать класс Bar, хранящий вещественное число y
(конструктор по умолчанию инициализирует его нулем) и имеющий метод set с единственным вещественным
параметром a. Если y + a > 100, возбуждается исключение типа Ex с данными a*y, иначе в y заносится значение a.
В функции main завести переменную класса Bar и в цикле в блоке try вводить с клавиатуры целое n. Использовать его
в качестве параметра метода set до тех пор, пока не будет введено 0. В обработчике исключения выводить сообщение об ошибке,
содержащее данные объекта исключения.*/

class Ex
{
public:

    float X;

public:

    Ex(float x) : X(x) {};

};

class Bar
{
private:

    float Y;

public:
    Bar() { Y = 0; }

    void set(float a)
    {
       if (a > 0 && Y + a > 100)
       {               
            cout << "   Becouse total (y + a) > 100, take (a * y): ";
            throw Ex(a * Y);
            cout << endl << endl;                
       }
       else if (a > 0 && Y + a <= 100)
       {
            Y = a;
            cout << "   Becouse total (y + a) < 100, take enter number: " << a << endl;
       }
       else if (a < 0 && Y + a > 100)
       {
           cout << "   Becouse total (y + a) > 100, take (a * y): ";
           throw Ex(a * Y);
           cout << endl << endl;
       }
       else if (a < 0 && Y + a <= 100)
       {
           Y = a;
           cout << "   Becouse total (y + a) < 100, take enter number: " << a << endl;
       }        
    }
};

/*3. Написать класс «робот», моделирующий перемещения робота по сетке 10x10, у которого есть метод, означающий задание переместиться на соседнюю позицию.
Эти методы должны запускать классы - исключения OffTheField, если робот должен уйти с сетки, и IllegalCommand, если подана неверная команда(направление
    не находится в нужном диапазоне).Объект исключения должен содержать всю необходимую информацию — текущую позицию и направление движения.Написать
    функцию main, пользующуюся этим классом и перехватывающую все исключения от его методов, а также выводящую подробную информацию о всех возникающих
    ошибках.*/

class OffTheField : public exception
{
public:
    OffTheField()
    {
        cout << "   ERROR! Out of the Field! || ";
    }
};

class IllegalCommand : public exception
{
public:
    IllegalCommand()
    {
        cout << "   ERROR! Illegal command! || ";
    }
};

class Robot
{
private:

    const int mMIN_X = 1;
    const int mMAX_X = 10;
    const int mMIN_Y = 1;
    const int mMAX_Y = 10;
    int mX;
    int mY;

public:

    Robot()
    {
        mX = 1;
        mY = 1;
    }
    Robot(int x, int y) : mX(x), mY(y)
    {

    }

    int GetX() const
    {
        return mX;
    }
    int GetY() const
    {
        return mY;
    }

    bool Move(int Right, int Up)
    {
        int mx = mX + Right;
        int my = mY + Up;
        if (mMIN_X <= mx && mMAX_X >= mx && mMIN_Y <= my && mMAX_Y >= my)
        {
            mX = mx;
            mY = my;
            return true;
        }
        throw OffTheField();
    }

    bool MoveUp()
    {
        return Move(0, -1);
    }
    bool MoveDown()
    {
        return Move(0, 1);
    }
    bool MoveLeft()
    {
        return Move(-1, 0);
    }
    bool MoveRight()
    {
        return Move(1, 0);
    }
};

int main()
{
    cout << "###############################################################################################" << endl;
    cout << endl;
    cout << "   Exercise 1";
    cout << endl << endl;
    try
    {
        div1(9, 4);
    }

    catch (const char* exception)
    {
        cerr << "   Error: " << exception << endl;
    }
    
    cout << "###############################################################################################" << endl;
    cout << endl;
    cout << "   Exercise 2";
    cout << endl << endl;

    Bar A;
    float n;    
    
    do
    {
        cout << "   Enter a number: ";
        cin >> n;
        try
        {                    
            A.set(n);
            
        }
        catch (const Ex& ex)
        {
            cerr << ex.X << endl;
            
        }
    } while (n != 0);

    cout << endl << endl;
    cout << "###############################################################################################" << endl;
    cout << endl;
    cout << "   Exercise 3" << endl << endl;

    Robot R;
    string tomove;
    cout << "   For move to north enter W and press Enter" << endl;
    cout << "   For move to south enter S and press Enter" << endl;
    cout << "   For move to west enter A and press Enter" << endl;
    cout << "   For move to east enter D and press Enter" << endl;

    while (cin >> tomove && tomove != "N" && tomove != "n")
    {
        try
        {
            if (tomove == "W" || tomove == "w")
            {
                R.MoveUp();
            }
            else if (tomove == "S" || tomove == "s")
            {
                R.MoveDown();
            }
            else if (tomove == "A" || tomove == "a")
            {
                R.MoveLeft();
            }
            else if (tomove == "D" || tomove == "d")
            {
                R.MoveRight();
            }
            else
            {
                throw IllegalCommand();
            }
            cout << "   Robot position is: " << "X = " << R.GetX() << " " << "Y = " << R.GetY() << endl;
        }
        catch (IllegalCommand& ill)
        {
            cout << ill.what() << " ||" << " Robot position is: " << "X = " << R.GetX() << " " << "Y = " << R.GetY() << endl;
        }
        catch (OffTheField& off)
        {
            cout << off.what() << " ||" << " Robots position is: " << "X = " << R.GetX() << " " << "Y = " << R.GetY() << endl;
        }
    }
    cout << "###############################################################################################" << endl << endl;
    return 0;
}