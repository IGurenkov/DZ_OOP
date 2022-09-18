#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Задание 1

//Реализовать шаблон класса Pair1, который позволяет пользователю передавать данные одного типа парами.

template< class T1 >
class Pair1
{
    T1 mA;
    T1 mB;

public:

    Pair1(T1 A, T1 B) : mA(A), mB(B)
    {

    }

    T1 first() const
    {
        return mA;
    }

    T1 second() const
    {
        return mB;
    }
};

//Задание 2

//Реализовать класс Pair, который позволяет использовать разные типы данных в передаваемых парах.

template < class T1, class T2 >
class Pair
{
protected:
    T1 mC;
    T2 mD;
public:

    Pair(T1 C, T2 D) : mC(C), mD(D)
    {

    }

    T1 first() const
    {
        return mC;
    }

    T2 second() const
    {
        return mD;
    }
};

//Задание 3

//Написать шаблон класса StringValuePair, в котором первое значение всегда типа string, а второе — любого типа. 
//Этот шаблон класса должен наследовать частично специализированный класс Pair, в котором первый параметр — string, 
//а второй — любого типа данных.

template <class T2>
class StringValuePair : public Pair < string, T2 >
{
    
public:
    StringValuePair(string C, T2 D) : Pair <string, T2> (C, D) {};
   
};

//Задание 4

/*Согласно иерархии классов, которая представлена в методичке к уроку 3, от класса Hand наследует класс GenericPlayer,
который обобщенно представляет игрока, ведь у нас будет два типа игроков - человек и компьютер.Создать класс GenericPlayer, 
в который добавить поле name - имя игрока.Также добавить 3 метода:
• IsHitting() - чисто виртуальная функция, возвращает информацию, нужна ли игроку еще одна карта.
• IsBusted() - возвращает bool значение, есть ли у игрока перебор
• Bust() - выводит на экран имя игрока и объявляет, что у него перебор.*/

//Из прошлого ДЗ

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
        cout << "   Face Up: " << m_isFaceUp << endl << "   Suit: " << static_cast<char>(suit) << endl << "   Cardvalue: " << static_cast<int>(cardvalue) << endl << endl;
    }
};

class Hand
{
private:

    vector<Card*> m_CardVec;

public:
    
    Hand()
    {

    }

    void Add(Card* pCard)
    {
        m_CardVec.push_back(pCard);
    }

    void Clear()
    {
        for (auto p : m_CardVec)
        {
            delete p;
        }
        m_CardVec.clear();
    }

    int GetTotal()
    {
        int sum = 0;
        vector<Card*>::const_iterator iter;

        for (iter = m_CardVec.begin(); iter != m_CardVec.end(); iter++)
        {
            sum += static_cast<int>((*iter)->GetValue());
        }

        bool containsAce = false;
        for (iter = m_CardVec.begin(); iter != m_CardVec.end(); iter++)
        {
            if ((*iter)->GetValue() == m_cardvalue::ACE)
            {
                containsAce = true;
            }
        }

        if (containsAce && sum <= 11)
        {
            sum += 10;
            cout << "   Value = " << sum << endl << endl;
        }
        else
        {
            cout << "   Value = " << sum << endl << endl;
        }

        return sum;
    }

    void printHand()
    {
        for (size_t i = 0; i < m_CardVec.size(); i++)
        {
            cout << "Card " << i + 1 << endl;
            m_CardVec[i]->print();
        }
    }
};

//Само задание

class GenericPlayer : public Hand
{
    string m_Name;

public:

    virtual bool IsHitting() = 0;

    bool IsBusted()
    {
        return GetTotal() > 21;               
    }
    void Bust()
    {        
        cout << "Player" << m_Name << "Bust!";        
    }
};

int main()
{
    cout << endl;
    cout << "   Exercise 1";
    cout << endl << endl;

    Pair1<int> p1(6, 9);
    cout << "   Pair: " << p1.first() << "; " << p1.second() << endl;

    const Pair1<double> p2(3.4, 7.8);
    cout << "   Pair: " << p2.first() << "; " << p2.second() << endl;

    cout << endl;
    cout << "   Exercise 2";
    cout << endl << endl;

    Pair<int, double> p3(6, 7.8);
    cout << "   Pair: " << p3.first() << "; " << p3.second() << endl;

    const Pair<double, int> p4(3.4, 5);
    cout << "   Pair: " << p4.first() << "; " << p4.second() << endl;

    cout << endl;
    cout << "   Exercise 3";
    cout << endl << endl;

    StringValuePair<int> svp("Amazing", 7);
    std::cout << "   Pair: " << svp.first() << "; " << svp.second() << endl;    

    return 0;
}
