#pragma once

#include "school.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std; //名字空间

#define CLASS Management<STUDENT>
#define GRADE Management<Management<STUDENT>>
#define SPECIALITY Management<Management<Management<STUDENT>>>

class Undergraduate;

class Postgradute;

/*********************************************************************************/
/*******************************学生类********************************************/
/*********************************************************************************/

//学生类
template<class STUDENT>
class Student
{
protected:
    string name;                                     //名字
    string sex;                                      //性别
    long id;                                         //学号
    int totalscore;                                  //总成绩
    typename list<CLASS >::iterator pClass;           //班级指针
    typename list<GRADE>::iterator pGrade;           //年级指针
    typename list<SPECIALITY >::iterator pSpeciality; //专业指针
public:
    Student(long id = -1, string name = "", string sex = ""); //学生构造函数
    void input(void);                               //输入基本信息的函数
    void basePut(void);                             //输出基本信息
    void elsePut(void);                             //输出排名信息
    long getId(void);                               //获取学号
    string getSex(void);                            //获取性别
    string getName(void);                           //获取姓名
    int getTotalscore(void);                        //获取总成绩
    typename list<CLASS >::iterator &getClass(void); //获取班级指针变量
    typename list<GRADE>::iterator &getGrade(void); //获取班级指针变量
    typename list<SPECIALITY >::iterator &getSpeciality(void); //获取班级指针变量
    void setName(void);                                       //改变姓名
    void setSex(void);                                        //改变性别
    ifstream &load(ifstream &in);                             //储存基本信息
    virtual void setScore(int s1, int s2, int s3 = -1) = 0; //设置成绩的纯虚函数
    virtual int getSubject(void) = 0;                       //选择科目名
    virtual void changeScore(void) = 0;                     //改变分数
    virtual bool fail(int i) = 0; //检查科目是否及格
    static long maxId;
};

template<class STUDENT>
string Student<STUDENT>::getSex() { return this->sex; }

template<class STUDENT>
ifstream &Student<STUDENT>::load(ifstream &in)
{
    in >> this->id;
    in >> this->name;
    in >> this->sex;
    in >> this->totalscore;

    return in;
}

template<class STUDENT>
int Student<STUDENT>::getTotalscore()
{
    return this->totalscore;
}

template<class STUDENT>
void Student<STUDENT>::input(void)
{
    cout << "基本信息" << endl;

    cout << "姓名：";
    cin >> this->name;

    cout << "性别: ";
    cin >> this->sex;
}

template<class STUDENT>
Student<STUDENT>::Student(long id, string name, string sex)
{
    //初始化各种数据
    this->name = name;
    this->sex = sex;
    this->id = id;
    this->totalscore = -1;
}

template<class STUDENT>
void Student<STUDENT>::basePut(void)
{
    cout << setw(5) << left << this->id;
    cout << setw(12) << left << this->name;
    cout << setw(8) << left << this->sex;
    cout << setw(15) << left << this->pClass->getName();
    cout << setw(15) << left << this->pGrade->getName();
    cout << setw(15) << left << this->pSpeciality->getName();
}

template<class STUDENT>
void Student<STUDENT>::elsePut(void)
{
    cout << setw(8) << this->totalscore << endl;
}

template<class STUDENT>
long Student<STUDENT>::getId(void) { return this->id; }

template<class STUDENT>
string Student<STUDENT>::getName(void)
{
    return this->name;
}

template<class STUDENT>
typename list<CLASS >::iterator &Student<STUDENT>::getClass()
{
    return this->pClass;
}

template<class STUDENT>
typename list<GRADE>::iterator &Student<STUDENT>::getGrade()
{
    return this->pGrade;
}

template<class STUDENT>
typename list<SPECIALITY >::iterator &Student<STUDENT>::getSpeciality()
{
    return this->pSpeciality;
}

template<class STUDENT>
void Student<STUDENT>::setName(void)
{
    cout << "姓名：";
    cin >> this->name;
}

template<class STUDENT>
void Student<STUDENT>::setSex(void)
{
    cout << "性别：";
    cin >> this->sex;
}

/*********************************************************************************/
/*******************************本科生类********************************************/
/*********************************************************************************/

class Undergraduate : public Student<Undergraduate>
{
private:
    int math;      //高数成绩
    int english;   //英语成绩
    int clanguage; // C语言成绩
public:
    //本科生构造函数
    Undergraduate(long id = -1, string name = "", string sex = "")
            : Student(id, name, sex) {}

    void setScore(int s1, int s2, int s3 = -1); //设置成绩的函数
    void setScore(void);

    void changeScore(void);        //改变分数
    void setMath(void);            //设置数学
    void setEnglish(void);        //设置英语
    void setClanguage(void);    //设置Ｃ语言
    int getSubject(void);        //选择科目名
    int getSubject(int subject);//返回相应的科目成绩
    bool fail(int i);            //检查科目是否及格
    friend ostream &operator<<(ostream &out, Undergraduate &und);   //输出重载
    friend istream &operator>>(istream &in, Undergraduate &und);    //输出重载
    friend ofstream &operator<<(ofstream &out, Undergraduate &und); //输出重载
    friend ifstream &operator>>(ifstream &in, Undergraduate &und);  //输出重载
};

/*********************************************************************************/
/*******************************研究生类********************************************/
/*********************************************************************************/
class Postgradute : public Student<Postgradute>
{
private:
    int comprehensive; //课程综合
    int thesis;        //毕业论文
public:
    //研究生构造函数
    Postgradute(long id = -1, string name = "", string sex = "")
            : Student(id, name, sex) {}

    void setScore(int s1, int s2, int s3 = -1); //设置成绩的函数
    void setScore(void);

    void changeScore(void);      //改变分数
    void setComprehensive(void); //设置课程综合
    void setThesis(void);        //设置毕业论文
    int getSubject(void);        //选择科目名
    int getSubject(int subject); //获取相应科目
    bool fail(int i);            //检查科目是否及格
    friend ostream &operator<<(ostream &out, Postgradute &pos);   //输出重载
    friend istream &operator>>(istream &in, Postgradute &pos);    //输出重载
    friend ofstream &operator<<(ofstream &out, Postgradute &pos); //输出重载
    friend ifstream &operator>>(ifstream &in, Postgradute &pos);  //输出重载
};

template<class STUDENT> long Student<STUDENT>::maxId = 0;