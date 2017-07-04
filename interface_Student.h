#pragma once

#include "interface_Base.h"

#define N 5

/*********************************************************************************/
/*******************************学生操作类****************************************/
/*********************************************************************************/
//学生操作类
template<class STUDENT>
class Interface_Student : virtual public Interface_Base<STUDENT>
{
protected:
    STUDENT *MySearch(long id);        //按学号查找学生的功能
    STUDENT *MySearch(string name);    //按姓名查找学生的功能
    vector<STUDENT *> pStudent_vector; //学生指针容器
    void myPutIn(void);                //将所有学生推进学生容器
    bool flag;                         //是否本地
public:
    int menu(void);             //菜单函数
    void run(bool flag = true); //运行函数
    void add_info(void);        //增加函数
    void del_info(void);        //删除函数
    void change_info(void);     //改变函数
    void display(void);         //显示函数
    void sort(void);            //排序函数
    void statistics(void);      //统计函数
    int page(int now);          //分页函数
};

template<class STUDENT>
void Interface_Student<STUDENT>::statistics(void)
{
    int choice, subject; //选项
    STUDENT stu(99);
    subject = stu.getSubject(); //选择科目
    if (subject == 0)
        return;

    //我的天，一次过把事情都做完吧
    int aver = 0, min = 100, max = 0, n = 0;
    int count[6] = {0, 0, 0,
                    0, 0, 0}; //超过平均成绩的人数,优,良，中，及格，不及格

    for (int i = 0; i < pStudent_vector.size(); ++i)
    {
        int score = pStudent_vector[i]->getSubject(subject); //当前学生该科成绩
        if (score == -1)
            continue;
        if (score > max)
            max = score;
        if (score < min)
            min = score;
        if (score >= 90)
            count[1]++;
        if (score < 90 && score >= 80)
            count[2]++;
        if (score < 80 && score >= 70)
            count[3]++;
        if (score < 70 && score >= 60)
            count[4]++;
        if (score < 60)
            count[5]++;
        n++; //记录有效人数
        aver += score;
    }
    aver /= n;

    while (true)
    {
        // system("cls"); // 清屏
        cout << "\n 	            统计" << endl;
        cout << "\n============================================";
        cout << "\n||                                        ||";
        cout << "\n||    0.返回             1.平均成绩       ||";
        cout << "\n||                                        ||";
        cout << "\n||    2.最低成绩         3.最高成绩       ||";
        cout << "\n||                                        ||";
        cout << "\n||      4.超过平均成绩的学生名单及人数    ||";
        cout << "\n||                                        ||";
        cout << "\n||      5.不及格学生名单及人数            ||";
        cout << "\n||                                        ||";
        cout << "\n||      6.不同等级的学生人数              ||";
        cout << "\n||                                        ||";
        cout << "\n============================================";
        cout << "\n               请选择(0-6): " << endl;

        while (!(cin >> choice) || cin.peek() != '\n' || choice < 0 || choice > 6)
        {
            cin.clear();           // 恢复状态标志
            cin.ignore(100, '\n'); // 略过缓存
            cerr << "输入数据错误，请重新输入:" << endl;
        }
        if (choice == 0)
            return;

        switch (choice)
        {
            case 1:cout << "平均成绩：" << aver << endl;
                break;
            case 2:cout << "最低分：" << min << endl;
                break;
            case 3:cout << "最高分：" << max << endl;
                break;
            case 4:
            {
                for (int i = 0; i < pStudent_vector.size(); ++i)
                {
                    if (pStudent_vector[i]->getSubject(subject) > aver)
                    {
                        cout << *pStudent_vector[i];
                        count[0]++;
                    }
                }
                cout << "超过平均成绩的人数：" << count[0] << endl;
            }
                break;

            case 5:
            {
                for (int i = 0; i < pStudent_vector.size(); ++i)
                {
                    if (pStudent_vector[i]->fail(subject))
                    {
                        cout << *pStudent_vector[i];
                    }
                }
                cout << "不及格的人数：" << count[5] << endl;
            }
                break;

            case 6:
            {
                cout << "成绩为优的人数：" << count[1] << endl;
                cout << "成绩为良的人数：" << count[2] << endl;
                cout << "成绩为中的人数：" << count[3] << endl;
                cout << "成绩为及格的人数：" << count[4] << endl;
                cout << "成绩为不及格的人数：" << count[5] << endl;
            }
                break;
        }
    }
}

