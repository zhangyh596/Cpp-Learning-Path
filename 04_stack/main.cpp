#include <iostream>
#include "stack.h"

void test1()
{
    zyh::stack<int> s;

    // 压栈操作
    s.push(10);
    s.push(20);
    s.push(30);

    std::cout << "Top element is: " << s.top() << std::endl;

    std::cout << "Stack size is: " << s.size() << std::endl;

    s.pop(); // 弹出一个元素

    std::cout << "Top element after one pop is: " << s.top() << std::endl;

    // 循环清空栈
    while (!s.empty())
    {
        s.pop();
    }
}

int main()
{
    test1();
    return 0;
}