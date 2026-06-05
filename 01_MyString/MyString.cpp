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

// 19. 重载流提取运算符 (>>)
istream &operator>>(istream &is, MyString &str)
{
    // 先清空原本字符串里的旧数据（直接赋一个空字符串对象）
    str = MyString();

    char ch;
    // 跳过前导空白字符（空格、回车、制表符等）
    while (is.get(ch) && isspace(ch))
    {
    }

    // 如果读到文件尾(EOF)或者流出错，直接返回
    if (!is)
        return is;

    // 此时 ch 已经是第一个有效字符了
    char buf[1024];
    size_t index = 0;
    buf[index++] = ch;

    // 循环读取，直到遇到下一个空白字符
    while (is.get(ch) && !isspace(ch))
    {
        buf[index++] = ch;
        if (index >= 1023)
        {
            buf[index] = '\0';
            str += MyString(buf);
            index = 0;
        }
    }

    // 把最后残留在缓冲区的数据追加到 str
    if (index > 0)
    {
        buf[index] = '\0';
        str += MyString(buf);
    }

    return is;
}

// 20. 实现 getline 函数
// 核心逻辑：不跳过前导空白，一直读取直到遇到指定的结束符（默认是 '\n'）
istream &getline(istream &is, MyString &str, char delim)
{
    // 清空原本的数据
    str = MyString();

    char buf[1024];
    size_t index = 0;
    char ch;

    // 循环读取，直到读到分隔符或者流结束
    while (is.get(ch) && ch != delim)
    {
        buf[index++] = ch;
        if (index >= 1023) // 缓冲区满了，先倒进 str
        {
            buf[index] = '\0';
            str += MyString(buf);
            index = 0;
        }
    }

    // 倒出最后残留的数据
    if (index > 0)
    {
        buf[index] = '\0';
        str += MyString(buf);
    }

    return is;
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