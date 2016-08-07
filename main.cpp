#include "mainwindow.h"
#include <QApplication>
#include"addressbook.h"
AddressBook addressbook;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
/*
#include"person.h"
#include"AddressBook.h"
#include <iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include <locale.h>
using namespace std;
int menu_select();
int main()
{
    setlocale(LC_CTYPE, "");
    char choice;
    AddressBook maillist;
    for (;;) {
        choice = menu_select();
        switch (choice) {
        case 1:maillist.Enter(); break;
        case 2:maillist.Delete(); break;
        case 3:maillist.List(); break;
        case 4:maillist.Save(); break;
        case 5:maillist.Read(); break;
        case 6:maillist.Search(); break;
        case 7:exit(0);
        }
    }
    return 0;
}
int menu_select()
{
    char c;
    cout << "             * * * * * * 通讯录 * * * * * *\n";
    cout << "             *       1. 添加联系人         *\n";
    cout << "             *       2. 删除联系人         *\n";
    cout << "             *       3. 显示联系人         *\n";
    cout << "             *       4. 通讯录保存       　*\n";
    cout << "             *       5. 读取通讯录         *\n";
    cout << "             *       6. 查找联系人         *\n";
    cout << "             *       7. 退出               *\n";
    cout << "             * * * * * * * * * * * * * * * *\n";
    cout << "                     \n请输入(1~7)中的一个整数:";
    do {//键盘输入循环
        cin.get(c);
    } while (c<'1' || c>'7');
    return c - 48;
}

*/
