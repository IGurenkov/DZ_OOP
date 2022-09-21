#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Задание 1

class Int
{
public:
    void Input()
    {
        int a;
        cout << "   Write a Integrals number: ";
        while (!(cin >> a) || (cin.peek() != '\n'))
        {              
            cin.clear();
            while (cin.get() != '\n');
            cout << "   Error!" << endl;
            cout << "   Write a Integrals number: ";
        }        
    }
};

//Задание 2

class endll
{
public:
    friend ostream& operator<< (ostream& out, const endll& m_endll);
};

ostream& operator << (ostream& out, const endll& m_endll)
{
    out << endl << endl;
    return out;
};


//Задания 3, 4, 5

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
    friend ostream& operator << (ostream& out, const Card& card);

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

//Задание 5 

ostream& operator<< (ostream& out, const Card& card)
{
    if (card.m_isFaceUp)
    {   
        out << "Card: " << static_cast<int>(card.cardvalue) << static_cast<char>(card.suit);               
    }
    else
    {
        out << "XX";
        
    }
    return out;
}

class Hand
{
protected:

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

class GenericPlayer : public Hand
{
protected:
    string m_Name;
    friend ostream& operator << (ostream& out, GenericPlayer& genericplayer);

public:
    
    GenericPlayer(const string& name = "") : m_Name(name) {};

    virtual ~GenericPlayer() {};

    virtual bool IsHitting() = 0;

    bool IsBusted()
    {
        return (GetTotal() > 21);
    }
    void Bust()
    {
        cout << "Player " << m_Name << " Bust!";
    }    
};

//Задание 5 ещё

ostream& operator << (ostream& out, GenericPlayer& genericplayer)
{
    out << genericplayer.m_Name << ":\t";
    vector<Card*>::const_iterator pCard;
    if (!genericplayer.m_CardVec.empty())
    {
        for (pCard = genericplayer.m_CardVec.begin();
            pCard != genericplayer.m_CardVec.end();
            ++pCard)
        {
            out << *(*pCard) << "\t";
        }
        if (genericplayer.GetTotal() != 0)
        {
            cout << "(" << genericplayer.GetTotal() << ")";
        }
        else
        {
            out << "<empty>";
        }
        return out;
    }
}

//Задание 3

class Player : public GenericPlayer
{
public:

    Player(const string& name = "") {};
    
    virtual ~Player(){};

    virtual bool IsHitting() override
    {
        cout << m_Name << "Want you a Card? Press Y (Yes) or another (No): ";
            char addcard;
            cin >> addcard;
            if (addcard == 'Y' || addcard == 'y')
            {
                return true;
            }           
    }

    void Win() const
    {
        cout << m_Name << " Won!";
    }
    void Lose() const
    {
        cout << m_Name << " Lose!";
    }
    void Push() const
    {
        cout << m_Name << " Push!";
    }
};

//Задание 4

class House : public GenericPlayer
{
public:
    House(const string& name = "House"){};
    virtual ~House(){};

    virtual bool IsHitting() override
    {        
        return (GetTotal() <= 16);
    }    

    void FlipFirstCard()
    {
        if (!(m_CardVec.empty()))
        {
            m_CardVec[0]->Flip();
        }
        else
        {
            cout << "No card to flip!\n";
        }
    }
};

int main()
{
    cout << endl;
    cout << "   Exercise 1";
    cout << endl << endl;
    
    Int a;
    a.Input();
    
    cout << endl;
    cout << "   Exercise 2";
    cout << endl << endl;

    endll endll;

    cout << "   Perevod" << endll << "   stroki" << endll;

    return 0;
}