template<class STUDENT>
inline int Interface_Student<STUDENT>::page(int now)
{
    //将现在的页数给我，我返回你要的页数
    int choice;
    int n = pStudent_vector.size() / N; //总页数
    if (pStudent_vector.size() % N)
        n++;

    cout << "\n0-退出\t\t1-首页\t\t2-上一页\t【" << now << "/";
    cout << n << "】\t3-下一页\t\t4-尾页\t\t5-跳页:";
    do
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cin >> choice;
    }
    while (choice < 0 || choice > 5);
    if (choice == 0)
        throw 0;

    switch (choice)
    {
        case 1:now = 1;
            break; //首页
        case 2:
            if (now == 1)
            {
                cout << "已经是首页，无上一页了哦！\n";
                // system("pause");
            } else
            {
                now--;
            }
            break; //上一页
        case 3:
            if (now == n)
            {
                printf("已经是尾页，无下一页了哦！\n");
                // system("pause");
            } else
            {
                now++;
            }
            break; //下一页
        case 4:now = n;
            break;
        case 5:cout << "请输入您要跳至哪一页：";
            do
            {
                cin >> now;
            }
            while (now < 1 || now > n);
            break;
    }

    return now;
}

template<class STUDENT>
void Interface_Student<STUDENT>::sort(void)
{

    int choice, nowPage = 0; //选项,现在的页数

    // system("cls"); // 清屏
    cout << "\n 	            学生信息查询" << endl;
    cout << "\n**************************************************";
    cout << "\n*****                                        *****";
    cout << "\n*****    1.按学号从低到高排序并显示。        *****";
    cout << "\n*****                                        *****";
    cout << "\n*****    2.按总成绩从高到低排序并显示。      *****";
    cout << "\n*****                                        *****";
    cout << "\n*****               0.返回                   *****";
    cout << "\n*****                                        *****";
    cout << "\n**************************************************";
    cout << "\n               请选择(0-4): " << endl;

    while (!(cin >> choice) || cin.peek() != '\n' || choice < 0 || choice > 2)
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cerr << "输入数据错误，请重新输入:";
    }

    switch (choice)
    {
        case 1:
        {
            for (int i = 0; i < pStudent_vector.size() - 1; ++i)
            {
                for (int j = i; j < pStudent_vector.size(); ++j)
                {
                    if (pStudent_vector[j]->getId() < pStudent_vector[i]->getId())
                    {
                        STUDENT *temp;
                        temp = pStudent_vector[i];
                        pStudent_vector[i] = pStudent_vector[j];
                        pStudent_vector[j] = temp;
                    }
                }
            }

            while (true)
            {
                for (int i = 0; i + (nowPage * N) < pStudent_vector.size() && i < N;
                     ++i)
                {
                    cout << *pStudent_vector[i + (nowPage * N)];
                }
                try
                {
                    nowPage = page(nowPage + 1) - 1;
                }
                catch (int)
                {
                    break;
                }
            }
        }
            break;

        case 2:
        {
            for (int i = 0; i < pStudent_vector.size() - 1; ++i)
            {
                for (int j = i; j < pStudent_vector.size(); ++j)
                {
                    if (pStudent_vector[j]->getTotalscore() >
                        pStudent_vector[i]->getTotalscore())
                    {
                        STUDENT *temp;
                        temp = pStudent_vector[i];
                        pStudent_vector[i] = pStudent_vector[j];
                        pStudent_vector[j] = temp;
                    }
                }
            }

            int nLast = 1, n = 2;
            cout << "第1名:  " << *pStudent_vector[0];
            for (int i = 1; i < pStudent_vector.size(); ++i, n++)
            {
                if (pStudent_vector[i]->getTotalscore() ==
                    pStudent_vector[i - 1]->getTotalscore())
                {
                    cout << "第" << nLast << "名:  " << *pStudent_vector[i];
                } else
                {
                    cout << "第" << n << "名:  " << *pStudent_vector[i];
                    nLast = n;
                }
            }
        }
            break;
    }
}

template<class STUDENT>
void Interface_Student<STUDENT>::myPutIn(void)
{

    this->pStudent_vector.clear(); //先将学生指针容器清空

    typename list<SPECIALITY >::iterator pSpeciality; //指向专业的迭代器
    typename list<GRADE>::iterator pGrade;           //年级迭代器
    typename list<CLASS >::iterator pClass;           //班级迭代器
    typename list<STUDENT>::iterator pStudent;       //学生迭代器

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
                    this->pStudent_vector.push_back(&(*pStudent));
                }
            }
        }
    }
}

