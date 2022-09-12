#include <iostream>
#include <cmath>

using namespace std;

/*1. Создать абстрактный класс Figure (фигура). Его наследниками являются классы Parallelogram (параллелограмм) и 
Circle (круг). Класс Parallelogram — базовый для классов Rectangle (прямоугольник), Square (квадрат), Rhombus (ромб). 
Для всех классов создать конструкторы. Для класса Figure добавить чисто виртуальную функцию area() (площадь). 
Во всех остальных классах переопределить эту функцию, исходя из геометрических формул нахождения площади.*/

//Задание 1
class Figure
{
protected:
    double mA;
    double mB;
public:
   virtual double area() = 0;
   Figure(double A, double B) : mA(A), mB(B)
   {

   }
};

class Parallelogram : virtual public Figure
{
public:
    Parallelogram(double A, double B):Figure(A, B)
    {

    }
    double area()
    {
        cout << "   Parallelogram Area = " << mA*mB << endl;
        return 0;
    }
};

class Circle : virtual public Figure
{
public:
    Circle(double A, double B) : Figure(A, B)
    {

    }
    double area()
    {
        cout << "   Circle Area = " << mB*pow(mA, 2) << endl;
        return 0;
    }
};

class Rectangle : virtual public Parallelogram
{
public:
    Rectangle(double A, double B) : Figure(A, B), Parallelogram(A, B)
    {

    }
    double area()
    {
        cout << "   Rectangle Area = " << mA*mB << endl;
        return 0;
    }
};

class Square : virtual public Parallelogram
{
public:
    Square(double A, double B) : Figure(A, B), Parallelogram(A, B)
    {

    }
    double area()
    {
        cout << "   Square Area = " << pow (mA, 2) << endl;
        return 0;
    }
};

class Rhombus : virtual public Parallelogram
{
public:
    Rhombus(double A, double B) : Figure(A, B), Parallelogram(A, B)
    {

    }
    double area()
    {
        cout << "   Rhombus Area = " << mA * mB << endl;
        return 0;
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

//Задание 4
/*4. Создать класс Card, описывающий карту в игре БлэкДжек. У этого класса должно быть три поля: масть, значение карты 
и положение карты (вверх лицом или рубашкой). Сделать поля масть и значение карты типом перечисления (enum). 
Положение карты - тип bool. Также в этом классе должно быть два метода:
метод Flip(), который переворачивает карту, т.е. если она была рубашкой вверх, то он ее поворачивает лицом вверх, и наоборот.
метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.*/

enum class m_suit : char { Diamonds = 'D', Hearts = 'H', Clubs = 'C', Spades = 'S' };
enum class m_cardvalue : int
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
    Card(bool isFaceUp, m_suit suit, m_cardvalue cardvalue) : m_isFaceUp(isFaceUp), suit(suit), cardvalue(cardvalue)
    {

    }
    void Flip()
    {
        m_isFaceUp = !m_isFaceUp;
    }
    m_cardvalue GetValue()
    {
        return cardvalue;
    }
    void print()
    {
        cout << "   Face Up: " << m_isFaceUp << endl << "   Suit: " << static_cast<char>(suit) << endl << "   Cardvalue: " << static_cast<int>(cardvalue) << endl;
    }
};



int main()
{
    cout << endl;
    cout << "   Exercise 1";
    cout << endl << endl;

    Parallelogram A(15, 17);
    A.area();

    Circle B(4, 3.14);
    B.area();

    Rectangle C(6, 4);
    C.area();

    Square D(6, 1);
    D.area();

    Rhombus E(7, 3);
    E.area();

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
    cout << "   Exercise 4";
    cout << endl << endl;

    Card a(false, m_suit::Hearts, m_cardvalue::QUEEN);
    a.Flip();
    a.print();

    return 0;
}




