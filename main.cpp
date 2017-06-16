#include "interface_set.h"

using namespace std;

int main(void)
{
    int choice; //选项
    Interface_set<Undergraduate> inter1("Undergradate.txt");
    Interface_set<Postgradute> inter2("Postgredute.txt");

    while (1)
    {
        //system("cls"); // 清屏
        cout << "\n\n 	            学生管理";
        cout << "\n*************************************************";
        cout << "\n*****                                       *****";
        cout << "\n*****    1.本科生管理         2.研究生管理     *****";
        cout << "\n*****                                       *****";
        cout << "\n*****              0.退出系统                *****";
        cout << "\n*************************************************";
        cout << "\n               请选择(0-2): ";

        while (!(cin >> choice) || cin.peek() != '\n' || choice < 0 || choice > 2)
        {
            cin.clear();           // 恢复状态标志
            cin.ignore(100, '\n'); // 略过缓存
            cerr << "输入数据错误，请重新输入:" << endl;
        }

        switch (choice)
        {
            case 0:return 0;
            case 1:inter1.myRun();
                break;
            case 2:inter2.myRun();
                break;
        }
    }
}
