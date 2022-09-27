#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;

class Card
{
    friend ostream& operator << (ostream& out, const Card& card);

public:
    enum rank
    {
        ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
        JACK, QUEEN, KING
    };

    enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };

    Card(rank r, suit s, bool IsFaceUp) : m_Rank(r), m_Suit(s), m_IsFaceUp(IsFaceUp)
    {

    }

    void Flip()
    {
        m_IsFaceUp = !(m_IsFaceUp);
    }
    int GetValue()
    {
        int value = 0;
        if (m_IsFaceUp)
        {
            value = m_Rank;
            if (value > 10)
            {
                value = 10;
            }
        }
        return value;
    }
private:
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;
};

ostream& operator<< (ostream& out, const Card& card)
{
    const string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    const string SUITS[] = { "C", "D", "H", "S" };

    if (card.m_IsFaceUp)
    {
        out << "Card: " << RANKS[card.m_Rank] << SUITS[card.m_Suit];
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

    vector<Card*> m_Cards;

public:

    Hand()
    {
        m_Cards.reserve(7);
    }

    virtual ~Hand()
    {
        Clear();
    }

    void Add(Card* pCard)
    {
        m_Cards.push_back(pCard);
    }

    void Clear()
    {
        vector<Card*>::iterator iter = m_Cards.begin();
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        {
            delete* iter;
            *iter = 0;
        }
        
        m_Cards.clear();
    }

    int GetTotal()
    {
        int sum = 0;
        vector<Card*>::const_iterator iter;

        for (iter = m_Cards.begin(); iter != m_Cards.end(); iter++)
        {
            sum += (*iter)->GetValue();
        }

        bool containsAce = false;
        for (iter = m_Cards.begin(); iter != m_Cards.end(); iter++)
        {
            if ((*iter)->GetValue() == Card::ACE)
            {
                containsAce = true;
            }
        }

        if (containsAce && sum <= 11)
        {
            sum += 10;
        }
        return sum;
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


ostream& operator << (ostream& out, GenericPlayer& genericplayer)
{
    out << genericplayer.m_Name << ":   ";
    vector<Card*>::const_iterator pCard;
    if (!genericplayer.m_Cards.empty())
    {
        for (pCard = genericplayer.m_Cards.begin();
            pCard != genericplayer.m_Cards.end();
            ++pCard)
        {
            out << *(*pCard) << "   ";
        }
        if (genericplayer.GetTotal() != 0)
        {
            cout << "(" << genericplayer.GetTotal() << ")";
        }
        else
        {
            out << "<EMPTY>";
        }
    }
    return out;
}

class Player : public GenericPlayer
{
public:

    Player(const string& name) : GenericPlayer(name) {};

    virtual ~Player() {};

    bool IsHitting() override
    {
        cout << m_Name << "Want you a Card? Press Y (Yes) or another (No): ";
        char addcard;
        cin >> addcard;
        if (addcard == 'Y' || addcard == 'y')
        {
            return (addcard == 'y' || addcard == 'Y');
        }
        else
        {
            return false;
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

class House : public GenericPlayer
{
public:
    House(const string& name = "House") : GenericPlayer(name) {};
    virtual ~House() {};

    virtual bool IsHitting() override
    {
        return (GetTotal() <= 16);
    }

    void FlipFirstCard()
    {
        if (!(m_Cards.empty()))
        {
            m_Cards[0]->Flip();
        }
        else
        {
            cout << "No card to flip!" << endl;
        }
    }
};

class Deck : public Hand
{
public:
    Deck()
    {
        m_Cards.reserve(52);
        Populate();
    };
    virtual ~Deck() {};

    void Populate()
    {
        Clear();

        for (int s = Card::CLUBS; s <= Card::SPADES; ++s)
        {
            for (int r = Card::ACE; r <= Card::KING; ++r)
            {
                Add(new Card(static_cast<Card::rank>(r), static_cast<Card::suit>(s), true));
            }
        }
    }

    void Shuffle()
    {
        random_shuffle(m_Cards.begin(), m_Cards.end());
    }

    void Deal(Hand& aHand)
    {
        if (!m_Cards.empty())
        {
            aHand.Add(m_Cards.back());
            m_Cards.pop_back();
        }
        else
        {
            cout << "Out of cards. Unable to deal.";
        }
    }
    void AdditionalCards(GenericPlayer& aGenericPlayer)
    {
        cout << endl;

        while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting())
        {
            Deal(aGenericPlayer);
            cout << aGenericPlayer << endl;
            if (aGenericPlayer.IsBusted())
            {
                aGenericPlayer.Bust();
            }
        }
    }
};

class Game
{
private:
    House m_House;
    Deck m_Deck;
    vector<Player> m_Players;
public:
    Game(const vector<string>& names)
    {
        vector<string>::const_iterator pName;
        for (pName = names.begin(); pName != names.end(); ++pName)
        {
            m_Players.push_back(Player(*pName));
        }

        srand(static_cast<unsigned int>(time(0)));
        m_Deck.Populate();
        m_Deck.Shuffle();
    }

    ~Game() {};

    void Play()
    {
        vector<Player>::iterator pPlayer;
        for (int i = 0; i < 2; ++i)
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            {
                m_Deck.Deal(*pPlayer);
            }
            m_Deck.Deal(m_House);
        }

        m_House.FlipFirstCard();

        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            cout << *pPlayer << endl;
        }
        cout << m_House << endl;

        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            m_Deck.AdditionalCards(*pPlayer);
        }

        m_House.FlipFirstCard();
        cout << endl << m_House;

        m_Deck.AdditionalCards(m_House);

        if (m_House.IsBusted())
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            {
                if (!(pPlayer->IsBusted()))
                {
                    pPlayer->Win();
                }
            }
        }
        else
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            {
                if (!(pPlayer->IsBusted()))
                {
                    if (pPlayer->GetTotal() > m_House.GetTotal())
                    {
                        pPlayer->Win();
                    }
                    else if (pPlayer->GetTotal() < m_House.GetTotal())
                    {
                        pPlayer->Lose();
                    }
                    else
                    {
                        pPlayer->Push();
                    }
                }
            }
        }
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            pPlayer->Clear();
        }
        m_House.Clear();
    }
};

