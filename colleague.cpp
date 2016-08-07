#include"colleague.h"
using namespace std;
Colleague::Colleague(string avastar_path, string name, string phone, string email, string postcode, string add, string company, string pos,
                    int year, int month, int day, int type):
    Person( avastar_path,name, phone, email, postcode, add,  year, month, day,type)
{
    memset(Company, 0, sizeof(Company));
    memset(Pos, 0, sizeof(Pos));
    memcpy_s(Company, 100, company.c_str(), company.length());
    memcpy_s(Pos, 100, pos.c_str(), pos.length());
}
string Colleague::GetCompany()const{
    string s = Company;
    return s;
}
string Colleague::GetPos()const{
    string s = Pos;
    return s;
}

