#include <iostream>

using namespace std;

//Задание 1

class Person
{
protected:

    string m_Name;
    string m_Sex;
    unsigned int m_Age;
    float m_Weight;

public:

    Person(const string &Name, const string &Sex, unsigned int Age, float Weight)
        : m_Name(Name), m_Sex(Sex), m_Age(Age), m_Weight(Weight)
    {

    };    
};

class Student : public Person
{
private:

    static int Count;

public:
    
    unsigned int m_YearOfStudy;
    
    Student(const string &Name, const string &Sex, unsigned int Age, float Weight, unsigned int YearOfStudy) :
        Person(Name, Sex, Age, Weight), m_YearOfStudy(YearOfStudy) 
    {
        Count++;
    }

    unsigned int GetmYearOfStudy() const
    {
        return m_YearOfStudy;
    }
    void SetmYearOfStudy(const unsigned int valuem_YearOfStudy)
    {
        m_YearOfStudy = valuem_YearOfStudy;
    }

    void print()
    {
        cout << "   Name: " << m_Name << endl;
        cout << "   Sex: " << m_Sex << endl;
        cout << "   Age: " << m_Age << endl;
        cout << "   Weight: " << m_Weight << endl;
        cout << "   Year of Study: " << m_YearOfStudy << endl;
    }    
        
    static void ShowCount()
    { 
        cout << "   Number of students: " << Count << endl << endl;
    }    
};

//Задание 2

class Fruit
{
public:
    string mName;
    string mColor;

    Fruit(const string &Name = "", const string &Color = "")
        : mName(Name), mColor(Color)
    {

    }
    string getName() const
    { 
        return mName; 
    }
    string getColor() const 
    { 
        return mColor; 
    }
};

class Apple : public virtual Fruit
{
public:

    Apple(const string &Name = "", const string &Color = "") : Fruit(Name, Color)
    {

    }
};

class Banana : public virtual Fruit
{
public:
    Banana(const string& Name = "", const string& Color = "") : Fruit(Name, Color)
    {

    }
};

class GrannySmith : public virtual Apple
{
public:
    GrannySmith(const string& Name = "", const string& Color = "") : Apple(Name, Color)
    {

    }
};

int Student::Count = 0;

int main()
{
    cout << endl;
    //Задание 1
    cout << "   Exercise 1";
    cout << endl << endl;

    Student Ivan ("Ivan", "Man", 22, 81, 2022);
    Ivan.m_YearOfStudy = 2019;
    Ivan.print();        
    cout << endl;

    Student Vova("Vova", "Man", 34, 79, 2021);
    Vova.m_YearOfStudy = 2025;
    Vova.print();    
    cout << endl;

    Student Yulya("Yulya", "Women", 27, 55, 2019);
    Yulya.m_YearOfStudy = 2022;
    Yulya.print();   
    cout << endl;

    Student::ShowCount();    

    //Задание 2
    cout << "   Exercise 2";
    cout << endl << endl;

    Apple a;
    a.mName = "apple";
    a.mColor = "red";

    Banana b;
    b.mName = "banana";
    b.mColor = "yellow";

    GrannySmith c;
    c.mName = "Granny Smith apple";
    c.mColor = "green";

    cout << "   My " << a.getName() << " is " << a.getColor() << endl;
    cout << "   My " << b.getName() << " is " << b.getColor() << endl;
    cout << "   My " << c.getName() << " is " << c.getColor() << endl;

    return 0;
}
    //Задание 3

/*
Класс игрока и класс, возможно наследуемый от класса игрока, дилер или наоборот.
Нужен одномерный массив или энум с обозначением карт на три колоды для большей случайности игры.
Массив/энум возможно должен быть в отдельном классе, который наследуют или в основном классе, который наследуют.
Игрок и дилер должны вытаскивать значения из одного и того же массива/энума и он должен уменьшаться (если
не считаем, что количество карт бесконечно).
Переменные Игрок, Дилер, рука игрока, рука дилера, банк игрока, ставка игрока и если надо, то случайная 
ставка дилера но не больше определенного размера чтобы игра не закончилась быстро и банк дилера и методы их заполнения.
Также нужен метод случайного выбора карт для игрока и дилера с записью в соответствующие переменные (наверно в руки) 
и вывод их на экран.
Метод уменьшающий и увеличивающую банк игрока и может дилера при проигрыше или выигрыше
Раздача карт должна происходить по одной с запросом у пользователя "ещё" или "хватит"*/
