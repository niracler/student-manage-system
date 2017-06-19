//
// Created by manjaro on 5/30/17.
//
# include <iostream>
# include "student.h"
#include <fstream>
# include <iomanip> //对齐要用到

using namespace std;


/*********************************************************************************/
/*******************************本科生类******************************************/
/*********************************************************************************/

//设置成绩的函数
void Undergraduate::setScore(int s1, int s2, int s3)
{
    //成绩赋值
    this->math = s1;
    this->english = s2;
    this->clanguage = s3;

    //算总分
    if (s2 != -1 && s2 != -1 && s3 != -1)
    {
        this->totalscore = s1 + s2 + s3;
    } else
    {
        this->totalscore = -1;
    }
}

void Undergraduate::setScore()
{
    this->setClanguage();
    this->setMath();
    this->setEnglish();

    //设置成绩,计算总分
    this->setScore(this->clanguage, this->math, this->english);
}

void Undergraduate::changeScore()
{
    //选择专业
    int choice = this->getSubject();

    switch (choice)
    {
        case 1:this->setMath();
            break;
        case 2:this->setEnglish();
            break;
        case 3:this->setClanguage();
            break;
    }

    //设置成绩,计算总分
    this->setScore(this->clanguage, this->math, this->english);
}

//设置数学
void Undergraduate::setMath(void)
{
    cout << "高数成绩(没有就填-1)：";

    cin >> this->math;

    while (this->math < -1 || this->math > 100)
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cerr << "抱歉，成绩的范围在0～100" << endl;
        cin >> this->math;
    }
}

//设置英语
void Undergraduate::setEnglish(void)
{
    cout << "英语成绩(没有就填-1):";

    cin >> this->english;

    while (this->english < -1 || this->english > 100)
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cerr << "抱歉，成绩的范围在0～100" << endl;
        cin >> this->english;
    }
}

//设置Ｃ语言
void Undergraduate::setClanguage(void)
{
    cout << "C语言成绩(没有就填-1)：";

    cin >> this->clanguage;

    while (this->clanguage < -1 || this->clanguage > 100)
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cerr << "抱歉，成绩的范围在0～100" << endl;
        cin >> this->clanguage;
    }
}

//选择科目名
int Undergraduate::getSubject(void)
{
    int choice; //选项

    //system("cls"); /* 清屏 */
    cout << "\n 	            本科生科目" << endl;
    cout << "\n============================================";
    cout << "\n||                                        ||";
    cout << "\n||    1.高数     　　　   2.英语 　　　      ||";
    cout << "\n||                                        ||";
    cout << "\n||    3.Ｃ语言           0.退出系统　　　　  ||";
    cout << "\n||                                        ||";
    cout << "\n============================================";
    cout << "\n               请选择(0-3): " << endl;

    while (!(cin >> choice) || cin.peek() != '\n' || choice < 0 || choice > 3)
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cerr << "输入数据错误，请重新输入:" << endl;
    }

    return choice;
}

//检查科目是否及格
bool Undergraduate::fail(int i)
{
    switch (i)
    {
        case 1:
        {
            if (this->math < 60 && this->math > -1)
            {
                return true;
            }
        }
            break;

        case 2:
        {
            if (this->english < 60 && this->english > -1)
            {
                return true;
            }
        }
            break;

        case 3:
        {
            if (this->clanguage < 60 && this->clanguage > -1)
            {
                return true;
            }
        }
            break;
    }

    return false;
}

//本科生输出运算符重载函数
ostream &operator<<(ostream &out, Undergraduate &und)
{
    und.basePut();                   //基本信息输出
    out << setw(4) << und.clanguage; // C语言成绩输出
    out << setw(10) << und.math;     //高数成绩输出
    out << setw(10) << und.english;  //英语成绩输出
    und.elsePut();                   //排名输出

    return out;
}

//本科生输入运算符重载函数
istream &operator>>(istream &in, Undergraduate &und)
{
    //基本信息输入
    und.input();

    //成绩输入
    cout << "\n以下是成绩" << endl;
    und.setScore();

    return in;
}

