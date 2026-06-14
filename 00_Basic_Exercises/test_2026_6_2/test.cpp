// #include <iostream>
// using namespace std;

// int main()
// {
//     std::string s = "hello bit!!!";

//     // 删掉中间的 "bit"
//     // s.begin()+5 指向 'b'，s.begin()+8 指向 '!'（不包含它本身）
//     s.erase(s.begin() + 5, s.begin() + 9);
//     // 现在的 s 变成 "hello!!!"

//     cout << s << endl;

//     // // 1. 从索引 6 开始，截取长度为 3 的子串
//     // std::string sub1 = s.substr(6, 3);
//     // // 包含索引：6(b), 7(i), 8(t) -> 结果完全正确："bit"

//     // // 2. 从索引 9 开始，不传第二个参数（默认到末尾）
//     // std::string sub2 = s.substr(9);
//     // // 包含索引：9(!), 10(!), 11(!) -> 结果完全正确："!!!"

//     // cout << s << endl;
//     // cout << sub1 << endl;
//     // cout << sub2 << endl;
//     return 0;
// }

#include <iostream>

namespace zyh
{
    class string
    {
    public:
    private:
        char *_str;
    };
}