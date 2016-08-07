#ifndef _RELATIVE_H_
#define _RELATIVE_H_
#include"person.h"
using namespace std;
class Relative:public Person{
    char Relation[100];//和本人关系（称呼）
public:
    Relative(string avastar_path,string name, string phone, string email, string postcode, string add, string relation,
        int year,int month,int day,int type);
    Relative(){}
    string GetRelation()const;
};
#endif
