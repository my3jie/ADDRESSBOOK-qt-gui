#ifndef _COLLEAGUE_H_
#define  _COLLEAGUE_H_
#include"person.h"
using namespace std;
class Colleague :public Person{
    char Company[100];//工作地点
    char Pos[40];//职位

public:
    Colleague(string avastar_path,string name, string phone, string email, string postcode, string add, string company, string pos,
                int year,int month,int day,int type);
    Colleague(){}
    string GetCompany()const;
    string GetPos()const;
};
#endif
