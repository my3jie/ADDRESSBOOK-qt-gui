#ifndef _ADDRESSBOOK_H
#define _ADDRESSBOOK_H
#include"person.h"
#include <iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;
const int ItemNum = 100;
class AddressBook
{
public:
    //Item,联系人的数据
    Person *Item[ItemNum];
    //当前联系人的数目
    int Num;
    AddressBook(){ Num = 0; }
    //新建联系人
    Person* Enter(string avastar_path,int type,string name,string phone,string email,string postcode,string add,int year,int month,int day,string p1,string p2="");
    //删除联系人
    void Delete(Person *pitem);
    //从磁盘中读取数据
    void Read();
    //保存数据到磁盘
    void Save();
    //对当前数据进行排序
    void Sort(int a);
    //查找指定字符串和电话，不存在返回NULL，
    Person *Search(string s);
    //信息统计
    int statistic_birth_month[13];//记录1~12月生日的人数
    int statistic_group[5];	//记录每个分组的人数
};
#endif
