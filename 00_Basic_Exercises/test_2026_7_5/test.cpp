#include <iostream>
#include <cstring>
using namespace std;

class CPerson
{
public:
    CPerson(char *s)
    {
        name = new char[strlen(s) + 1];
        strcpy(name, s);
    }
    void Print()
    {
        cout << "name:" << name << endl;
    }

protected:
    char *name;
};

class CStudent : virtual public CPerson
{
private:
    char *grade;

public:
    CStudent(char *s1, const char *s2) : CPerson(s1)
    {
        grade = new char[strlen(s2) + 1];
        strcpy(grade, s2);
    }
    void Print()
    {
        CPerson::Print();
        cout << "grade:" << grade << endl;
    }
};

class CTeacher : virtual public CPerson
{
private:
    char *lesson;

public:
    CTeacher(char *s1, const char *s2) : CPerson(s1)
    {
        lesson = new char[strlen(s2) + 1];
        strcpy(lesson, s2);
    }
    void Print()
    {
        CPerson::Print();
        cout << "lesson:" << lesson << endl;
    }
};

class CStudentTeacher : public CStudent, public CTeacher
{
private:
    char *major;

public:
    CStudentTeacher(char *s1, const char *s2, const char *s3, const char *s4)
        : CPerson(s1), CStudent(s1, s2), CTeacher(s1, s3)
    {
        major = new char[strlen(s4) + 1];
        strcpy(major, s4);
    }
    void Print()
    {
        CStudent::Print();
        cout << "Major:" << major << endl;
    }
};

int main()
{
    char sname[10], tname[10], stname[10];
    cin >> sname >> tname >> stname;
    CStudent stu(sname, "16");
    CTeacher tea(tname, "math");
    CStudentTeacher stutea(stname, "17", "ds", "computer");
    stu.Print();
    tea.Print();
    stutea.Print();
    return 0;
}