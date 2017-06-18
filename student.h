#pragma once

#include <iostream> //要重载输入输出
#include <string>   //字符串类头文件
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include "school.h"

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
    string name;    //名字
    string sex;     //性别
    long id;        //学号
    int totalscore; //总成绩
    int classrank;  //班级排名
    int schoolrank; //校级排名
    typename list<CLASS >::iterator pClass;//班级指针
    typename list<GRADE>::iterator pGrade;//年级指针
    typename list<SPECIALITY >::iterator pSpeciality;//专业指针
public:
    Student(long id = -1, string name = "", string sex = ""); //学生构造函数
    void input(void);          //输入基本信息的函数
    void basePut(void);        //输出基本信息
    void elsePut(void);        //输出排名信息
    long getId(void);          //获取学号
    string getSex(void);

    string getName(void);      //获取姓名
    int getTotalscore(void);          //获取总成绩
    int getClassrank(void);          //获取班级排名
    int getSchoolrank(void);          //获取校级排名
    typename list<CLASS >::iterator &getClass(void);//获取班级指针变量
    typename list<GRADE>::iterator &getGrade(void);//获取班级指针变量
    typename list<SPECIALITY >::iterator &getSpeciality(void);//获取班级指针变量
    void setName(void); //改变姓名
    void setSex(void);   //改变性别
    ifstream &load(ifstream &in);

    virtual void setScore(int s1, int s2, int s3 = -1) = 0; //设置成绩的纯虚函数
    virtual int getSubject(void) = 0; //选择科目名
    virtual void changeScore(void) = 0;//改变分数
    virtual bool fail(int i) = 0; //检查科目是否及格
};

template<class STUDENT>
string Student<STUDENT>::getSex()
{
    return this->sex;
}

template<class STUDENT>
ifstream &Student<STUDENT>::load(ifstream &in)
{
    in >> this->id;
    in >> this->name;
    in >> this->sex;
    in >> this->totalscore;
    in >> this->classrank;
    in >> this->schoolrank;

    return in;
}

template<class STUDENT>
int Student<STUDENT>::getTotalscore()
{
    return this->totalscore;
}

template<class STUDENT>
int Student<STUDENT>::getClassrank()
{
    return this->classrank;
}

template<class STUDENT>
int Student<STUDENT>::getSchoolrank()
{
    return this->schoolrank;
}

//输入基本信息的函数
template<class STUDENT>
void Student<STUDENT>::input(void)
{
    cout << "基本信息" << endl;

    cout << "姓名：";
    cin >> this->name;

    cout << "性别: ";
    cin >> this->sex;
}

//学生构造函数
template<class STUDENT>
Student<STUDENT>::Student(long id, string name, string sex)
{
    //初始化各种数据
    this->name = name;
    this->sex = sex;
    this->id = id;
    this->totalscore = -1;
    this->classrank = -1;
    this->schoolrank = -1;
}

//基本信息输出函数
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

//其他输出函数
template<class STUDENT>
void Student<STUDENT>::elsePut(void)
{
    cout << setw(8) << this->totalscore;

    if (this->classrank != -1)
    {
        cout << setw(8) << this->classrank;
        cout << setw(8) << this->schoolrank << endl;
    } else
    {
        cout << setw(8) << "待统计";
        cout << setw(8) << "待统计" << endl;
    }
}

//获取学号函数
template<class STUDENT>
long Student<STUDENT>::getId(void)
{
    return this->id;
}

//获取姓名
template<class STUDENT>
string Student<STUDENT>::getName(void)
{
    return this->name;
}

//获取班级
template<class STUDENT>
typename list<CLASS >::iterator &Student<STUDENT>::getClass()
{
    return this->pClass;
}

//获取年级
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

//改变姓名函数
template<class STUDENT>
void Student<STUDENT>::setName(void)
{
    cout << "姓名：";
    cin >> this->name;
}

//改变性
template<class STUDENT>
void Student<STUDENT>::setSex(void)
{
    cout << "性别：";
    cin >> this->sex;
}


/*********************************************************************************/
/*******************************学生类********************************************/
/*********************************************************************************/
//本科生类
class Undergraduate : public Student<Undergraduate>
{
private:
    int math;      //高数成绩
    int english;   //英语成绩
    int clanguage; //C语言成绩
public:
    //本科生构造函数
    Undergraduate(long id = -1, string name = "", string sex = "")
            : Student(id, name, sex) {}

    void setScore(int s1, int s2, int s3 = -1); //设置成绩的函数
    void setScore(void);

    void changeScore(void);//改变分数
    void setMath(void);                     //设置数学
    void setEnglish(void);               //设置英语
    void setClanguage(void);           //设置Ｃ语言
    int getSubject(void);              //选择科目名
    bool fail(int i); //检查科目是否及格
    friend ostream &operator<<(ostream &out, Undergraduate &und); //输出重载
    friend istream &operator>>(istream &in, Undergraduate &und);  //输出重载
    friend ofstream &operator<<(ofstream &out, Undergraduate &und); //输出重载
    friend ifstream &operator>>(ifstream &in, Undergraduate &und);  //输出重载
};
/*********************************************************************************/
/*******************************学生类********************************************/
/*********************************************************************************/

//研究生类
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

    void changeScore(void);                     //改变分数
    void setComprehensive(void);                //设置课程综合
    void setThesis(void);                       //设置毕业论文
    int getSubject(void);                       //选择科目名
    bool fail(int i);                           //检查科目是否及格
    friend ostream &operator<<(ostream &out, Postgradute &pos); //输出重载
    friend istream &operator>>(istream &in, Postgradute &pos);  //输出重载
    friend ofstream &operator<<(ofstream &out, Postgradute &pos); //输出重载
    friend ifstream &operator>>(ifstream &in, Postgradute &pos);  //输出重载
};