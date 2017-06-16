//
// Created by niracler on 6/15/17.
//
#pragma once

#include "interface_Base.h"
#define CLASS Management<STUDENT>
#define GRADE Management<Management<STUDENT>>
#define SPECIALITY Management<Management<Management<STUDENT>>>

/*********************************************************************************/
/*******************************年级操作类****************************************/
/*********************************************************************************/

template<class STUDENT>
class Interface_Grade : virtual public Interface_Base<STUDENT>
{
private:
    typename list<SPECIALITY >::iterator pSpeciality;      //指向该该专业
    list <STUDENT> student_vector;                         //学生容器
    bool student_flag;                                     //能用就举手
public:
    int menu(void);         //菜单函数
    void run(void);         //运行函数
    void add_info(void);    //增加函数
    void del_info(void);    //删除函数
    void change_info(void); //改变函数
};

template<class STUDENT>
void Interface_Grade<STUDENT>::run()
{
    //选择相应的专业
    pSpeciality = show(this->speciality_vector);

    while (1)
    {
        int choice = this->menu();

        switch (choice)
        {
            case 0:return;
            case 1:this->add_info();
                break; //调用添加函数
            case 2:this->change_info();
                break; //调用修改函数
            case 3:this->del_info();
                break; //调用删除函数
            case 4:break; //查询函数
        }
    }
}

template<class STUDENT>
int Interface_Grade<STUDENT>::menu()
{
    int choice; //选项

    //system("cls"); // 清屏
    cout << "\n 	           年级管理" << endl;
    cout << "\n*************************************************";
    cout << "\n*****                                       *****";
    cout << "\n*****    1.添加年级          2.修改年级       *****";
    cout << "\n*****                                       *****";
    cout << "\n*****    3.删除年级          4.显示所有年级    *****";
    cout << "\n*****                                       *****";
    cout << "\n*****              0.返回                    *****";
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
void Interface_Grade<STUDENT>::add_info()
{
    cout << "您要新建的年级:";
    string name;
    cin >> name;

    //定义一个年级对象，并存进容器
    GRADE grade(name);
    CLASS classes("1班");

    grade.MyVector.push_back(classes);
    pSpeciality->MyVector.push_back(grade);
}

template<class STUDENT>
void Interface_Grade<STUDENT>::del_info()
{
    try
    {
        //假如该年级只有一个班，那就不能删了
        if (pSpeciality->MyVector.size() > 1)
        {
            cout << "请输入要删除的年级名:";
            string name;
            cin >> name;
            pSpeciality->MyVector.erase(search(name, pSpeciality->MyVector));
            cout << "删除成功！！！" << endl;
        } else
        {
            cout << "抱歉，该专业只有一个班级，不能进行删除操作！！！" << endl;
        }
    }
    catch (string)
    {
        cout << "抱歉，找不到\n" << endl;
        // system("pause");
    }
}

template<class STUDENT>
void Interface_Grade<STUDENT>::change_info()
{
    //定义一个要管理的东西的迭代器
    typename list<GRADE>::iterator p;

    try
    {
        cout << "您要修改的年级的名字:";
        string name;
        cin >> name;
        p = search(name, pSpeciality->MyVector);

        cout << "要修改成:";
        cin >> name;
        p->setName(name);
    }
    catch (string)
    {
        cout << "抱歉，找不到\n" << endl;
        return;
    }
}

