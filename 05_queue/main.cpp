#include <iostream>
#include "queue.h"

void test1()
{
    zyh::queue<std::string> q;
    q.push("张三");
    q.push("李四");
    q.push("王五");

    std::cout << "队头是: " << q.front() << ", 队尾是: " << q.back() << std::endl;

    std::cout << "队列弹出顺序: ";
    while (!q.empty())
    {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
}

int main()
{
    test1();
    return 0;
}