#pragma once

#include "interface_Base.h"

/*********************************************************************************/
/*******************************学生操作类****************************************/
/*********************************************************************************/
//学生操作类
template<class STUDENT>
class Interface_Student : virtual public Interface_Base<STUDENT>
{
protected:
    typename list<STUDENT>::iterator mySearch(long id);     //按学号查找学生的功能
    typename list<STUDENT>::iterator mySearch(string name); //按姓名查找学生的功能
    list <STUDENT> student_vector;                          //学生容器
    bool student_flag;                                      //能用就举手
    void myPutIn(void);                                     //将所有学生推进学生容器
public:
    Interface_Student() {}

    int menu(void);         //菜单函数
    void run(void);         //运行函数
    void add_info(void);    //增加函数
    void del_info(void);    //删除函数
    void change_info(void); //改变函数
    void display(void);     //显示函数
    void sort(void);        //排序函数
    void statistics(void);  //统计函数
};

template<class STUDENT>
void Interface_Student<STUDENT>::myPutIn(void)
{
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
                    this->student_vector.push_back(*pStudent);
                }
            }
        }
    }
}

/*
函数功能：学生操作
*/
template<class STUDENT>
void Interface_Student<STUDENT>::run(void)
{
    while (1)
    {
        int choice = this->menu();


        switch (choice)
        {
            case 0:return;
            case 1:this->add_info();
                break; //调用学生添加函数
            case 2:this->change_info();
                break; //调用学生修改函数
            case 3:this->del_info();
                break; //调用学生删除函数
            case 4:this->display();
                break; //学生查询函数
            case 5:break;
            case 6:break;
        }
    }
}

//函数功能：学生管理菜单
template<class STUDENT>
int Interface_Student<STUDENT>::menu(void)
{
    int choice; //选项

    //system("cls"); /* 清屏 */
    cout << "\n 	            学生管理" << endl;
    cout << "\n****************************************************";
    cout << "\n*****                                        *****";
    cout << "\n*****    1.添加学生          2.修改学生        *****";
    cout << "\n*****                                        *****";
    cout << "\n*****    3.删除学生          4.查询学生        *****";
    cout << "\n*****                                        *****";
    cout << "\n*****    5.排序              6.统计           *****";
    cout << "\n*****                                        *****";
    cout << "\n*****              0.返回                     *****";
    cout << "\n*****************************************************";
    cout << "\n               请选择(0-6): ";

    while (!(cin >> choice) || cin.peek() != '\n' || choice < 0 || choice > 6)
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cerr << "输入数据错误，请重新输入:" << endl;
    }

    return choice;
}

//函数功能：添加学生
template<class STUDENT>
void Interface_Student<STUDENT>::add_info(void) //增加函数
{
    //数数
    static int count = 0;
    count++;

    //定义一个学生对象，并存进容器
    //我的天，我的天，我的天，我的天，这只是局部变量！！！！！！！！！！
    STUDENT stu(count);

    try
    {
        //选择相应的专业
        stu.getSpeciality() = show(this->speciality_vector);

        //选择相应的年级
        stu.getGrade() = show(stu.getSpeciality()->MyVector);

        //从该年级中选择班级，让学生的班级指针指向该班级
        stu.getClass() = show(stu.getGrade()->MyVector);
    }
    catch (int)
    {
        return;
    }

    //将学生的指针放到这里的学生容器中
    cin >> stu;

    //用班级容器装住该学生以免让他飞走了
    stu.getClass()->MyVector.push_back(stu);
}

//函数功能：删除学生
template<class STUDENT>
void Interface_Student<STUDENT>::del_info(void) //删除函数
{
    try
    {
        //根据学号找到学生
        cout << "请输入学生学号：";
        long id;
        cin >> id;

        typename list<STUDENT>::iterator p;
        p = mySearch(id);
        p->getClass()->MyVector.erase(p);
    }
    catch (long)
    {
        cout << "抱歉，找不到该学生\n" << endl;
        // system("pause");
    }
}