ofstream &operator<<(ofstream &out, Undergraduate &und)
{
    out << und.clanguage << ' ';
    out << und.english << ' ';
    out << und.math << ' ';

    return out;
}//输出重载

ifstream &operator>>(ifstream &in, Undergraduate &und)
{
    und.load(in);
    in >> und.clanguage >> und.english >> und.math;

    if (Student<Undergraduate>::maxId < und.getId())
    {
        Student<Undergraduate>::maxId = und.getId();
    }
    return in;
}//输出重载


/*********************************************************************************/
/*******************************研究生类******************************************/
/*********************************************************************************/

//设置成绩的函数
void Postgradute::setScore(int s1, int s2, int s3)
{
    this->comprehensive = s1;
    this->thesis = s2;

    //算总分
    if (s2 != -1 && s2 != -1)
    {
        this->totalscore = s1 + s2;
    }
}

void Postgradute::setScore(void)
{
    this->setComprehensive();
    this->setThesis();

    //设置成绩,计算总分
    this->setScore(this->comprehensive, this->thesis);
}

void Postgradute::changeScore(void)
{
    //选择专业
    int choice = this->getSubject();

    switch (choice)
    {
        case 1:this->setComprehensive();
            break;
        case 2:this->setThesis();
            break;
    }

    //设置成绩,计算总分
    this->setScore(this->comprehensive, this->thesis);
}

//设置课程终合
void Postgradute::setComprehensive(void)
{
    cout << "课程终合成绩：";
    cin >> this->comprehensive;

    while (this->comprehensive < -1 || this->comprehensive > 100)
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cerr << "抱歉，成绩的范围在0～100" << endl;
        cin >> this->comprehensive;
    }
}

//设置毕业论文
void Postgradute::setThesis(void)
{
    cout << "毕业论文：";
    cin >> this->thesis;

    while (this->thesis < -1 || this->thesis > 100)
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cerr << "抱歉，成绩的范围在0～100" << endl;
        cin >> this->thesis;
    }
}

//选择科目名
int Postgradute::getSubject(void)
{
    int choice; //选项

    //system("cls"); /* 清屏 */
    cout << "\n 	            研究生科目" << endl;
    cout << "\n============================================";
    cout << "\n||                                        ||";
    cout << "\n||    1.课程综合   　　　 2.毕业论文         ||";
    cout << "\n||                                        ||";
    cout << "\n||               0.退出系统　　       　　  ||";
    cout << "\n||                                        ||";
    cout << "\n============================================";
    cout << "\n               请选择(0-3): " << endl;

    while (!(cin >> choice) || cin.peek() != '\n' || choice < 0 || choice > 2)
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cerr << "输入数据错误，请重新输入:" << endl;
    }

    return choice;
}

//检查科目是否及格
bool Postgradute::fail(int i)
{
    switch (i)
    {
        case 1:
        {
            if (this->comprehensive < 60 && this->comprehensive > -1)
            {
                return true;
            }
        }
            break;

        case 2:
        {
            if (this->thesis < 60 && this->thesis > -1)
            {
                return true;
            }
        }
            break;
    }

    return false;
}

//研究生输出运算符重载函数
ostream &operator<<(ostream &out, Postgradute &pos)
{
    pos.basePut();                       //基本信息输出
    out << setw(8) << pos.comprehensive; //课程综合输出
    out << setw(8) << pos.thesis;       //毕业论文输出
    pos.elsePut();                       //排名输出

    return out;
}

//研究生输入运算符重载函数
istream &operator>>(istream &in, Postgradute &pos)
{
    //基本信息输入
    pos.input();

    //成绩输入
    cout << "\n以下是成绩" << endl;
    pos.setScore();

    return in;
}

ofstream &operator<<(ofstream &out, Postgradute &pos)
{
    out << pos.comprehensive << ' ' << pos.thesis << ' ';
    return out;
}//输出重载

ifstream &operator>>(ifstream &in, Postgradute &pos)
{
    pos.load(in);
    in >> pos.comprehensive >> pos.thesis;

    if (Student<Postgradute>::maxId < pos.getId())
    {
        Student<Postgradute>::maxId = pos.getId();
    }

    return in;
}//输出重载

