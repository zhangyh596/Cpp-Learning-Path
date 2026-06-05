#include "MyString.h"

using namespace std; // 在 .cpp 文件中可以使用这个，不影响其他文件

// 1. 默认构造函数
MyString::MyString() : _length(0), _capacity(0)
{
    _data = new char[1];
    _data[0] = '\0';
}

// 2. 带参构造函数
MyString::MyString(const char *str)
{
    if (str != nullptr)
    {
        _length = strlen(str);
        _capacity = _length;
        _data = new char[_capacity + 1];
        strcpy(_data, str);
    }
    else
    {
        _length = 0;
        _capacity = 0;
        _data = new char[1];
        _data[0] = '\0';
    }
}

// 3. 析构函数
MyString::~MyString()
{
    delete[] _data;
}

// 辅助函数
const char *MyString::c_str() const
{
    return _data ? _data : "";
}

size_t MyString::size() const
{
    return _length;
}

void MyString::set_char(size_t index, char ch)
{
    if (index < _length)
    {
        _data[index] = ch;
    }
}

// 4. 拷贝构造函数
MyString::MyString(const MyString &other)
{
    _length = other._length;
    _capacity = _length;
    _data = new char[_capacity + 1];
    strcpy(_data, other._data);
}

// 5. 拷贝赋值运算符
MyString &MyString::operator=(const MyString &other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] _data;

    _length = other._length;
    _capacity = _length;
    _data = new char[_capacity + 1];
    strcpy(_data, other._data);

    return *this;
}

// 6. 移动构造函数
MyString::MyString(MyString &&other) noexcept
    : _data(other._data), _length(other._length), _capacity(other._capacity)
{
    other._data = nullptr;
    other._length = 0;
    other._capacity = 0;
    cout << "【触发移动构造函数】" << endl;
}

// 7. 移动赋值运算符
MyString &MyString::operator=(MyString &&other) noexcept
{
    cout << "【触发移动赋值运算符】" << endl;

    if (this != &other)
    {
        delete[] _data;
        _data = other._data;
        _length = other._length;
        _capacity = other._capacity;

        other._data = nullptr;
        other._length = 0;
        other._capacity = 0;
    }
    return *this;
}

// 8. 下标操作符 (普通)
char &MyString::operator[](size_t index)
{
    return _data[index];
}

// 9. 下标操作符 (常量)
const char &MyString::operator[](size_t index) const
{
    return _data[index];
}

// 10. 追加操作符 (+=)
MyString &MyString::operator+=(const MyString &other)
{
    if (other._length == 0)
        return *this;

    size_t new_length = _length + other._length;
    char *new_data = new char[new_length + 1];

    if (_data)
    {
        strcpy(new_data, _data);
    }
    else
    {
        new_data[0] = '\0';
    }

    if (other._data)
    {
        strcat(new_data, other._data);
    }

    delete[] _data;

    _data = new_data;
    _length = new_length;
    _capacity = new_length;

    return *this;
}

// --- 下面是非成员函数的实现 ---

// 11. 相加操作符 (+)
MyString operator+(const MyString &lhs, const MyString &rhs)
{
    MyString result(lhs);
    result += rhs;
    return result;
}

// 12. 重载输出流操作符 (<<)
ostream &operator<<(ostream &os, const MyString &str)
{
    os << str.c_str();
    return os;
}

// 13. 比较操作符
bool operator==(const MyString &lhs, const MyString &rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const MyString &lhs, const MyString &rhs)
{
    return !(lhs == rhs);
}

bool operator<(const MyString &lhs, const MyString &rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator>(const MyString &lhs, const MyString &rhs)
{
    return rhs < lhs;
}

bool operator<=(const MyString &lhs, const MyString &rhs)
{
    return !(lhs > rhs);
}

bool operator>=(const MyString &lhs, const MyString &rhs)
{
    return !(lhs < rhs);
}