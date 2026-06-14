#include <iostream>
#include <string>
#include "MyVector.h"
using namespace zyh;
using namespace std;

void test1()
{
    vector<int> v;
    // 阶段 1：初始状态
    cout << "--- 阶段 1 ---" << endl;
    cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << endl;

    // 阶段 2：连续插入 4 个元素
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    cout << "--- 阶段 2 ---" << endl;
    cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << endl;

    // 阶段 3：插入第 5 个元素（触发扩容！）
    v.push_back(50);
    cout << "--- 阶段 3 ---" << endl;
    cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << endl;

    // 阶段 4：遍历打印
    cout << "--- 阶段 4 元素内容 ---" << endl;
    // 利用我们刚学过的：iterator 就是原生指针，直接用它来遍历！
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void test2()
{
    cout << "=== 阶段 1：构建 v1 ===" << endl;
    // 创建一个装了 3 个 "Hello" 的容器
    vector<string> v1(3, "Hello");

    cout << "=== 阶段 2：触发深拷贝构建 v2 ===" << endl;
    // 这里会精准调用你刚刚手写的【拷贝构造函数】！
    vector<string> v2(v1);

    cout << "=== 阶段 3：验证物理隔离 ===" << endl;
    // 给 v2 单独尾插一个新字符串，看看会不会影响 v1
    v2.push_back("World");

    // 打印 v1
    cout << "v1 (size: " << v1.size() << ") 元素: ";
    for (vector<string>::iterator it = v1.begin(); it != v1.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    // 打印 v2
    cout << "v2 (size: " << v2.size() << ") 元素: ";
    for (vector<string>::iterator it = v2.begin(); it != v2.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "=== 阶段 4：程序结束，见证奇迹 ===" << endl;
    // v2 会先调用析构函数，销毁自己的地皮和字符串。
    // v1 会后调用析构函数，销毁自己的地皮和字符串。
    // 因为你写了深拷贝，这里绝对不会出现 Double Free（段错误）！程序将完美退出。
}

void test3()
{
    cout << "=== 阶段 1：准备测试数据 ===" << endl;
    // v1 是我们要被抄袭的“原件”
    vector<string> v1(2, "Apple");

    // v3 是一个“老油条”，里面已经占用了地皮，存了 3 个 "Banana"
    vector<string> v3(3, "Banana");

    cout << "=== 阶段 2：触发赋值运算符 ===" << endl;
    // 关键时刻！这里会触发 operator=
    // v3 必须先销毁自己的 3 个 "Banana"，退掉旧地皮，再去深拷贝 v1 的 2 个 "Apple"
    v3 = v1;

    cout << "=== 阶段 3：测试连续赋值 (Chain Assignment) ===" << endl;
    vector<string> v4;
    // 这里先执行 v3 = v1，然后返回 v3 的引用，再执行 v4 = v3
    v4 = v3 = v1;

    cout << "=== 阶段 4：验证物理隔离 ===" << endl;
    // 我们往 v3 里加点新东西，看看 v1 和 v4 会不会跟着变
    v3.push_back("Orange");

    // --- 打印结果 ---
    cout << "v1 (size: " << v1.size() << ") 元素: ";
    for (vector<string>::iterator it = v1.begin(); it != v1.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "v3 (size: " << v3.size() << ") 元素: ";
    for (vector<string>::iterator it = v3.begin(); it != v3.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "v4 (size: " << v4.size() << ") 元素: ";
    for (vector<string>::iterator it = v4.begin(); it != v4.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "=== 阶段 5：程序结束，见证奇迹 ===" << endl;
    // 程序退出时，v4, v3, v1 将依次调用析构函数。
    // 如果没有段错误（Core Dump），说明我们不仅没有 Double Free，也没有内存泄漏！
}

void test4()
{
    cout << "=== 阶段 1：测试 push_back 和 operator[] ===" << endl;
    vector<string> v;

    // 连续放入 4 个元素，假设此时容量刚好达到了 4
    v.push_back("A");
    v.push_back("B");
    v.push_back("C");
    v.push_back("D");

    cout << "原始元素: ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " "; // 测试 operator[]
    }
    cout << endl
         << endl;

    cout << "=== 阶段 2：触发致命危机 (扩容 + 插入) ===" << endl;
    // 此时 v 的 size 是 4，capacity 也是 4，仓库已满！
    // 我们获取一个指向第二个元素 "B" 的迭代器（此时它指向旧地皮）
    vector<string>::iterator it = v.begin() + 1;

    cout << "准备在 'B' 的位置前面插入一个 'X'..." << endl;
    // 关键时刻！
    // insert 内部发现满载，会调用 reserve 申请新地皮并销毁旧地皮。
    // 如果没有我们的 offset 修复逻辑，这里继续使用 it 就会直接发生段错误崩溃！
    v.insert(it, "X");
    cout << "插入成功！没有发生崩溃！\n\n";

    cout << "=== 阶段 3：验证挪动结果 ===" << endl;
    cout << "插入后 vector 大小: " << v.size() << "，容量: " << v.capacity() << endl;
    cout << "最终元素: ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << "\n";
}

void test5()
{
    vector<string> v;
    v.push_back("Apple");
    v.push_back("Banana");
    v.push_back("Cherry");
    v.push_back("Date");

    cout << "=== 阶段 1：原始数据 ===" << endl;
    cout << "v (size: " << v.size() << ") 元素: ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << "\n\n";

    cout << "=== 阶段 2：测试 erase (删除 Banana) ===" << endl;
    // 获取指向 "Banana" 的迭代器 (begin + 1)
    vector<string>::iterator it = v.begin() + 1;

    // 删除它，并接收返回的新迭代器
    it = v.erase(it);

    cout << "删除后 v (size: " << v.size() << ") 元素: ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << "\n";
    // 验证返回值是不是指向了原本 Banana 后面的 Cherry
    cout << "erase 返回的迭代器现在指向: " << *it << "\n\n";

    cout << "=== 阶段 3：测试 pop_back 和 clear ===" << endl;
    v.pop_back(); // 删掉 Date
    cout << "pop_back 后元素: ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << "\n";

    v.clear(); // 全部清空
    cout << "clear 后，size: " << v.size() << "，capacity: " << v.capacity() << endl;
}

void test6()
{
    vector<string> v;

    cout << "=== 阶段 1：测试 empty ===" << endl;
    if (v.empty())
    {
        cout << "刚初始化的 vector 是空的！(验证成功)\n\n";
    }

    cout << "=== 阶段 2：填入初始数据 ===" << endl;
    v.push_back("Apple");
    v.push_back("Banana");
    cout << "当前 size: " << v.size() << "，capacity: " << v.capacity() << endl;
    cout << "元素: ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << "\n\n";

    cout << "=== 阶段 3：测试 resize 放大 (带默认参数) ===" << endl;
    // 原本只有 2 个元素，要求扩到 5 个。会补充 3 个 "Hello"
    v.resize(5, "Hello");
    cout << "resize(5, 'Hello') 之后 size: " << v.size() << "，capacity: " << v.capacity() << endl;
    cout << "元素: ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << "\n\n";

    cout << "=== 阶段 4：测试 resize 缩小 ===" << endl;
    // 从 5 个缩减到 1 个。尾部的 4 个元素必须被执行析构函数（安乐死）
    v.resize(1);
    cout << "resize(1) 之后 size: " << v.size() << "，capacity: " << v.capacity() << endl;
    cout << "元素: ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << "\n\n";

    cout << "=== 阶段 5：清理门户 ===" << endl;
    v.clear();
    cout << "clear() 之后，empty() 返回: " << (v.empty() ? "true" : "false") << endl;
    cout << "此时 capacity (地皮) 依然是: " << v.capacity() << endl;
}

int main()
{
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    test6();
    return 0;
}