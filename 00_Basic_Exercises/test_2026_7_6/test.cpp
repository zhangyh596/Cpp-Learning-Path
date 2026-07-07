#include <iostream>
using namespace std;

const double PI = 3.14159;

class Point
{
private:
    double x, y;

public:
    Point(double x_val, double y_val)
        : x(x_val), y(y_val)
    {
    }

    double getx()
    {
        return x;
    }

    double gety()
    {
        return y;
    }
};

class Circle : public Point
{
private:
    double r;

public:
    Circle(double x_val, double y_val, double r_val)
        : Point(x_val, y_val), r(r_val)
    {
    }

    double getr()
    {
        return r;
    }

    double area()
    {
        return PI * r * r;
    }
};

int main()
{
    Circle c(5, 7, 9);

    cout << "圆心：(" << c.getx() << "," << c.gety() << ")" << endl;
    cout << "半径：" << c.getr() << endl;
    cout << "面积：" << c.area() << endl;

    return 0;
}