#pragma once

#include "interface_Base.h"
#define CLASS Management<STUDENT>
#define GRADE Management<Management<STUDENT>>
#define SPECIALITY Management<Management<Management<STUDENT>>>

/*********************************************************************************/
/*******************************班级操作类****************************************/
/*********************************************************************************/

template<class STUDENT>
class Interface_Class : virtual public Interface_Base<STUDENT>
{
private:
    typename list<SPECIALITY >::iterator pSpeciality;      //指向该专业
    typename list<GRADE>::iterator pGrade;                 //指向该年级
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
void Interface_Class<STUDENT>::run()
{
    pSpeciality = show(this->speciality_vector); //选择相应的专业
    pGrade = show(pSpeciality->MyVector);        //选择相应的年级

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
int Interface_Class<STUDENT>::menu()
{
    int choice; //选项

    //system("cls"); // 清屏
    cout << "\n 	            班级管理" << endl;
    cout << "\n============================================";
    cout << "\n||                                        ||";
    cout << "\n||    1.添加数据          2.修改数据        ||";
    cout << "\n||                                        ||";
    cout << "\n||    3.删除数据          4.查询数据        ||";
    cout << "\n||                                        ||";
    cout << "\n||              0.返回                    ||";
    cout << "\n============================================";
    cout << "\n               请选择(0-6): " << endl;

    while (!(cin >> choice) || cin.peek() != '\n' || choice < 0 || choice > 4)
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cerr << "输入数据错误，请重新输入:" << endl;
    }

    return choice;
}

template<class STUDENT>
void Interface_Class<STUDENT>::add_info()
{
    cout << "您要新建的班级名:";
    string name;
    cin >> name;

    //定义一个管理对象，并存进容器
    CLASS classes(name);
    pGrade->MyVector.push_back(classes);
}

template<class STUDENT>
void Interface_Class<STUDENT>::del_info()
{
    try
    {
        //假如该年级只有一个班，那就不能删了
        if (pGrade->MyVector.size() > 1)
        {
            cout << "您要删除的班级名:";
            string name;
            cin >> name;
            pGrade->MyVector.erase(search(name, pGrade->MyVector));
            cout << "删除成功！！！" << endl;
        } else
        {
            cout << "抱歉，该年级只有一个班级，不能进行删除操作" << endl;
        }
    }
    catch (string)
    {
        cout << "抱歉，找不到\n" << endl;
        // system("pause");
    }
}

template<class STUDENT>
void Interface_Class<STUDENT>::change_info()
{
    //定义一个要管理的东西的迭代器
    typename list<CLASS >::iterator p;

    try
    {
        cout << "您要修改的班级名:";
        string name;
        cin >> name;
        p = search(name, pGrade->MyVector);

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