//函数功能：修改学生
template<class STUDENT>
void Interface_Student<STUDENT>::change_info(void) //改变函数
{
    //定义一个学生指针
    typename list<STUDENT>::iterator p;

    try
    {
        cout << "请输入学生学号：";
        long id;
        cin >> id;
        p = this->mySearch(id);
        cout << *p;
    }
    catch (long)
    {
        cout << "抱歉，找不到该学生\n" << endl;
        return;
    }

    int choice; //选项

    //system("cls"); /* 清屏 */
    cout << "\n 	            修改学生" << endl;
    cout << "\n============================================";
    cout << "\n||                                        ||";
    cout << "\n||    1.修改姓名          2.修改性别        ||";
    cout << "\n||                                        ||";
    cout << "\n||    3.修改班级          4.修改专业        ||";
    cout << "\n||                                        ||";
    cout << "\n||    5.修改年级          6.修改成绩        ||";
    cout << "\n||                                        ||";
    cout << "\n||              0.退出系统                 ||";
    cout << "\n============================================";
    cout << "\n               请选择(0-6): " << endl;

    while (!(cin >> choice) || cin.peek() != '\n' || choice < 0 || choice > 6)
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cerr << "输入数据错误，请重新输入:" << endl;
    }

    switch (choice)
    {
        case 0:return;
        case 1:p->setName();
            break; //修改姓名
        case 2:p->setSex();
            break; //修改性别

        case 3:
        {
            try
            {
                if (p->getGrade()->MyVector.size() == 1)
                {
                    cout << "该年级现在只有一个班级！！！" << endl;
                    return;
                }

                typename list<CLASS >::iterator classes = p->getClass();

                //从该年级中选择班级，让学生的班级指针指向该班级
                p->getClass() = show(p->getGrade()->MyVector);

                //用班级容器装住该学生以免让他飞走了
                p->getClass()->MyVector.push_back(*p);

                classes->MyVector.erase(p);
            }
            catch (int)
            {
                return;
            }

        }
            break; //修改班级

        case 4:
        {
            try
            {
                if (this->speciality_vector.size() == 1)
                {
                    cout << "现在只有一个专业！！！" << endl;
                    return;
                }

                typename list<CLASS >::iterator classes = p->getClass();

                //选择相应的年级
                p->getSpeciality() = show(this->speciality_vector);

                //选择相应的年级
                p->getGrade() = show(p->getSpeciality()->MyVector);

                //从该年级中选择班级，让学生的班级指针指向该班级
                p->getClass() = show(p->getGrade()->MyVector);

                //用班级容器装住该学生以免让他飞走了
                p->getClass()->MyVector.push_back(*p);

                classes->MyVector.erase(p);
            }
            catch (int)
            {
                return;
            }

        }
            break; //修改专业

        case 5:
        {
            try
            {
                if (p->getSpeciality()->MyVector.size() == 1)
                {
                    cout << "该专业现在只有一个年级！！！" << endl;
                    return;
                }

                typename list<CLASS >::iterator classes = p->getClass();

                //选择相应的年级
                p->getGrade() = show(p->getSpeciality()->MyVector);

                //从该年级中选择班级，让学生的班级指针指向该班级
                p->getClass() = show(p->getGrade()->MyVector);

                //用班级容器装住该学生以免让他飞走了
                p->getClass()->MyVector.push_back(*p);

                classes->MyVector.erase(p);
            }
            catch (int)
            {
                return;
            }
        }
            break; //修改年级

        case 6:p->changeScore();
            break; //修改成绩
    }
}

//函数功能：显示学生
template<class STUDENT>
void Interface_Student<STUDENT>::display(void)
{

    int choice; //选项

    //system("cls"); /* 清屏 */
    cout << "\n 	            学生信息查询" << endl;
    cout << "\n***************************************************";
    cout << "\n*****                                        *****";
    cout << "\n*****    1.按姓名查询        2.按学号查询       *****";
    cout << "\n*****                                        *****";
    cout << "\n*****    3.显示所有学生      4.显示不及格       *****";
    cout << "\n*****                                        *****";
    cout << "\n*****               0.退出系统                *****";
    cout << "\n*****                                        *****";
    cout << "\n****************************************************";
    cout << "\n               请选择(0-4): " << endl;

    while (!(cin >> choice) || cin.peek() != '\n' || choice < 0 || choice > 4)
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cerr << "输入数据错误，请重新输入:";
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


    switch (choice)
    {
        case 0:return;
        case 1:
        {
            try
            {
                string name;
                cout << "姓名：";
                cin >> name;
                cout << *(mySearch(name));
            }
            catch (string)
            {
                cout << "抱歉，找不到该学生\n" << endl;
            }
        }
            break; //按姓名查找

        case 2:
        {
            try
            {
                cout << "请输入学生学号：";
                long id;
                cin >> id;
                cout << *(this->mySearch(id));
            }
            catch (long)
            {
                cout << "抱歉，找不到该学生\n" << endl;
            }
        }
            break; //按学号查找

        case 3:
        {
            this->myPutIn();
            pStudent = student_vector.begin();
            for (int i = 0; i < student_vector.size(); ++i, pStudent++)
            {
                //遍历学生
                cout << *pStudent;
            }
        }
            break; //显示所有学生

        case 4:
        {
            STUDENT stu(99);
            choice = stu.getSubject();

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
                        for (int l = 0; l < pClass->MyVector.size(); ++l, pStudent)
                        {
                            //遍历学生
                            cout << *pStudent;
                        }
                    }
                }
            }
        }
            break; //不及格的学生举手
    }

    // system("pause");
}

//查找学生的功能
template<class STUDENT>
typename list<STUDENT>::iterator Interface_Student<STUDENT>::mySearch(long id)
{
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
                    if (pStudent->getId() == id)
                    {
                        return pStudent;
                    }
                }
            }
        }
    }

    throw id; //要是找不到，则抛出
}


template<class STUDENT>
typename list<STUDENT>::iterator Interface_Student<STUDENT>::mySearch(string name)
{
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
                    if (pStudent->getName() == name)
                    {
                        return pStudent;
                    }
                }
            }
        }
    }

    throw name; //要是找不到，则抛出
}