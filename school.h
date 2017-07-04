#pragma once

#include "student.h" //学生类的东西
#include <fstream>
#include <list>

using namespace std;

//班级类,年级类，专业类
template<class MEMBER>
class Management
{
private:
    string name; //管理名字
public:
    list <MEMBER> MyVector;        //成员容器
    Management(string name = ""); //管理构造函数
    string getName(void);

    void setName(string name);

    template<class MEN>
    friend ifstream &operator>>(ifstream &in, Management<MEN> &man);
};

template<class MEMBER>
Management<MEMBER>::Management(string name)
{
    this->name = name;
}

template<class MEMBER>
string Management<MEMBER>::getName(void)
{
    return this->name;
}

template<class MEMBER>
void Management<MEMBER>::setName(string name)
{
    this->name = name;
}

template<class MEN>
ifstream &operator>>(ifstream &in, Management<MEN> &man)
{
    in >> man.name;
    return in;
}