#pragma once

#include <vector>
#include <stddef.h>

namespace zyh
{
    template <typename T, typename Container = std::vector<T>>
    class stack
    {
    private:
        Container c; // 底层容器

    public:
        // 入栈
        void push(const T &value)
        {
            c.push_back(value);
        }

        // 出栈
        void pop()
        {
            c.pop_back();
        }

        // 获取栈顶元素
        T &top()
        {
            return c.back();
        }

        // const版本获取栈顶元素
        const T &top() const
        {
            return c.back();
        }

        // 判断是否为空
        bool empty() const
        {
            return c.empty();
        }

        // 获取大小
        size_t size() const
        {
            return c.size();
        }
    };
}