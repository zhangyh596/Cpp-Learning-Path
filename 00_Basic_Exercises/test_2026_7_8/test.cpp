#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

/* ===== 类声明 ===== */
class Course
{
private:
    int score;
    int credit;

public:
    Course(int s = 0, int c = 0);
    double getGPA() const;
    int getCredit() const;
};

class Student
{
private:
    vector<Course> courses;

public:
    void addCourse(const Course &c);
    double calcGPA() const;
    int CourseNum() const;
};

Course::Course(int s, int c)
{
    score = s;
    credit = c;
}

double Course::getGPA() const
{
    if (score >= 90)
    {
        return 4.0;
    }
    else
    {
        return (4.0) * (score / 90.0);
    }
}

int Course::getCredit() const
{
    return credit;
}

void Student::addCourse(const Course &c)
{
    courses.push_back(c);
}

double Student::calcGPA() const
{
    double sum_s = 0;
    double sum_c = 0;
    for (size_t i = 0; i < courses.size(); ++i)
    {
        sum_s += courses[i].getGPA() * courses[i].getCredit();
        sum_c += courses[i].getCredit();
    }
    return sum_s / sum_c;
}

int Student::CourseNum() const
{
    return courses.size();
}

int main()
{
    Student stu;
    int score, credit, Cnum;
    cin >> Cnum;
    for (int i = 0; i < Cnum; i++)
    {
        cin >> score >> credit;
        stu.addCourse(Course(score, credit));
    }
    cout << fixed << setprecision(2);
    cout << "Total course num: " << stu.CourseNum() << endl;
    cout << "GPA: " << stu.calcGPA() << endl;

    return 0;
}
