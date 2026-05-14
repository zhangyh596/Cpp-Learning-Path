#include <iostream>
using namespace std;

class Date
{
private:
    int _year;
    int _month;
    int _day;

public:
    int GetMonthDay(int year, int month)
    {
        int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        int day = days[month];
        if ((year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) && month == 2)
        {
            day = 29;
        }
        return day;
    }

    Date(int year = 2026, int month = 4, int day = 28)
    {
        _year = year;
        _month = month;
        _day = day;
    }

    Date &operator-=(int day)
    {
        _day -= day;
        while (_day <= 0)
        {
            --_month;
            if (_month == 0)
            {
                --_year;
                _month = 12;
            }

            _day += GetMonthDay(_year, _month);
        }

        return *this;
    }

    void print()
    {
        cout << _year << "-" << _month << "-" << _day << endl;
    }
};

int main()
{
    Date d1;
    d1.print();
    return 0;
}