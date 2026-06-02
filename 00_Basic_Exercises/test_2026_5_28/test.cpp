// #include <iostream>
// #include <string>
// using namespace std;

// int main()
// {
//     // string s1;
//     // string s2("hello");
//     // string s3(s2);

//     // cout << s1 << endl;
//     // cout << s2 << endl;
//     // cout << s3 << endl;

//     string s1("hello");
//     s1 += ' ';
//     s1 += "world";

//     cout << s1 << endl;

//     // 反向迭代器打印
//     int val = 0;
//     string nums("12345");
//     string::reverse_iterator rit = nums.rbegin();
//     while (rit != nums.rend())
//     {
//         val *= 10;
//         val += (*rit - '0');
//         ++rit;
//     }

//     cout << val << endl;
//     return 0;
// }

#include <iostream>
using namespace std;

template <class T>
class Vector
{
public:
    // 构造函数
    Vector(size_t capacity = 10)
        : _pData(new T[capacity]), _size(0), _capacity(capacity)
    {
    }

    // 析构函数
    ~Vector();

private:
    T *_pData;
    size_t _size;
    size_t _capacity;
};

template <class T>
Vector<T>::~Vector()
{
    if (_pData)
    {
        delete[] _pData;
        _pData = nullptr;
        _size = _capacity = 0;
    }
}

int main()
{
    Vector<int> v1(20);
    Vector<double> v2;
    return 0;
}