template<class STUDENT>
void Interface_Student<STUDENT>::run(bool flag)
{

    this->flag = flag;

    while (1)
    {
        int choice = this->menu();

        if ((!flag) && (choice == 1 || choice == 2))
        {
            cout << "\n\tsorry，1,2功能在此不能用!!" << endl;
            break;
        }

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
            case 6:this->statistics();
                break;
        }
    }
}

template<class STUDENT>
int Interface_Student<STUDENT>::menu(void)
{
    int choice; //选项

    // system("cls"); // 清屏
    cout << "\n 	            学生管理" << endl;
    cout << "\n****************************************************";
    cout << "\n*****                                          *****";
    cout << "\n*****    1.添加学生          2.修改学生        *****";
    cout << "\n*****                                          *****";
    cout << "\n*****    3.删除学生          4.查询学生        *****";
    cout << "\n*****                                          *****";
    cout << "\n*****    5.排序              6.统计            *****";
    cout << "\n*****                                          *****";
    cout << "\n*****              0.返回                      *****";
    cout << "\n****************************************************";
    cout << "\n               请选择(0-6): ";

    while (!(cin >> choice) || cin.peek() != '\n' || choice < 0 || choice > 6)
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cerr << "输入数据错误，请重新输入:" << endl;
    }

    return choice;
}

template<class STUDENT>
void Interface_Student<STUDENT>::add_info(void) //增加函数
{
    static long count = Student<STUDENT>::maxId;
    count++; //数数

    //定义一个学生对象，并存进容器
    STUDENT stu(count);

    try
    {
        cout << "\t   请选择专业：";
        stu.getSpeciality() = show(this->speciality_vector);

        cout << "\t   请选择年级：";
        stu.getGrade() = show(stu.getSpeciality()->MyVector);

        cout << "\t   请选择班级：";
        stu.getClass() = show(stu.getGrade()->MyVector);
    }
    catch (int)
    {
        return;
    }

    cin >> stu;                              //输入基本信息
    stu.getClass()->MyVector.push_back(stu); //用班级容器装住该学生以免让他飞走了
    this->pStudent_vector.push_back(
            &stu.getClass()->MyVector.back()); //也把他放到学生容器里
}

template<class STUDENT>
void Interface_Student<STUDENT>::del_info(void) //删除函数
{
    try
    {
        //根据学号找到学生
        cout << "请输入学生学号：";
        long id;
        cin >> id;

        STUDENT *p = MySearch(id); //找这个学生
        p->getClass()->MyVector.erase(
                search(p->getName(), p->getClass()->MyVector)); //在班级容器里把他删了

        for (int i = 0; i < pStudent_vector.size(); i++)
        {
            if (pStudent_vector[i] == p)
            {
                pStudent_vector.erase(pStudent_vector.begin() + i);
            }
        }
        cout << "恭喜，成功删除了！！！" << endl;
    }
    catch (long)
    {
        cout << "抱歉，找不到该学生\n" << endl;
        // system("pause");
    }
}

template<class STUDENT>
void Interface_Student<STUDENT>::change_info(void) //改变函数
{
    STUDENT *p;                            //定义一个学生指针
    string name;                           //记录姓名的对象
    typename list<CLASS >::iterator pClass; //班级指针

    try
    {
        cout << "请输入学生学号：";
        long id;
        cin >> id;
        p = this->MySearch(id); //在学生容器中找到他
        cout << *p;
        name = p->getName();
    }
    catch (long)
    {
        cout << "抱歉，找不到该学生\n" << endl;
        return;
    }

    int choice; //选项

    // system("cls"); // 清屏
    cout << "\n 	            修改学生" << endl;
    cout << "\n============================================";
    cout << "\n||                                        ||";
    cout << "\n||    1.修改姓名          2.修改性别      ||";
    cout << "\n||                                        ||";
    cout << "\n||    3.修改班级          4.修改专业      ||";
    cout << "\n||                                        ||";
    cout << "\n||    5.修改年级          6.修改成绩      ||";
    cout << "\n||                                        ||";
    cout << "\n||              0.返回                    ||";
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
                typename list<CLASS >::iterator classes =
                        p->getClass(); //指向这个学生所在的班级

                pClass = p->getClass() =
                        show(p->getGrade()
                                     ->MyVector); //从该年级中选择班级，让学生的班级指针指向该班级
                p->getClass()->MyVector.push_back(*p); //用班级容器装住该学生

                classes->MyVector.erase(
                        search(p->getName(), classes->MyVector)); //从原来的班级中删去
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

                p->getSpeciality() = show(this->speciality_vector); //选择相应的年级
                p->getGrade() = show(p->getSpeciality()->MyVector); //选择相应的年级
                pClass = p->getClass() =
                        show(p->getGrade()
                                     ->MyVector); //从该年级中选择班级，让学生的班级指针指向该班级
                p->getClass()->MyVector.push_back(
                        *p); //用班级容器装住该学生以免让他飞走了

                classes->MyVector.erase(
                        search(p->getName(), classes->MyVector)); //从原来的班级中删去
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

                p->getGrade() = show(p->getSpeciality()->MyVector); //选择相应的年级
                pClass = p->getClass() =
                        show(p->getGrade()
                                     ->MyVector); //从该年级中选择班级，让学生的班级指针指向该班级
                p->getClass()->MyVector.push_back(
                        *p); //用班级容器装住该学生以免让他飞走了

                classes->MyVector.erase(
                        search(p->getName(), classes->MyVector)); //从原来的班级中删去
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

    if (choice == 3 || choice == 4 || choice == 5)
    {
        //在学生指针容器中把他重新弄一次
        for (int i = 0; i < pStudent_vector.size(); i++)
        {
            if (pStudent_vector[i] == p)
            {
                pStudent_vector.erase(pStudent_vector.begin() + i);
            }
        }

        pStudent_vector.push_back(&(*search(name, pClass->MyVector)));
    }
}

