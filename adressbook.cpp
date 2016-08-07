//AddressBook.cpp
#include"Person.h"
#include"Friend.h"
#include"Relative.h"
#include"Colleague.h"
#include"Classmate.h"
#include"AddressBook.h"
using namespace std;
Person *  AddressBook::Enter(string avastar_path, int type, string name, string phone, string email, string postcode, string add, int year, int month, int day, string p1, string p2)//输入联系人的信息
{
    if(type == Person::type_Friend){//p1认识的地方
        Item[Num] = new Friend(avastar_path,name, phone, email, postcode, add, p1,
                                 year, month, day,type);
    }else if(type == Person::type_Relative){//p1 realation 关系
        Item[Num] = new Relative(avastar_path,name, phone, email, postcode, add, p1,
                                 year, month, day,type);
    }else if(type == Person::type_Colleague){//p1 公司 p2 工作岗位
        Item[Num] = new Colleague(avastar_path,name, phone, email, postcode, add, p1,p2,
                                 year, month, day,type);
    }else if(type == Person::type_Classmate){//p1 学校名字
        Item[Num] = new Classmate(avastar_path,name, phone, email, postcode, add, p1,
                                 year, month, day,type);
    }else return NULL;
    ++statistic_group[type];
    ++statistic_birth_month[month];
    return Item[Num++];
}
void AddressBook::Delete(Person *pitem){//删除联系人
    int t;
    if (!Num) return ;//无联系人，直接返回
    else{
        for (t = 0; t<Num; t++){
            if (Item[t] == pitem) {
                --statistic_group[Item[t]->GetType()];
                --statistic_birth_month[Item[t]->GetMonth()];
                Num--;
                delete(Item[t]);
                for (int i = t; i < Num + 2; i++){
                    Item[i] = Item[i + 1];
                }
                return ;
            }
        }
    }
}

//对当前数据进行排序， a : 1:按名字排序，非1按电话号码排序
void AddressBook::Sort(int a){
    int i, j;
    Person* temp;
    if (Num){
        for (i = 0; i < Num; i++){
            for (j = Num - 1; j > i; j--){
                if (a == 1)
                    if(Item[j - 1]->GetName() > Item[j]->GetName()){//姓名排序
                        temp = Item[j - 1];
                        Item[j - 1] = Item[j];
                        Item[j] = temp;
                    }
                if (a != 1)
                    if (Item[j - 1]->GetPhone() > Item[j]->GetPhone())//电话号码排序
                    {
                        temp = Item[j - 1];
                        Item[j - 1] = Item[j];
                        Item[j] = temp;
                    }
            }
        }
    }
}


void AddressBook::Save()//保存到文件夹
{
    ofstream file[4];
    //打开文件
    file[0].open("address_friend.txt",ios::out | ios::binary);
    file[1].open("address_classmate.txt",ios::out | ios::binary);
    file[2].open("address_colleague.txt",ios::out | ios::binary);
    file[3].open("address_relative.txt",ios::out | ios::binary);
    //统计数目
    int cnt[4] = {0};
    for(int i = 0 ; i < Num; ++i){
        if((Item[i]->GetType()) == Person::type_Friend)   ++cnt[0];
        if((Item[i]->GetType()) == Person::type_Classmate)   ++cnt[1];
        if((Item[i]->GetType()) == Person::type_Colleague)   ++cnt[2];
        if((Item[i]->GetType()) == Person::type_Relative)   ++cnt[3];
    }
    //写入文件
    //写入数目
    file[0].write((char*)&cnt[0], sizeof(cnt[0]));
    file[1].write((char*)&cnt[1], sizeof(cnt[1]));
    file[2].write((char*)&cnt[2], sizeof(cnt[2]));
    file[3].write((char*)&cnt[3], sizeof(cnt[3]));
    //写入数据
    for (int i = 0; i<Num; i++) {
        if((Item[i]->GetType()) == Person::type_Friend)      file[0].write((char *)Item[i], sizeof(Friend));
        if((Item[i]->GetType()) == Person::type_Classmate)   file[1].write((char *)Item[i], sizeof(Classmate));
        if((Item[i]->GetType()) == Person::type_Colleague)   file[2].write((char *)Item[i], sizeof(Colleague));
        if((Item[i]->GetType()) == Person::type_Relative)    file[3].write((char *)Item[i], sizeof(Relative));
    }
    //关闭文件
    file[0].close();file[1].close();file[2].close();file[3].close();
}

void AddressBook::Read()//读取文件
{   
    ifstream file;int j = 0;
    //读取 friend
    file.open("address_friend.txt", ios::in);
    file.read((char*)&j, sizeof(j));
    statistic_group[Person::type_Friend] = j;
    for (int i = 0; i<j; i++,++Num) {
        Item[Num] =(new Friend);
        file.read((char *)Item[Num], sizeof(Friend));      
        ++statistic_birth_month[Item[Num]->GetMonth()];
    }
    file.close();
    //读取classmate
    file.open("address_classmate.txt", ios::in);
    file.read((char*)&j, sizeof(j));
    statistic_group[Person::type_Classmate] = j;
    for (int i = 0; i<j; i++,++Num) {
        Item[Num] =(new Classmate);
        file.read((char *)Item[Num], sizeof(Classmate));
        ++statistic_birth_month[Item[Num]->GetMonth()];
    }
    file.close();
    //读取colleague
    file.open("address_colleague.txt", ios::in);
    file.read((char*)&j, sizeof(j));
    statistic_group[Person::type_Colleague] = j;
    for (int i = 0; i<j; i++,++Num) {
        Item[Num] =(new Colleague);
        file.read((char *)Item[Num], sizeof(Colleague));
        ++statistic_birth_month[Item[Num]->GetMonth()];
    }
    file.close();    
    //读取 relative
    file.open("address_relative.txt", ios::in);
    file.read((char*)&j, sizeof(j));
    statistic_group[Person::type_Relative] = j;
    for (int i = 0; i<j; i++,++Num) {
        Item[Num] =(new Relative);
        file.read((char *)Item[Num], sizeof(Relative));
        ++statistic_birth_month[Item[Num]->GetMonth()];
    }
    file.close();
}
Person * AddressBook::Search(string s)//查找联系人
{
    int t;
    if (Num){//通讯录不为空
        for (t = 0; t<Num; t++){
            if ((Item[t]->GetName() == s) || (Item[t]->GetPhone() == s)) {
                return Item[t];
            }
        }
    }
    return NULL;
}




