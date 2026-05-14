#include <iostream>
using namespace std;

class Date
{
public:
    Date(int year = 0, int month = 1, int day = 1)
    {
        _year = year;
        _month = month;
        _day = day;
    }

    void Print() const
    {
        cout << _year << "-" << _month << "-" << _day << endl;
    }

private:
    int _year;
    int _month;
    int _day;
};

void f(const Date &d)
{
    d.Print();
}

int main()
{
    Date d1(2026, 4, 29);
    return 0;
}