template<class STUDENT>
void Interface_Student<STUDENT>::display(void)
{

    int choice; //选项

    // system("cls"); // 清屏
    cout << "\n 	            学生信息查询" << endl;
    cout << "\n**************************************************";
    cout << "\n*****                                        *****";
    cout << "\n*****    1.按姓名查询        2.按学号查询    *****";
    cout << "\n*****                                        *****";
    cout << "\n*****    3.显示所有学生      4.显示不及格    *****";
    cout << "\n*****                                        *****";
    cout << "\n*****               0.返回                   *****";
    cout << "\n*****                                        *****";
    cout << "\n**************************************************";
    cout << "\n               请选择(0-4): " << endl;

    while (!(cin >> choice) || cin.peek() != '\n' || choice < 0 || choice > 4)
    {
        cin.clear();           // 恢复状态标志
        cin.ignore(100, '\n'); // 略过缓存
        cerr << "输入数据错误，请重新输入:";
    }

    switch (choice)
    {
        case 0:return;
        case 1: //按姓名查找
        {
            try
            {
                string name;
                cout << "姓名：";
                cin >> name;
                cout << *(MySearch(name));
            }
            catch (string)
            {
                cout << "抱歉，找不到该学生\n" << endl;
            }
        }
            break;

        case 2: //按学号查找
        {
            try
            {
                cout << "请输入学生学号：";
                long id;
                cin >> id;
                cout << *(this->MySearch(id));
            }
            catch (long)
            {
                cout << "抱歉，找不到该学生\n" << endl;
            }
        }
            break;

        case 3: //显示所有学生
        {
            int nowPage = 0;
            while (true)
            {
                for (int i = 0; i + (nowPage * N) < pStudent_vector.size() && i < N;
                     ++i)
                {
                    cout << *pStudent_vector[i + (nowPage * N)];
                }
                try
                {
                    nowPage = page(nowPage + 1) - 1;
                }
                catch (int)
                {
                    break;
                }
            }
        }
            break;

        case 4: //不及格的学生举手
        {
            STUDENT stu(99);
            choice = stu.getSubject();

            for (int i = 0; i < pStudent_vector.size(); ++i)
            {
                if (pStudent_vector[i]->fail(choice))
                {
                    cout << *pStudent_vector[i];
                }
            }
        }
            break;
    }

    // system("pause");
}

template<class STUDENT>
inline STUDENT *Interface_Student<STUDENT>::MySearch(long id)
{
    //遍历学生，找到就返回指针
    for (int i = 0; i < pStudent_vector.size(); ++i)
    {
        if (pStudent_vector[i]->getId() == id)
        {
            return pStudent_vector[i];
        }
    }

    throw id; //要是找不到，则抛出
}

template<class STUDENT>
inline STUDENT *Interface_Student<STUDENT>::MySearch(string name)
{
    //遍历学生，找到就返回指针
    for (int i = 0; i < pStudent_vector.size(); ++i)
    {
        if (pStudent_vector[i]->getName() == name)
        {
            return pStudent_vector[i];
        }
    }

    throw name; //要是找不到，则抛出
}
