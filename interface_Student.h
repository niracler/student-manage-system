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
    list<STUDENT> student_vector;                          //学生容器
    bool student_flag;                                      //能用就举手
    void myPutIn(void);                                     //将所有学生推进学生容器
public:
    Interface_Student()
    {
        student_flag = false;
    }

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
void Interface_Student<STUDENT>::statistics()
{

}

template<class STUDENT>
void Interface_Student<STUDENT>::sort(void)
{
    //假如学生容器不能用，就将学生放进学生容器
    if (!student_flag)
    {
        this->myPutIn();
    }

    //学生迭代器
    typename list<STUDENT>::iterator p2, p1 = student_vector.begin();

    for (int i = 0; i < student_vector.size() - 1; ++i, p1++)
    {
        p2 = p1;
        for (int j = i; j < student_vector.size(); ++j, p2++)
        {
            if (p2->getTotalscore() > p1->getTotalscore())
            {
                STUDENT temp;
                temp = *p1;
                *p1 = *p2;
                *p2 = temp;
            }
        }
    }

    int  n = 1;
    p1 = p2= student_vector.begin();
    p1->setSchoolrank(n);
    for (int i = 0; i < student_vector.size(); ++i, p2++)
    {

        n++;
        if (p2->getTotalscore() == p1->getTotalscore())
        {
            p2->setSchoolrank(p1->getSchoolrank());
        }
        else
        {

            p2->setSchoolrank(n);
        }
        cout << *p2;
        p1 = p2;
    }
}

template<class STUDENT>
void Interface_Student<STUDENT>::myPutIn(void)
{
    //先将学生容器清空
    this->student_vector.clear();

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

    this->student_flag = true; //表示能用了
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
            case 5:this->sort();
                break;
            case 6:
                this->statistics();
                break;
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

    cin >> stu;//输入基本信息
    stu.getClass()->MyVector.push_back(stu);//用班级容器装住该学生以免让他飞走了
    this->student_vector.push_back(stu);    //也把他放到学生容器里
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

        //在学生容器里把它删了
        typename list<STUDENT>::iterator p;
        p = mySearch(id);
        student_vector.erase(p);

        //也在班级容器里把他删了
        p = p->getClass()->MyVector.begin();
        for (int i = 0; i < student_vector.size(); ++i, p++)
        {
            if (p->getId() == id)
            {
                p->getClass()->MyVector.erase(p);
                break;
            }
        }
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
        p = this->mySearch(id);//在学生容器中找到他
        cout << *p;
        //在班级容器中找到他
        p = p->getClass()->MyVector.begin();
        for (int i = 0; i < student_vector.size(); ++i, p++)
        {
            if (p->getId() == id)
            {
                break;
            }
        }
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

    this->student_flag = false;//还是失效了
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

    //学生迭代器
    typename list<STUDENT>::iterator pStudent;

    //假如学生容器不能用，就将学生放进学生容器
    if (!student_flag)
    {
        this->myPutIn();
    }

    switch (choice)
    {
        case 0:return;
        case 1://按姓名查找
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
            break;

        case 2://按学号查找
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
            break;

        case 3://显示所有学生
        {
            //遍历学生
            pStudent = student_vector.begin();
            for (int i = 0; i < student_vector.size(); ++i, pStudent++)
            {
                cout << *pStudent;
            }
        }
            break;

        case 4://不及格的学生举手
        {
            STUDENT stu(99);
            choice = stu.getSubject();

            pStudent = student_vector.begin();
            for (int i = 0; i < student_vector.size(); ++i, pStudent++)
            {
                if (pStudent->fail(choice))
                {
                    cout << *pStudent;
                }
            }
        }
            break;
    }

    // system("pause");
}

//查找学生的功能
template<class STUDENT>
typename list<STUDENT>::iterator Interface_Student<STUDENT>::mySearch(long id)
{
    //遍历学生，找到就返回迭代器
    //假如学生容器不能用，就将学生放进学生容器
    if (!student_flag)
    {
        this->myPutIn();
    }

    //学生迭代器
    typename list<STUDENT>::iterator pStudent = student_vector.begin();

    for (int i = 0; i < student_vector.size(); ++i, pStudent++)
    {
        if (pStudent->getId() == id)
        {
            return pStudent;
        }
    }

    throw id; //要是找不到，则抛出
}


template<class STUDENT>
typename list<STUDENT>::iterator Interface_Student<STUDENT>::mySearch(string name)
{
    //假如学生容器不能用，就将学生放进学生容器
    if (!student_flag)
    {
        this->myPutIn();
    }

    //学生迭代器
    typename list<STUDENT>::iterator pStudent = student_vector.begin();

    for (int i = 0; i < student_vector.size(); ++i, pStudent++)
    {
        if (pStudent->getName() == name)
        {
            return pStudent;
        }
    }

    throw name; //要是找不到，则抛出
}