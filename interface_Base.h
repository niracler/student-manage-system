#pragma once

#include "student.h"
#include "school.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

/*********************************************************************************/
/*******************************学生操作基类****************************************/
/*********************************************************************************/
//操作基类
template<class STUDENT>
class Interface_Base
{
protected:
    typename list<SPECIALITY >::iterator pSpeciality;  //指向该该专业
    typename list<GRADE>::iterator pGrade;             //指向该年级
    typename list<CLASS >::iterator pClass;            //指向该班级
    list <SPECIALITY> speciality_vector;               //专业容器
public:
    template<class VECTOR>
    friend typename VECTOR::iterator show(VECTOR &myVector);

    template<class VECTOR>
    friend typename VECTOR::iterator search(string name, VECTOR &myVector);
};

//这个可以弄成一个很厉害的模板，把容器放进来，就能显示出里面的所有东西
template<class VECTOR>
typename VECTOR::iterator show(VECTOR &myVector)
{
    typename VECTOR::iterator p = myVector.begin();

    int choice; //选项
    int i;

    //system("cls"); // 清屏
    cout << "\n************************************";

    for (i = 0; i < myVector.size(); i++, p++)
    {
        cout << "\n                               *****";
        cout << "\n*****        " << i + 1 << "." << p->getName();
    }

    cout << "\n                               *****";
    cout << "\n*****         0.返回";
    cout << "\n************************************";

    cout << "\n         请选择(0-" << i << "): " << endl;

    while (!(cin >> choice) || cin.peek() != '\n' || choice < 0 || choice > i)
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cerr << "输入数据错误，请重新输入:" << endl;
    }

    //表示返回
    if (choice == 0)
    {
        throw 0;
    }

    p = myVector.begin();
    for (int j = 0; j < choice - 1; ++j)
    {
        p++;
    }

    return p;
}

//模板拯救世界啊，把名字给我，把容器给我，我帮你找到它
template<class VECTOR>
typename VECTOR::iterator search(string name, VECTOR &myVector)
{
    typename VECTOR::iterator p = myVector.begin();

    //遍历，找到就返回迭代器
    for (int i = 0; i < myVector.size(); i++, p++)
    {
        if (name == p->getName())
        {
            return p;
        }
    }

    throw name; //要是找不到，则抛出
}