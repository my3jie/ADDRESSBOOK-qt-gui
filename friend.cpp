#include"friend.h"
using namespace std;
string Friend::GetMeetPlace()const
{
    string s = MeetPlace;
    return s;
}

Friend::Friend(string avastar_path, string name, string phone, string email, string postcode, string add, string meetPlace,
    int year, int month, int day, int type):
    Person( avastar_path,name, phone, email, postcode, add,  year, month, day, type)
{
    memset(MeetPlace, 0, sizeof(MeetPlace));
    memcpy_s(MeetPlace, 100, meetPlace.c_str(), meetPlace.length());
}