int main()
{    
    setlocale(LC_ALL, "ru");
    SetConsoleTitle(L"BlackJack");

    cout << "       Welcome to Blackjack!" << endl << endl;
    cout << "Краткие правила игры:" << endl << endl;
    cout << "1. Главная цель игры набрать больше очков чем дилер (House) и не сделать перебор, перебор это больше 21 очка." << endl;
    cout << "2. В начале игры выдаются по две карты игроку и дилеру, первая карта дилера скрыта." << endl;
    cout << "3. Возьмите ещё карту, если считаете, что у вас меньше, чем у дилера." << endl;
    cout << "4. Очки карт с цифрами равны номиналу карты, а валет, дама и король дают 10 очков, туз даёт 1 очко или 11, если не будет перебора." << endl;
    cout << "5. Дилер будет брать карты пока у него меньше 17 очков." << endl;
    cout << "6. Вы выиграли, если после отказа от взятия карты у вас больше очков, чем у дилера, но меньше, либо равно 21 очку, в противном случае выигрывает дилер." << endl;
    cout << "7. Если у игрока и дилера одинаковое количество очков, то объявляется ничья." << endl << endl;

    int numPlayers = 0;
    while (numPlayers < 1 || numPlayers > 7)
    {
        cout << "How many players? (1 - 7): ";
        cin >> numPlayers;
    }
    vector<string> names;
    string name;
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Enter player name: ";
        cin >> name;
        names.push_back(name);
    }
    cout << endl;

    Game aGame(names);
    char again = 'y';
    while (again != 'n' && again != 'N')
    {
        aGame.Play();
        cout << endl << "Do you want to play again? (Y/N): ";
        cin >> again;
        cout << endl;
    }

    return 0;
}