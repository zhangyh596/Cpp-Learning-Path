#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <cstring>
#include <utility> // 为了 move

class MyString
{
private:
    char *_data;
    size_t _length;
    size_t _capacity;

public:
    // 构造与析构
    MyString();
    MyString(const char *str);
    ~MyString();

    // 拷贝构造与移动构造
    MyString(const MyString &other);
    MyString(MyString &&other) noexcept;

    // 赋值运算符
    MyString &operator=(const MyString &other);
    MyString &operator=(MyString &&other) noexcept;

    // 常用功能
    const char *c_str() const;
    size_t size() const;
    void set_char(size_t index, char ch);

    // 运算符重载 (成员函数)
    char &operator[](size_t index);
    const char &operator[](size_t index) const;
    MyString &operator+=(const MyString &other);
};

// 运算符重载 (非成员函数声明)
MyString operator+(const MyString &lhs, const MyString &rhs);
std::ostream &operator<<(std::ostream &os, const MyString &str);
std::istream &operator>>(std::istream &is, MyString &str);
std::istream &getline(std::istream &is, MyString &str, char delim = '\n');

bool operator==(const MyString &lhs, const MyString &rhs);
bool operator!=(const MyString &lhs, const MyString &rhs);
bool operator<(const MyString &lhs, const MyString &rhs);
bool operator>(const MyString &lhs, const MyString &rhs);
bool operator<=(const MyString &lhs, const MyString &rhs);
bool operator>=(const MyString &lhs, const MyString &rhs);

#endif // MYSTRING_H