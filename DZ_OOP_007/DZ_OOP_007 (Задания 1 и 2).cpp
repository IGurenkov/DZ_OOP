#include <iostream>
#include <memory>

using namespace std;

/*1. Создайте класс Date с полями день, месяц, год и методами доступа к этим полям.Перегрузите оператор вывода для данного класса.
Создайте два "умных" указателя today и date.Первому присвойте значение сегодняшней даты.Для него вызовите по отдельности методы доступа
к полям класса Date, а также выведите на экран данные всего объекта с помощью перегруженного оператора вывода.Затем переместите ресурс,
которым владеет указатель today в указатель date.Проверьте, являются ли нулевыми указатели today и date и выведите соответствующую информацию
об этом в консоль.*/

/*2. По условию предыдущей задачи создайте два умных указателя date1 и date2.
• Создайте функцию, которая принимает в качестве параметра два умных указателя типа Date и сравнивает их между собой
(сравнение происходит по датам).Функция должна вернуть более позднюю дату.
• Создайте функцию, которая обменивает ресурсами(датами) два умных указателя, переданных в функцию в качестве параметров.

Примечание: обратите внимание, что первая функция не должна уничтожать объекты, переданные ей в качестве параметров.*/

class Date
{
protected:
    unsigned int mDay;
    unsigned int mMonth;
    unsigned int mYear;
    friend ostream& operator << (ostream& out, Date& mData);

public:
    Date(unsigned int Day, unsigned int Month, unsigned int Year) : mDay(Day), mMonth(Month), mYear(Year) {};

    int SetDay() const
    {        
        return mDay;
    }
    int SetMonth() const
    {
        return mMonth;
    }
    int SetYear() const
    {
        return mYear;
    }
    friend Date PointerDate(shared_ptr<Date> date1, shared_ptr<Date> date2);
    friend void PointerSwap(shared_ptr<Date> date1, shared_ptr<Date> date2);
};

ostream& operator << (ostream& out, Date& mData)
{
    return out << "   " << mData.SetDay() << "." << mData.SetMonth() << "." << mData.SetYear();
};

Date PointerDate(shared_ptr<Date> date1, shared_ptr<Date> date2)
{
    if (date1->mYear > date2->mYear)
    {
        cout << "   Past date is: " << *date1 << endl;
        return *date1;        
    }
    else if (date2->mYear > date1->mYear)
    {
        cout << "   Past date is: " << *date2 << endl;
        return *date2;
    }
    else if (date1->mMonth > date2->mMonth)
    {
        cout << "   Past date is: " << *date1 << endl;
        return *date1;
    }
    else if (date2->mMonth > date1->mMonth)
    {
        cout << "   Past date is: " << *date2 << endl;
        return *date2;
    }
    else if (date1->mDay > date2->mDay)
    {
        cout << "   Past date is: " << *date1 << endl;
        return *date1;
    }
    else if (date2->mDay > date1->mDay)
    {
        cout << "   Past date is: " << *date2 << endl;
        return *date2;
    }
    else
    {
        cout << "   Same date: " << *date1 << ", " << *date2 << endl;        
    }    
}

void PointerSwap(shared_ptr<Date> date1, shared_ptr<Date> date2)
{
    swap(date1, date2);
    cout << *date1 << endl << *date2 << endl;
}

int main()
{
    cout << endl;
    cout << "   Exercise 1";
    cout << endl << endl;

    shared_ptr<Date> todayPtr = make_shared<Date>(25, 9, 2022);       

    todayPtr->SetDay();
    todayPtr->SetMonth();
    todayPtr->SetYear();

    cout << *todayPtr;
    cout << endl;
    shared_ptr<Date> datePtr = move(todayPtr);
    cout << *datePtr;
    cout << endl;
    for (;;)
    {
        if (todayPtr == nullptr)
        {
            cout << "   Pointer todayPtr is empty" << endl;
        }
        else
        {
            cout << "   Pointer todayPtr is NOT empty" << endl;
        }
        break;
    }
    for (;;)
    {
        if (datePtr == nullptr)
        {
            cout << "   Pointer datePtr is empty" << endl;
        }
        else
        {
            cout << "   Pointer datePtr is NOT empty" << endl;
        }
        break;
    }
    
    cout << endl;
    cout << "   Exercise 2";
    cout << endl << endl;

    shared_ptr<Date> date1 = make_shared<Date>(25, 12, 2022);

    shared_ptr<Date> date2 = make_shared<Date>(27, 12, 2022);

    PointerDate(date1, date2);    
    cout << endl;
    PointerSwap(date1, date2);

    return 0;
}

