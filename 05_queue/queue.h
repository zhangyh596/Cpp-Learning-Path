#pragma once

#include <list>
#include <stddef.h>

namespace zyh
{
    template <typename T, typename Container = std::list<T>>
    class queue
    {
    private:
        Container c; // 底层容器

    public:
        // 入队
        void push(const T &value)
        {
            c.push_back(value);
        }

        // 出队
        void pop()
        {
            c.pop_front();
        }

        // 获取队头元素
        T &front()
        {
            return c.front();
        }

        // const版本获取队头元素
        const T &front() const
        {
            return c.front();
        }

        // 获取队尾元素
        T &back()
        {
            return c.back();
        }

        // const版本获取队尾元素
        const T &back() const
        {
            return c.back();
        }

        // 判断是否为空
        bool empty() const
        {
            return c.empty();
        }

        size_t size() const
        {
            return c.size();
        }
    };
}