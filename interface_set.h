#pragma once

#include "interface_Speciality.h"
#include "interface_Grade.h"
#include "interface_Class.h"
#include "interface_Student.h"

/*********************************************************************************/
/*******************************集合操作类****************************************/
/*********************************************************************************/

//把学生管理，班级管理，年级管理，专业管理杂揉在一起的类

template<class STUDENT>
class Interface_set :
        public Interface_Student<STUDENT>,
        public Interface_Class<STUDENT>,
        public Interface_Grade<STUDENT>,
        public Interface_Speciality<STUDENT>
{
protected:
    string fileName;
public:
    Interface_set(string fileName);

    ~Interface_set();

    void myRun(void);

    int myMenu(void);

    bool load();//读档函数
    bool save();//存档函数
};

template<class STUDENT>
Interface_set<STUDENT>::Interface_set(string fileName)
{
    this->fileName = fileName;

    if (!this->load())
    {
        cout << "   您是第一次使用，请初始化第一个专业！！！\n" << endl;

        //定义一个专业对象，并存进容器
        Interface_Speciality<STUDENT>::add_info();
    }
}

template<class STUDENT>
Interface_set<STUDENT>::~Interface_set(void)
{
    if (this->save())
    {
        cout << "存档结束" << endl;
    }
}

template<class STUDENT>
void Interface_set<STUDENT>::myRun(void)
{
    while (1)
    {
        int choice = this->myMenu();

        switch (choice)
        {
            case 0:return;
            case 1:Interface_Speciality<STUDENT>::run();
                break;
            case 2:Interface_Grade<STUDENT>::run();
                break;
            case 3:Interface_Class<STUDENT>::run();
                break;
            case 4:Interface_Student<STUDENT>::run();
                break;
        }
    }
}

template<class STUDENT>
int Interface_set<STUDENT>::myMenu(void)
{
    int choice; //选项

    //system("cls"); // 清屏
    cout << "\n\n 	            学生管理系统";
    cout << "\n*************************************************";
    cout << "\n*****                                        *****";
    cout << "\n*****    1.专业管理          2.年级管理        *****";
    cout << "\n*****                                        *****";
    cout << "\n*****    3.班级管理          4.学生管理        *****";
    cout << "\n*****                                        *****";
    cout << "\n*****              0.返回                     *****";
    cout << "\n*************************************************";
    cout << "\n               请选择(0-4): ";

    while (!(cin >> choice) || cin.peek() != '\n' || choice < 0 || choice > 4)
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cerr << "输入数据错误，请重新输入:" << endl;
    }

    return choice;
}

template<class STUDENT>
bool Interface_set<STUDENT>::save(void)
{
    ofstream out(fileName);
    if (!out)
    {
        cout << "文件打开失败呢！" << endl;
        return false;
    }

    //遍历学生，找到就返回迭代器
    //弄一个指向专业的迭代器
    typename list<SPECIALITY >::iterator pSpeciality;

    //年级迭代器
    typename list<GRADE>::iterator pGrade;

    //班级迭代器
    typename list<CLASS >::iterator pClass;

    //学生迭代器
    typename list<STUDENT>::iterator pStudent;

    out << this->speciality_vector.size() << ' ';//存取专业数
    pSpeciality = this->speciality_vector.begin();
    for (int i = 0; i < this->speciality_vector.size(); ++i, pSpeciality++)
    {
        //遍历专业, 把专业读进文件
        out << pSpeciality->getName() << ' ';//存专业名
        out << pSpeciality->MyVector.size() << ' ';//存取年级数

        pGrade = pSpeciality->MyVector.begin();
        for (int j = 0; j < pSpeciality->MyVector.size(); ++j, pGrade++)
        {
            //遍历年级, 把年级读进文件
            out << pGrade->getName() << ' '; //存取年级名
            out << pGrade->MyVector.size() << ' '; //存取班级数

            pClass = pGrade->MyVector.begin();
            for (int k = 0; k < pGrade->MyVector.size(); ++k, pClass++)
            {
                //遍历班级
                out << pClass->getName() << ' ';//存取班级名
                out << pClass->MyVector.size() << ' '; //存取学生数

                pStudent = pClass->MyVector.begin();
                for (int l = 0; l < pClass->MyVector.size(); ++l, pStudent++)
                {
                    //遍历学生
                    out << pStudent->getId() << ' '; //存取学号
                    out << pStudent->getName() << ' ';//存取姓名
                    out << pStudent->getSex() << ' '; //存取性别
                    out << pStudent->getTotalscore() << ' ';//存取总成绩
                    out << pStudent->getClassrank() << ' ';//存取班级排名
                    out << pStudent->getSchoolrank() << ' ';//存取校级排名
                    out << *pStudent;//存取成绩
                }
            }
        }
    }

    return true;
}

template<class STUDENT>
bool Interface_set<STUDENT>::load(void)
{
    ifstream in(fileName);
    if (!in)
    {
        return false;
    }

    int studentCount;      //学生数
    int id;
    int classCount;        //班级数
    int gradeCount;        //年级数
    int specialityCount;   //专业数
    STUDENT studentNew;
    CLASS classNew;
    GRADE gradeNew;
    SPECIALITY specialityNew;

    in >> specialityCount;//读取专业数
    if (specialityCount == 0) return false;

    for (int i = 0; i < specialityCount; ++i)
    {
        in >> specialityNew;//读专业名

        //读年级数
        in >> gradeCount;
        for (int j = 0; j < gradeCount; ++j)
        {
            in >> gradeNew;//读年级名

            //读班级数
            in >> classCount;
            for (int k = 0; k < classCount; ++k)
            {
                in >> classNew;//读班级名

                //读学生数
                in >> studentCount;
                for (int l = 0; l < studentCount; ++l)
                {
                    in >> studentNew;//读取学生数据
                    classNew.MyVector.push_back(studentNew);
                }

                //将班级放入年级
                gradeNew.MyVector.push_back(classNew);
                classNew.MyVector.clear();
            }

            //将年级放入
            specialityNew.MyVector.push_back(gradeNew);
            gradeNew.MyVector.clear();
        }

        //将专业放入
        this->speciality_vector.push_back(specialityNew);
        specialityNew.MyVector.clear();
    }

    //遍历学生，找到就返回迭代器
    //弄一个指向专业的迭代器
    typename list<SPECIALITY >::iterator pSpeciality;

    //年级迭代器
    typename list<GRADE>::iterator pGrade;

    //班级迭代器
    typename list<CLASS >::iterator pClass;

    //学生迭代器
    typename list<STUDENT>::iterator pStudent;


    pSpeciality = this->speciality_vector.begin();
    for (int i = 0; i < this->speciality_vector.size(); ++i, pSpeciality++)
    {
        //遍历专业
        pGrade = pSpeciality->MyVector.begin();
        for (int j = 0; j < pSpeciality->MyVector.size(); ++j, pGrade++)
        {
            //遍历年级
            pClass = pGrade->MyVector.begin();
            for (int k = 0; k < pGrade->MyVector.size(); ++k, pClass++)
            {
                //遍历班级
                pStudent = pClass->MyVector.begin();
                for (int l = 0; l < pClass->MyVector.size(); ++l, pStudent++)
                {
                    //遍历学生
                    pStudent->getClass() = pClass;
                    pStudent->getGrade() = pGrade;
                    pStudent->getSpeciality() = pSpeciality;
                }
            }
        }
    }

    return true;
}


