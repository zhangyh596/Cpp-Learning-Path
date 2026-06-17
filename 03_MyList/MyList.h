#ifndef MY_STL_LIST_HPP
#define MY_STL_LIST_HPP

#include <cstddef>

namespace zyh
{
    template <typename T>
    struct __list_node
    {
        __list_node<T> *_next;
        __list_node<T> *_prev;
        T _data;
    };

    // 普通迭代器
    template <typename T, typename Ref, typename Ptr>
    struct __list_iterator
    {
        typedef __list_node<T> *link_type;
        typedef __list_iterator<T, Ref, Ptr> self;

        link_type _node; // 迭代器的芯片，指向节点

        __list_iterator() : _node(nullptr)
        {
        }

        __list_iterator(link_type x) : _node(x)
        {
        }

        // 普通迭代器的解引用：返回货物的引用
        Ref operator*()
        {
            return _node->_data;
        }

        // 重载箭头操作符
        Ptr operator->()
        {
            return &(_node->_data);
        }
        // 当比如_data是一个自定义的结构体(例如Student)
        // 手写的 operator-> 函数，必须返回一个“原生的指针（内存地址）”
        // 然后，编译器会自动、强行、在后面再补上一个箭头
        // !!! 写下it->age相当于(it.operator->())->age

        // 前置 ++ 操作符：返回迭代器自己的引用
        self &operator++()
        {
            _node = _node->_next;
            return *this;
        }

        // 前置 -- 操作符
        self &operator--()
        {
            _node = _node->_prev;
            return *this;
        }

        // 后置 ++ 操作符
        self operator++(int)
        {
            self tmp(*this);
            _node = _node->_next;
            return tmp;
        }

        // 后置 -- 操作符
        self operator--(int)
        {
            self tmp(*this);
            _node = _node->_prev;
            return tmp;
        }

        // 判断两个迭代器是否指向的节点不一样
        bool operator!=(const self &__x) const
        {
            return _node != __x._node;
        }
    };

    template <typename T>
    class list
    {
    public:
        typedef __list_iterator<T, T &, T *> iterator;
        typedef __list_iterator<T, const T &, const T *> const_iterator;

        typedef __list_node<T> *link_type;

    private:
        link_type _head; // 哨兵节点
        size_t _size;

    public:
        // 构造函数
        list()
        {
            _size = 0;
            _head = new __list_node<T>();

            _head->_next = _head;
            _head->_prev = _head;
        }

        // 拷贝构造函数
        list(list<T> &other)
        {
            _head = new __list_node<T>();
            _head->_next = _head;
            _head->_prev = _head;

            // 拿出迭代器，从头到尾遍历另一个链表
            iterator it = other.begin();
            while (it != other.end())
            {
                push_back(*it);
                ++it;
            }
        }

        void swap(list<T> &other)
        {
            std::swap(_head, other._head);
        }

        // 赋值运算符重载（现代写法：Copy-and-Swap（拷贝并交换））
        list<T> &operator=(list<T> other) // 这里没有用 &，故意用“值传递”！
        {
            swap(other);

            return *this;
        }

        // // 尾插函数
        // void push_back(const T &x)
        // {
        //     link_type new_node = new __list_node<T>();
        //     new_node->_data = x;

        //     link_type tail = _head->_prev;

        //     new_node->_next = _head;
        //     new_node->_prev = tail;

        //     tail->_next = new_node;
        //     _head->_prev = new_node;
        // }

        // 返回指向第一个真实货物的迭代器
        iterator begin()
        {
            return iterator(_head->_next);
        }

        // 只读版本
        const_iterator begin() const
        {
            return _head->_next;
        }

        // 返回指向终点（哨兵节点）的迭代器
        iterator end()
        {
            return iterator(_head);
        }

        // 只读版本
        const_iterator end() const
        {
            return _head;
        }

        // 在指定的位置前面插入一个节点
        iterator insert(iterator pos, const T &x)
        {
            link_type curr = pos._node;

            link_type prev = curr->_prev;

            link_type new_node = new __list_node<T>();
            new_node->_data = x;

            new_node->_next = curr;
            new_node->_prev = prev;

            prev->_next = new_node;
            curr->_prev = new_node;

            ++_size;

            // 回指向新节点的迭代器
            return iterator(new_node);
        }

        // 更改之前的尾插函数，复用insert函数
        void push_back(const T &x)
        {
            insert(end(), x);
        }

        // 头插函数，复用insert
        void push_front(const T &x)
        {
            insert(begin(), x);
        }

        // 任意位置删除，并返回下一个节点的迭代器
        iterator erase(iterator pos)
        {
            link_type curr = pos._node;

            link_type prev = curr->_prev;
            link_type next = curr->_next;

            prev->_next = next;
            next->_prev = prev;

            delete curr;

            --_size;

            return iterator(next);
        }

        // 清空所有真实节点（保留哨兵节点）
        void clear()
        {
            iterator it = begin();

            while (it != end())
            {
                // erase 会把当前车厢砸掉，并把下一个车厢的遥控器交给我们，我们直接接住！
                it = erase(it);
            }
        }

        // 辅助函数：判断链表是否为空
        bool empty() const
        {
            return _head->_next == _head;
        }

        // 头删
        void pop_front()
        {
            erase(begin());
        }

        // 尾删
        void pop_back()
        {
            // 要删最后一个，就是 end() 的前一个
            erase(--end());
        }

        size_t size() const
        {
            return _size;
        }

        ~list()
        {
            clear();

            delete _head;
            _head = nullptr;
        }
    };
}

#endif // MY_STL_LIST_HPP