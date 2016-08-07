#include"person.h"
using namespace std;
Person::Person(string avastar_path, string name, string phone, string email, string postcode, string add,
            int year, int month, int day, int type):Type(type),Year(year),Month(month),Day(day)
{
    memset(Avastar_path,0,sizeof(Avastar_path));
    memset(Name, 0, sizeof(Name));
    memset(Phone, 0, sizeof(Phone));
    memset(Email, 0, sizeof(Email));
    memset(Postcode, 0, sizeof(Postcode));
    memset(Add, 0, sizeof(Add));
    //memset(Type,0,sizeof(Type));
    //memset(Birth,0,sizeof(Birth));

    memcpy_s(Avastar_path, 200, avastar_path.c_str(), avastar_path.length());
    memcpy_s(Name, 100, name.c_str(), name.length());
    memcpy_s(Phone, 100, phone.c_str(), phone.length());
    memcpy_s(Email, 100, email.c_str(), email.length());
    memcpy_s(Postcode, 100, postcode.c_str(), postcode.length());
    memcpy_s(Add, 100, add.c_str(), add.length());
    //memcpy_s(Type, 100, type.c_str(), type.length());
    //memcpy_s(Birth, 100, year.c_str(), year.length());
}
string Person::GetName()const
{
    string s = Name;    
    return s;
}
string Person::GetPhone()const
{
    string s = Phone;
    return s;
}
string Person::GetEmail()const
{
    string s = Email;
    return s;
}
string Person::GetPostcode()const
{
    string s = Postcode;
    return s;
}
string Person::GetAdd()const
{
    string s = Add;
    return s;
}

int Person::GetType() const{
    return Type;
}

int Person::GetMonth() const{
    return Month;
}
int Person::GetYear() const{
    return Year;
}
int Person::GetDay() const{
    return Day;
}
