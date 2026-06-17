#include <iostream>
#include "MyList.h"
using namespace std;

void test1()
{
    zyh::list<int> ls;

    ls.push_back(1);
    ls.push_back(2);
    ls.push_back(3);

    zyh::list<int>::iterator it = ls.begin();

    cout << "zyh::list里面的数据是：";

    while (it != ls.end())
    {
        cout << *it << " ";
        ++it;
    }

    cout << endl;
}

// // 封装一个打印函数，专门用来测试我们的迭代器
// void print_list(zyh::list<int> &l)
// {
//     cout << "当前火车里的货物: ";
//     zyh::list<int>::iterator it = l.begin();
//     while (it != l.end())
//     {
//         cout << *it << " "; // 解引用拿数据
//         ++it;               // 迭代器往前走
//     }
//     cout << endl;
// }

// void test2()
// {
//     zyh::list<int> ls;

//     // 2. 测试尾插 (push_back)
//     cout << "\n[测试 1] 尾部插入 10, 20, 30:" << endl;
//     ls.push_back(10);
//     ls.push_back(20);
//     ls.push_back(30);
//     print_list(ls);

//     // 3. 测试头插 (push_front)
//     cout << "\n[测试 2] 头部插入 5:" << endl;
//     ls.push_front(5);
//     print_list(ls);

//     // 4. 测试任意位置插入 (insert)
//     cout << "\n[测试 3] 在 20 前面插入 15:" << endl;
//     zyh::list<int>::iterator it = ls.begin();
//     ++it; // 此时它指向 10
//     ++it; // 此时它指向 20
//     ls.insert(it, 15);
//     print_list(ls);

//     // 5. 测试任意位置删除 (erase)
//     cout << "\n[测试 4] 删除 10 这个元素:" << endl;
//     zyh::list<int>::iterator erase_it = ls.begin();
//     ++erase_it; // 让遥控器指向 10
//     ls.erase(erase_it);
//     print_list(ls);

//     cout << "\n================ 测试圆满结束 ================\n";
// }

// 稍微升级一下打印函数，带上链表的名字方便区分
void print_list(zyh::list<int> &l, const string &name)
{
    cout << name << " 的货物: ";
    zyh::list<int>::iterator it = l.begin();
    while (it != l.end())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
}

void test3()
{
    cout << "========== 开启深拷贝与赋值测试 ==========\n";

    // 1. 造一列 A 号链表
    zyh::list<int> list_A;
    list_A.push_back(10);
    list_A.push_back(20);
    list_A.push_back(30);
    print_list(list_A, "list_A");

    // 2. 测试拷贝构造：照着 A 造一列 B
    cout << "\n[测试 1] 拷贝构造测试 (list_B 照着 list_A 抄):" << endl;
    zyh::list<int> list_B(list_A); // 触发拷贝构造
    print_list(list_B, "list_B");

    // 验证深拷贝：修改 B 会不会影响 A？
    cout << "\n[验证深拷贝] 往 list_B 尾部加 99，往 list_A 头部加 88:" << endl;
    list_B.push_back(99);
    list_A.push_front(88);
    print_list(list_A, "list_A (预期只有88在头)");
    print_list(list_B, "list_B (预期只有99在尾)");

    // 3. 测试赋值运算符重载
    cout << "\n[测试 2] 赋值运算符测试 (造一个自带垃圾数据的 list_C):" << endl;
    zyh::list<int> list_C;
    list_C.push_back(666);
    list_C.push_back(777);
    print_list(list_C, "list_C (赋值前)");

    cout << "\n[执行覆盖] list_C = list_A;" << endl;
    list_C = list_A; // 触发 Copy-and-Swap 黑魔法！
    print_list(list_C, "list_C (赋值后)");

    cout << "\n================ 测试圆满结束 ================\n";

    // 当 return 0 执行时：
    // list_C、list_B、list_A 会依次调用我们写的 ~zyh::list() 析构函数。
    // 如果没有引发 Segmentation Fault (段错误)，说明我们的深拷贝大获全胜！
}

// 造一个结构体，用来专门测试 -> 操作符
struct Student
{
    string _name;
    int _age;

    // 构造函数，方便我们初始化装货
    Student(string name = "", int age = 0) : _name(name), _age(age)
    {
    }
};

