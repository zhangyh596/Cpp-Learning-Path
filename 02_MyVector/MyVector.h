#pragma once

namespace zyh
{
    template <class T>
    class vector
    {
    public:
        typedef T *iterator;
        typedef const T *const_iterator;

    private:
        iterator _start;
        iterator _finish;
        iterator _end_of_storage; // 可用空间尾（仓库后墙）

    public:
        vector() : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
        {
        }
        // 带参构造函数：创建 n 个大小的容器，并用 value 初始化
        vector(size_t n, const T &value = T())
        {
            _start = (T *)::operator new(n * sizeof(T));

            for (size_t i = 0; i < n; ++i)
            {
                new (_start + i) T(value);
            }

            _finish = _start + n;
            _end_of_storage = _start + n;
        }

        // 析构函数
        ~vector()
        {
            if (_start != nullptr)
            {
                for (iterator it = _start; it != _finish; ++it)
                {
                    it->~T();
                }

                ::operator delete(_start);
                _start = _finish = _end_of_storage = nullptr;
            }
        }

        // 拷贝构造函数：深拷贝
        vector(const vector<T> &v)
        {
            _start = (T *)::operator new(v.capacity() * sizeof(T));

            for (size_t i = 0; i < v.size(); ++i)
            {
                new (_start + i) T(v._start[i]);
            }

            _finish = _start + v.size();
            _end_of_storage = _start + v.capacity();
        }

        // // 拷贝赋值运算符重载
        // vector<T> &operator=(const vector<T> &v)
        // {
        //     if (this != &v)
        //     {
        //         if (_start != nullptr)
        //         {
        //             for (iterator it = _start; it != _finish; ++it)
        //             {
        //                 it->~T();
        //             }

        //             ::operator delete(_start);
        //         }

        //         // 另起炉灶：根据别人的容量申请新地皮
        //         _start = (T *)::operator new(v.capacity() * sizeof(T));

        //         for (size_t i = 0; i < v.size(); ++i)
        //         {
        //             new (_start + i) T(v._start[i]);
        //         }

        //         _finish = _start + v.size();
        //         _end_of_storage = _start + v.capacity();
        //     }

        //     // 返回自己的引用，支持连续赋值 (比如 v3 = v2 = v1;)
        //     return *this;
        // }

        // 【现代级神仙写法】利用编译器和现有的拷贝构造函数
        vector<T> &operator=(vector<T> v) // 注意：这里故意【不用引用】，而是【传值】！！！
        {
            // 利用 swap 交换两者的三个门牌号指针
            swap(_start, v._start);
            swap(_finish, v._finish);
            swap(_end_of_storage, v._end_of_storage);

            return *this;
        }

        // 下标访问
        T &operator[](size_t i)
        {
            return _start[i];
        }

        const T &operator[](size_t i) const
        {
            return _start[i];
        }

        size_t size() const
        {
            return _finish - _start;
        }

        size_t capacity() const
        {
            return _end_of_storage - _start;
        }

        iterator begin()
        {
            return _start;
        }

        iterator end()
        {
            return _finish;
        }

        // 请求开辟新容量
        void reserve(size_t n)
        {
            if (n > capacity())
            {
                // 【工业级规范】只申请裸内存，不调用任何 T 的构造函数！
                T *tmp = (T *)::operator new(n * sizeof(T));
                // 提前记下旧仓库里有多少件快递（极其关键！因为等下 _start 换成新仓库后，就没法用旧距离算了）
                size_t old_size = size();

                if (_start != nullptr)
                {
                    for (size_t i = 0; i < old_size; ++i)
                    {
                        tmp[i] = _start[i];
                        // 【工业级规范】旧仓库的快递搬走了，必须手动调用析构函数把它销毁
                        _start[i].~T();
                    }

                    // 【工业级规范】因为是裸内存，退租时必须用 ::operator delete
                    ::operator delete(_start);
                }

                _start = tmp;
                _finish = _start + old_size;
                _end_of_storage = _start + n;
            }
        }

        // 尾部插入新元素
        void push_back(const T &x)
        {
            // 检查仓库是不是满了 (当前结尾已经顶到了可用空间尾)
            if (_finish == _end_of_storage)
            {
                size_t new_capacity = capacity() == 0 ? 4 : capacity() * 2;
                reserve(new_capacity);
            }

            new (_finish) T(x); // 含义：就在 _finish 这个地址上，调用 T 的拷贝构造函数，原地生出一个新对象
            ++_finish;
        }

        // 任意位置插入
        iterator insert(iterator pos, const T &x)
        {
            if (_finish == _end_of_storage)
            {
                // 搬家前，先算好 pos 距离 _start 的偏移量
                size_t offset = pos - _start;

                size_t new_capacity = capacity() == 0 ? 4 : capacity() * 2;
                reserve(new_capacity);

                // 搬家后，刷新 pos，让它指向新地皮上的正确位置！
                pos = _start + offset;
            }

            // 挪动数据：把 pos 及它后面的元素全部往后挪一格
            iterator end_it = _finish - 1;
            while (end_it >= pos)
            {
                // 注意：这里最严谨的做法是判断是不是纯裸内存。
                // 为了简单说明逻辑，暂且先用 placement new 和赋值来处理
                if (end_it == _finish - 1)
                {
                    new (end_it + 1) T(*end_it);
                }
                else
                {
                    *(end_it + 1) = *end_it;
                }
                --end_it;
            }
            *pos = x;
            ++_finish;

            return pos;
        }

        // 任意位置删除
        iterator erase(iterator pos)
        {
            if (pos >= _start && pos < _finish)
            {
                // 挪动数据：从 pos 的下一个位置开始，全部往前挪一格
                iterator it = pos + 1;
                while (it != _finish)
                {
                    *(it - 1) = *it;
                    ++it;
                }

                --_finish;

                _finish->~T();
            }
            // C++ 官方标准规定：erase 必须返回被删除元素的【下一个元素】的新位置
            // 因为后面的元素全往前挪了，所以原本的 pos 指向的正好就是新的下一个元素
            return pos;
        }

        // 尾删函数
        void pop_back()
        {
            if (_start != _finish)
            {
                erase(_finish - 1);
            }
        }

        // 清空所有元素
        void clear()
        {
            while (_start != _finish)
            {
                --_finish;
                _finish->~T();
            }
        }

        // 调整有效元素个数
        void resize(size_t n, const T &val = T())
        {
            if (n < size())
            {
                // 情况 1：缩小。多出来的元素我们要让它们“安乐死”
                while (size() > n)
                {
                    --_finish;
                    _finish->~T();
                }
            }
            else if (n > size())
            {
                // 情况 2：放大。先看地皮够不够
                if (n > capacity())
                {
                    reserve(n);
                }

                while (size() < n)
                {
                    push_back(val);
                }
            }
        }

        // 判断容器是否为空
        bool empty() const
        {
            return _start == _finish;
        }
    };
}