//
// Created by niracler on 6/15/17.
//
#pragma once

#include "interface_Base.h"
#define CLASS Management<STUDENT>
#define GRADE Management<Management<STUDENT>>
#define SPECIALITY Management<Management<Management<STUDENT>>>

/*********************************************************************************/
/*******************************专业操作类****************************************/
/*********************************************************************************/
template<class STUDENT>
class Interface_Speciality : virtual public Interface_Base<STUDENT>
{
private:
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
void Interface_Speciality<STUDENT>::run()
{
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
            case 4:
                try
                {
                    show(this->speciality_vector);
                }
                catch (int) {}
                break; //查询函数
        }
    }
}

template<class STUDENT>
int Interface_Speciality<STUDENT>::menu()
{
    int choice; //选项

    //system("cls"); // 清屏
    cout << "\n 	           专业管理" << endl;
    cout << "\n*************************************************";
    cout << "\n*****                                       *****";
    cout << "\n*****    1.添加专业          2.修改专业       *****";
    cout << "\n*****                                       *****";
    cout << "\n*****    3.删除专业          4.显示所有专业    *****";
    cout << "\n*****                                       *****";
    cout << "\n*****              0.返回                    *****";
    cout << "\n*************************************************";
    cout << "\n               请选择(0-6): ";

    while (!(cin >> choice) || cin.peek() != '\n' || choice < 0 || choice > 4)
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cerr << "输入数据错误，请重新输入:" << endl;
    }

    return choice;
}

template<class STUDENT>
void Interface_Speciality<STUDENT>::add_info()
{
    cout << "您要新建的专业:";
    string name;
    cin >> name;

    //定义一个专业对象，并初始化其年级，班级,并存进容器
    SPECIALITY speciality(name);
    GRADE grade("一年级");
    CLASS classes("1班");

    grade.MyVector.push_back(classes);
    speciality.MyVector.push_back(grade);
    this->speciality_vector.push_back(speciality);
}

template<class STUDENT>
void Interface_Speciality<STUDENT>::del_info()
{
    try
    {
        cout << "请输入要删除的专业名:";
        string name;
        cin >> name;

        if (this->speciality_vector.size() > 1)
        {
            this->speciality_vector.erase(search(name, this->speciality_vector));
        } else
        {
            cout << "抱歉，只有一个专业，不能进行删除操作！！！" << endl;
        }
    }
    catch (string)
    {
        cout << "抱歉，找不到\n" << endl;
        // system("pause");
    }
}

template<class STUDENT>
void Interface_Speciality<STUDENT>::change_info()
{
    //定义一个要管理的东西的迭代器
    typename list<SPECIALITY>::iterator p;

    try
    {
        cout << "管理名字:";
        string name;
        cin >> name;
        p = search(name, this->speciality_vector);

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
