#ifndef _FRIEND_H_
#define _FRIEND_H_
#include"person.h"
using namespace std;
class Friend:public Person{
    char MeetPlace[100];
public:
    Friend(string avastar_path,string name, string phone, string email, string postcode, string add,string meetPlace,
        int year,int month,int day,int type);
    Friend() { }
    string GetMeetPlace()const;
};
#endif
