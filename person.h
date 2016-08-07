#ifndef ADDRESS_H
#define ADDRESS_H
#include <iostream>
#include<iomanip>
#include<fstream>
#include<string.h>
using namespace std;
class Person
{
public:
    char Avastar_path[200];
    char Name[100];
    char Phone[100];
    char Email[100];
    char Postcode[100];
    char Add[100];
    int Type;
    int Year;
    int Month;
    int Day;

    enum Type_Value{type_Relative = 1 ,type_Friend,type_Colleague,type_Classmate};
    Person(string avastar_path,string name, string phone, string email, string postcode, string add,
            int year,int month,int day,int type);
    Person(){}
    string GetName()const;
    string GetPhone()const;
    string GetEmail()const;
    string GetPostcode()const;
    string GetAdd()const;
    int GetType()const;
    int GetMonth()const;
    int GetYear()const;
    int GetDay()const;
};
#endif
