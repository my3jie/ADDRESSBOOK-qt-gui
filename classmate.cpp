#include"classmate.h"
using namespace std;
Classmate::Classmate(string avastar_path, string name, string phone, string email, string postcode, string add, string schoolName,
                    int year, int month, int day, int type):
    Person(avastar_path,name, phone, email, postcode, add,  year, month, day,type)
{
    memset(SchoolName, 0, sizeof(SchoolName));
    memcpy_s(SchoolName,  100, schoolName.c_str(), schoolName.length());
}
string Classmate::GetSchoolName()const{
    string s = SchoolName;
    return s;
}
