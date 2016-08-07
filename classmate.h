#ifndef _CLASSMATE_H_
#define _CLASSMATE_H_
#include"person.h"
using namespace std;
class Classmate:public Person{
    char SchoolName[40];
public:
    Classmate(string avastar_path, string name, string phone, string email, string postcode, string add, string schoolName,
           int year,int month,int day, int type);
    Classmate(){}
    string GetSchoolName()const;
};
#endif
