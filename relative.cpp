#include"relative.h"
using namespace std;
Relative::Relative(string avastar_path, string  name, string  phone, string  email, string  postcode, string add, string  relation,
    int year, int month, int day, int type):
    Person( avastar_path,name, phone, email, postcode, add, year, month, day,type)
{
    memset(Relation, 0, sizeof(Relation));
    memcpy_s(Relation, 100, relation.c_str(), relation.length());
}


string Relative::GetRelation()const
{
    string s = Relation;
    return s;
}