// 专门用来测试我们的 const_iterator
void print_const_list(const zyh::list<Student> &l)
{
    cout << "[常量函数内部] 正在使用 const_iterator 打印:\n";

    // 必须用 const_iterator，否则编译器会直接报错！
    zyh::list<Student>::const_iterator it = l.begin();
    while (it != l.end())
    {
        // 🔥 见证奇迹的时刻！直接用 -> 访问结构体零件
        // 底层偷偷执行了: ( it.operator->() )->_name
        cout << "学生姓名: " << it->_name << ", 年龄: " << it->_age << endl;

        // 🧪 恶作剧测试：如果解开下面这行的注释，编译器会立刻拦截，证明 const 锁生效了！
        // it->_age = 100;

        ++it;
    }
}

void test4()
{
    cout << "========== 开启 zyh::list 终极测试 ==========\n\n";

    // 第一步：造一列普通火车，装入 3 个学生实体
    zyh::list<Student> school_bus;
    school_bus.push_back(Student("张三", 18));
    school_bus.push_back(Student("李四", 19));
    school_bus.push_back(Student("王五", 20));

    // 第二步：使用普通迭代器（可读可改）
    cout << "[测试 1] 使用普通迭代器遍历，并将李四的年龄改成 99:\n";
    zyh::list<Student>::iterator it = school_bus.begin();
    while (it != school_bus.end())
    {
        if (it->_name == "李四")
        {
            it->_age = 99; // 普通迭代器，允许修改！
        }
        cout << "学生: " << it->_name << ", 修改后年龄: " << it->_age << endl;
        ++it;
    }
    cout << "\n--------------------------------------------------\n\n";

    // 第三步：把火车送进只读打印函数（触发 const 机制）
    // 此时 school_bus 会被以 const& 的身份传进去
    print_const_list(school_bus);

    cout << "\n========== 所有核心工程全部完美通过！ ==========\n";
}

void test5()
{
    cout << "========== 开启 zyh::list 最终测试 ==========\n\n";

    zyh::list<int> my_list;

    // ---------------------------------------------------------
    // 测试 1：仪表盘测试 (empty 和 size)
    // ---------------------------------------------------------
    cout << "[测试 1]\n";
    cout << "是否为空? " << (my_list.empty() ? "是 (Empty)" : "否") << "\n";
    cout << "当前数量: " << my_list.size() << "\n\n";

    // 装入 4 节车厢
    my_list.push_back(10);
    my_list.push_back(20);
    my_list.push_back(30);
    my_list.push_back(40);

    cout << "[测试 2]\n";
    cout << "是否为空? " << (my_list.empty() ? "是" : "否 (Not Empty)") << "\n";
    cout << "当前数量: " << my_list.size() << "\n\n";

    // ---------------------------------------------------------
    // 测试 3：遍历测试 (包含后置 ++ 和 前置后置 --)
    // ---------------------------------------------------------
    cout << "[测试 3] 使用后置 it++ 顺向遍历:\n";
    zyh::list<int>::iterator it = my_list.begin();
    while (it != my_list.end())
    {
        cout << *it << " ";
        it++; // 👈 专门测试你的后置 ++
    }
    cout << "\n\n";

    cout << "[测试 4] 使用倒车档逆向遍历 (从尾开到头):\n";
    zyh::list<int>::iterator rit = my_list.end();
    rit--; // 👈 先测试后置 --，把迭代器从哨兵节点退到真实的最后一节车厢 (40)

    // 得益于我们的双向循环结构，一直倒车直到再次撞到哨兵节点(end)为止
    while (rit != my_list.end())
    {
        cout << *rit << " ";
        --rit; // 👈 专门测试你的前置 --
    }
    cout << "\n\n";

    // ---------------------------------------------------------
    // 测试 5：弹射器测试 (pop_front 和 pop_back)
    // ---------------------------------------------------------
    cout << "[测试 5] 启动弹射器:\n";

    my_list.pop_front(); // 干掉车头 (10)
    cout << "执行 pop_front() 后，头部被删，剩余大小: " << my_list.size() << "\n";

    my_list.pop_back(); // 干掉车尾 (40)
    cout << "执行 pop_back() 后，尾部被删，剩余大小: " << my_list.size() << "\n";

    cout << "现在的剩余车厢是: ";
    for (zyh::list<int>::iterator cur = my_list.begin(); cur != my_list.end(); ++cur)
    {
        cout << *cur << " "; // 应该只剩下 20 和 30
    }
    cout << "\n\n";

    cout << "========== 恭喜！所有测试完美通过！ ==========\n";
}

int main()
{
    // test1();
    // test2();
    // test3();
    // test4();
    test5();
    return 0;
}