#include <iostream>
#include <cassert> // для assert()
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <numeric>

using namespace std;

//Задание 1
/*1. Добавить в контейнерный класс, который был написан в этом уроке, методы:
• для удаления последнего элемента массива(аналог функции pop_back() в векторах)
• для удаления первого элемента массива(аналог pop_front() в векторах)
• для сортировки массива
• для вывода на экран элементов.*/

class ArrayInt
{
private:
    int m_length;
    int* m_data;

public:
    ArrayInt() : m_length(0), m_data(nullptr) { }

    ArrayInt(int length) :
        m_length(length)
    {
        assert(length >= 0);

        if (length > 0) {
            m_data = new int[length];
        }
        else {
            m_data = nullptr;
        }
    }

    ~ArrayInt()
    {
        delete[] m_data;
    }

    void erase()
    {
        delete[] m_data;

        // Здесь нам нужно указать m_data значение nullptr, чтобы на выходе не было висячего указателя
        m_data = nullptr;
        m_length = 0;
    }

    int getLength() { return m_length; }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    // Функция resize изменяет размер массива. Все существующие элементы сохраняются. Процесс медленный
    void resize(int newLength)
    {
        // Если массив уже нужной длины — return
        if (newLength == m_length) {
            return;
        }

        // Если нужно сделать массив пустым — делаем это и затем return
        if (newLength <= 0) {
            erase();
            return;
        }

        // Теперь знаем, что newLength >0
        // Выделяем новый массив
        int* data = new int[newLength];

        // Затем нужно разобраться с количеством копируемых элементов в новый массив
        // Нужно скопировать столько элементов, сколько их есть в меньшем из массивов
        if (m_length > 0) {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;

            // Поочередно копируем элементы
            for (int index = 0; index < elementsToCopy; ++index) {
                data[index] = m_data[index];
            }
        }

        // Удаляем старый массив, так как он нам уже не нужен
        delete[] m_data;

        // И используем вместо старого массива новый! Обратите внимание, m_data указывает
        // на тот же адрес, на который указывает наш новый динамически выделенный массив. Поскольку
        // данные были динамически выделенные — они не будут уничтожены, когда выйдут из области видимости
        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        // Проверка корректности передаваемого индекса
        assert(index >= 0 && index <= m_length);

        // Создаем новый массив на один элемент больше старого массива
        int* data = new int[m_length + 1];

        // Копируем все элементы до index-а
        for (int before = 0; before < index; ++before) {
            data[before] = m_data[before];
        }

        // Вставляем новый элемент в новый массив
        data[index] = value;

        // Копируем все значения после вставляемого элемента
        for (int after = index; after < m_length; ++after) {
            data[after + 1] = m_data[after];
        }

        // Удаляем старый массив и используем вместо него новый 
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void push_back(int value) { insertBefore(value, m_length); }

    //Задание 1
    int DeleteLastElem()
    {        
        int m = m_data[m_length - 1];
        m_length--;
        int* Arr = new int[m_length];
        
        for (int i = 0; i < m_length; i++)
        {
            Arr[i] = m_data[i];            
        }               

        delete[] m_data;
        
        m_data = Arr;
                
        return m;
        cout << endl;
    }

    int DeleteFirstElem()
    {
        int n = *m_data;
        m_length--;
        int* Arr = new int[m_length];

        for (int i = 0; i < m_length; i++)
        {
            Arr[i] = m_data[i + 1];
        }

        delete[] m_data;

        m_data = Arr;

        return n;
        cout << endl;
    }

    void insertionSort()
    {
        for (int i = 1; i < m_length; i++)
        {
            for (int j = i; j > 0 && m_data[j - 1] > m_data[j]; j--)
            {
                int temp = m_data[j - 1];
                m_data[j - 1] = m_data[j];
                m_data[j] = temp;
            }
        }
        cout << "   ";
        for (int i = 0; i < m_length; i++)
        {
            cout << m_data[i] << " ";
        }
        cout << endl;
    }

    void printArr()
    {
        cout << "   ";
        for (int i = 0; i < m_length; i++)
        {
            cout << m_data[i] << " ";
        }
        cout << endl;
    }
};

//Задание 2
//2. Дан вектор чисел, требуется выяснить, сколько среди них различных.Постараться использовать максимально быстрый алгоритм.


int Unique(vector<int> &Arr)
{    
    unordered_set<int> s;
    copy(begin(Arr), end(Arr), inserter(s, s.begin()));
    cout << "   Unique Numbers: " << s.size() << endl;
    
    return 0;
}

/*3. Реализовать класс Hand, который представляет собой коллекцию карт.В классе будет одно поле : вектор указателей карт
(удобно использовать вектор, т.к.это по сути динамический массив, а тип его элементов должен быть - указатель на объекты класса Card).
Также в классе Hand должно быть 3 метода :
    • метод Add, который добавляет в коллекцию карт новую карту, соответственно он принимает в качестве параметра указатель на новую карту
    • метод Clear, который очищает руку от карт
    • метод GetValue, который возвращает сумму очков карт руки(здесь предусмотреть возможность того, что туз может быть равен 11).*/
//Задание 3

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
        //m_CardVec.clear();   Точно не знаю надо ли удалять все карты из руки...
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

int main()
{
    cout << endl;
    cout << "   Exercise 1";
    cout << endl << endl;

    ArrayInt arrayInt;
    arrayInt.push_back(100);
    arrayInt.push_back(0);
    arrayInt.push_back(1);
    arrayInt.push_back(10);

    arrayInt.printArr();

    arrayInt.insertionSort(); //Сортировка по возрастанию

    arrayInt.DeleteLastElem(); //Удаление последнего элемента
    arrayInt.printArr();

    arrayInt.DeleteFirstElem(); //Удаление первого элемента
    arrayInt.printArr();

    cout << endl;
    cout << "   Exercise 2";
    cout << endl << endl;

    vector<int> Arr = { 10, 8, 2, 4, 2, 2 };
    Unique(Arr); //Поиск и вывод кол-ва уникальных элементов

    cout << endl;
    cout << "   Exercise 3";
    cout << endl << endl;

    Card a(false, m_suit::Hearts, m_cardvalue::TWO);
    Card b(false, m_suit::Clubs, m_cardvalue::TWO);
    Card c(false, m_suit::Clubs, m_cardvalue::ACE);

    Hand X; //Рука

    X.Add(&a);   //
    X.Add(&b);   //Карты в руке
    X.Add(&c);   //

    X.printHand(); //Вывод руки с картами в консоль

    X.GetTotal(); //Подсчёт и вывод очков с учётом ТУЗ 1 и 11

    return 0;
}

