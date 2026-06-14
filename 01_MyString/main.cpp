#include "MyString.h"

using namespace std;

void test1()
{
    MyString s1;
    cout << s1.c_str() << endl;

    MyString s2("hello c++");
    cout << s2.c_str() << endl;
}

void test2()
{
    MyString s1("hello");
    cout << s1.c_str() << endl;

    MyString s2 = s1;
    cout << s2.c_str() << endl;

    s2.set_char(0, 'B');
    cout << "修改后s2为：" << s2.c_str() << endl;
}

void test3_1()
{
    MyString s1("Apple");
    MyString s2("Banana");
    MyString s3("Orange");

    cout << "赋值前:" << endl;
    cout << "s1: " << s1.c_str() << ", s2: " << s2.c_str() << ", s3: " << s3.c_str() << endl;

    // 测试点 1：连续赋值 (s3 = s2 = s1)
    s3 = s2 = s1;

    cout << "\n连续赋值后:" << endl;
    cout << "s1: " << s1.c_str() << ", s2: " << s2.c_str() << ", s3: " << s3.c_str() << endl;

    // 测试点 2：修改 s2，看看 s1 和 s3 会不会被影响（验证深拷贝）
    s2.set_char(0, 'G'); // 把 s2 改成 "Gpple"

    cout << "\n修改 s2 后的独立性测试:" << endl;
    cout << "s1 (应该还是 Apple): " << s1.c_str() << endl;
    cout << "s2 (应该变成了 Gpple): " << s2.c_str() << endl;
    cout << "s3 (应该还是 Apple): " << s3.c_str() << endl;

    // 测试点 3：自我赋值测试，确保不崩溃
    s1 = s1;
    cout << "\n自我赋值后 s1 依然完好: " << s1.c_str() << endl;
}

void test3_2()
{
    MyString s1("very long string");
    cout << "s1初始内容：" << s1.c_str() << endl;

    MyString s2 = move(s1);

    cout << "移动后" << endl;
    cout << "s2的内容：" << s2.c_str() << endl;
    cout << "s1的内容：" << s1.c_str() << endl;
}

void print_first_char(const MyString &str)
{
    if (str.size() > 0)
    {
        cout << "函数内部读取的首字母: " << str[0] << endl;
    }
}

void test4()
{
    MyString s1("hello");
    cout << "初始内容：" << s1.c_str() << endl;

    s1[0] = 'H';
    cout << "修改s1[0]后：" << s1.c_str() << endl;

    for (size_t i = 0; i < s1.size(); ++i)
    {
        cout << s1[i] << " ";
    }
    cout << endl;

    print_first_char(s1);
}

void test5()
{
    MyString s1("hello");
    MyString s2(" world");

    cout << "测试 + 号" << endl;

    MyString s3 = s1 + s2;

    cout << s1.c_str() << endl;
    cout << s2.c_str() << endl;
    cout << s3.c_str() << endl;

    cout << "测试 += 号" << endl;
    s1 += s2;
    cout << s1.c_str() << endl;
}

void test6()
{
    MyString s1("hello");
    MyString s2("C++");
    MyString s3("world");

    cout << s1 << " " << s2 << " " << s3 << endl;
}

void test7()
{
    MyString s1("apple");
    MyString s2("banana");
    MyString s3("apple");

    cout << (s1 == s3 ? "Yes" : "No") << endl;
    cout << (s1 != s2 ? "Yes" : "No") << endl;
}

void test8()
{
    MyString s1;
    MyString s2;

    cout << "========= 测试 cin >> =========" << endl;
    cout << "请输入两个单词（用空格隔开）: ";
    cin >> s1 >> s2;
    cout << "读取到的单词 1: " << s1 << endl;
    cout << "读取到的单词 2: " << s2 << endl;

    // 吸收掉残留的回车符，防止影响接下来的 getline
    char flush_char;
    cin.get(flush_char);

    cout << "\n========= 测试 getline =========" << endl;
    cout << "请输入一整行带空格的句子: ";
    getline(cin, s1);
    cout << "读取到的整行内容为: " << s1 << endl;
}

int main()
{
    cout << "--- 测试 ---" << endl;
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    // test6();
    // test7();
    test8();
    return 0;
}