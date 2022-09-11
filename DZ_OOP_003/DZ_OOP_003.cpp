#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>
#include <numeric>
#include "Fraction.h"




using namespace std;

/*1. Создать абстрактный класс Figure (фигура). Его наследниками являются классы Parallelogram (параллелограмм) и 
Circle (круг). Класс Parallelogram — базовый для классов Rectangle (прямоугольник), Square (квадрат), Rhombus (ромб). 
Для всех классов создать конструкторы. Для класса Figure добавить чисто виртуальную функцию area() (площадь). 
Во всех остальных классах переопределить эту функцию, исходя из геометрических формул нахождения площади.*/

//Задание 1
class Figure
{
public:
   virtual int area() = 0;
   Figure()
   {

   }
};

class Parallelogram : virtual public Figure
{
public:
    Parallelogram()
    {

    }
    int area()
    {

    }
};

class Circle : virtual public Figure
{
public:
    Circle()
    {

    }
    int area()
    {

    }
};

class Rectangle : virtual public Parallelogram
{
public:
    Rectangle() 
    {

    }
    int area()
    {

    }
};

class Square : virtual public Parallelogram
{
public:
    Square()
    {

    }
    int area()
    {

    }
};

class Rhombus : virtual public Parallelogram
{
public:
    Rhombus()
    {

    }
    int area()
    {

    }
};

/*2. Создать класс Car (автомобиль) с полями company (компания) и model (модель). Классы-наследники: PassengerCar 
(легковой автомобиль) и Bus (автобус). От этих классов наследует класс Minivan (минивэн). Создать конструкторы для 
каждого из классов, чтобы они выводили данные о классах. Создать объекты для каждого из классов и посмотреть, в какой 
последовательности выполняются конструкторы. Обратить внимание на проблему «алмаз смерти».
Примечание: если использовать виртуальный базовый класс, то объект самого "верхнего" базового класса создает самый "дочерний" класс.*/

//Задание 2

class Car
{
protected:
    string m_company;
    string m_model;
public:
    Car(const string& company, const string& model) : m_company(company), m_model(model)
    {

    }
    void print()
    {
        cout << "   Company: " << m_company << endl << "   Model: " << m_model << endl;
    }
};

class PassengerCar : virtual public Car
{
public:
    PassengerCar(const string& company, const string& model) : Car(company, model)
    {

    }    
};

class Bus : virtual public Car
{
public:
    Bus(const string& company, const string& model) : Car(company, model)
    {

    }
};

class Minivan : public PassengerCar, public Bus
{
public:
    Minivan(const string& company, const string& model) : Car(company, model), PassengerCar(company, model), Bus(company, model)
    {

    }
};

/*3. Создать класс: Fraction (дробь). Дробь имеет числитель и знаменатель (например, 3/7 или 9/2). 
Предусмотреть, чтобы знаменатель не был равен 0. 
Перегрузить:
математические бинарные операторы (+, -, *, /) для выполнения действий с дробями
унарный оператор (-)
логические операторы сравнения двух дробей (==, !=, <, >, <=, >=).

Примечание: Поскольку операторы < и >=, > и <= — это логические противоположности, попробуйте перегрузить один через другой.

Продемонстрировать использование перегруженных операторов.*/



//Задание 4
/*4. Создать класс Card, описывающий карту в игре БлэкДжек. У этого класса должно быть три поля: масть, значение карты 
и положение карты (вверх лицом или рубашкой). Сделать поля масть и значение карты типом перечисления (enum). 
Положение карты - тип bool. Также в этом классе должно быть два метода:
метод Flip(), который переворачивает карту, т.е. если она была рубашкой вверх, то он ее поворачивает лицом вверх, и наоборот.
метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.*/



enum class m_suit { Diamonds, Hearts, Clubs, Spades };
enum class m_cardvalue 
{
    TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8,
    NINE = 9, TEN = 10, JACK = 10, QUEEN = 10, KING = 10, ACE = 1
};

class Card
{
private:
    m_suit suit;    
    m_cardvalue cardvalue;
    bool m_isFaceUp;

public:
    Card(bool isFaceUp, enum suit, enum cardvalue) : suit{}, cardvalue{}, m_isFaceUp(isFaceUp)
    {

    }
    void Flip()
    {

    }
    string GetValue ()
    {    
        
    }
    string GetSuit()
    {

    }
    

};



int main()
{
    cout << endl;
    cout << "   Exercise 2";
    cout << endl << endl;

    cout << "   Car" << endl;
    Car car1("Toyota", "Camry");
    car1.print();

    cout << endl;
    cout << "   Passenger Car" << endl;
    PassengerCar pc("LADA", "Kalina");
    pc.print();

    cout << endl;
    cout << "   Bus" << endl;   
    Bus bus("IKARUS", "260");
    bus.print();

    cout << endl;
    cout << "   Minivan" << endl;
    Minivan minivan("Toyota", "Estima");
    minivan.print();

    cout << endl;
    cout << "   Exercise 3";
    cout << endl << endl;
        
    Fraction a(1, 2), b(1, 3), c(5), d;

    cout << "------------- 1 ------------- " << endl <<
        "a: " << a << endl <<
        "b: " << b << endl <<
        "c: " << c << endl <<
        "d: " << d << endl;

    cout << "b <m_numerator> <m_denominator>: ";
    cin >> b;

    d = 2 * a / b;
    c = d * 1;

    cout << "------------- 2 ------------- " << endl <<
        "a: " << a << endl <<
        "b: " << b << endl <<
        "c: " << c << endl <<
        "d: " << d << endl;
    if (d == c)
    {
        cout << "d == c" << endl;
    }
    else
    {
        cout << "NOT d == c" << endl;
    }
    a = a - d;
    c /= -d;

    cout << "------------- 3 ------------- " << endl <<
        "a: " << a << endl <<
        "b: " << b << endl <<
        "c: " << c << endl <<
        "d: " << d << endl;
    b = --c;
    cout << "------------- 4 ------------- " << endl <<
        "a: " << a << endl <<
        "b: " << b << endl <<
        "c: " << c << endl <<
        "d: " << d << endl;
    b = d--;

    cout << "------------- 5 ------------- " << endl <<
        "a: " << a << endl <<
        "b: " << b << endl <<
        "c: " << c << endl <<
        "d: " << d << endl;
    if (a < c)
    {
        cout << "a < c" << endl;
    }
    else
    {
        cout << "NOT a < c" << endl;
    }
    if (d < d)
    {
        cout << "d < d" << endl;
    }
    else
    {
        cout << "NOT d < d" << endl;
    }
    if (d <= d)
    {
        cout << "d <= d" << endl;
    }
    else
    {
        cout << "NOT d <= d" << endl;
    }

    return 0;
}

