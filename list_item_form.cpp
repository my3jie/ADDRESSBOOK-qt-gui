#include "list_item_form.h"
#include "ui_list_item_form.h"
#include <QMessageBox>
#include"info_form.h"
#include"addressbook.h"
#include<QDate>
#include<QProcess>
#include<fstream>

extern AddressBook addressbook;
List_Item_Form::List_Item_Form(Person *pitem,QWidget * parent):
    QWidget(parent),
    p(pitem),
    ui(new Ui::List_Item_Form)
{
    ui->setupUi(this);
    //按钮控件初始不显示
    ui->toolButton->setVisible(false);
    ui->toolButton_2->setVisible(false);
    ui->toolButton_3->setVisible(false);
    ui->label_4->setVisible(false);
    //通过p是否为0来判断是否新建联系人
    if(p){
        ui->label_2->setText(QString((p)->GetName().c_str()));
        ui->label_3->setText(QString((p)->GetPhone().c_str()));
        //判断是否有头像
        if(string(p->Avastar_path) != ""){
            ui->label->setPixmap(QPixmap(QString(p->Avastar_path)));
        }else ui->label->setPixmap(QPixmap(QString(":/new/icon/avatar.png")));
    }else{
        //创建新的联系人
        addressbook.Enter("",Person::type_Friend,"","","","","",2016,6,9,"");
        p = (addressbook.Item[addressbook.Num - 1]);
        on_toolButton_clicked();
    }
    flg_recent_birth = 0;
    //判断是否最近生日
    QDate birth_1 = QDate::currentDate();
    QDate birth_2 = birth_1.addDays(7);
    //把时间设置为今年，用以判断是否最近生日
    QDate birth(birth_1.year(),p->GetMonth(),p->GetDay());
    if(birth >= birth_1 && birth <= birth_2){
        flg_recent_birth = 1;
         ui->label_4->setText(birth.toString("yyyy-M-d dddd"));
    }
}
List_Item_Form::~List_Item_Form(){
    delete ui;
}
void List_Item_Form::on_toolButton_clicked(){
    Info_Form *k = new Info_Form(p);//创建窗口
    connect(k,Info_Form::avastar_changed,this,do_avastar_changed);
    connect(k,Info_Form::name_changed,this,do_name_changed);
    connect(k,Info_Form::phone_changed,this,do_phone_changed);
    connect(k,Info_Form::p_addr_changed,this,do_p_addr_changed);
    connect(k,Info_Form::delete_Item,this,do_delete_Item);
    connect(k,Info_Form::birth_changed,this,do_birth_changed);
    k->show();
}
void List_Item_Form::do_avastar_changed(QString str){
    //头像改变
    ui->label->setPixmap(QPixmap(str));
}
void List_Item_Form::do_name_changed(QString name){
    //名字改变
    if(name != ui->label_2->text()){
        ui->label_2->setText(name);
        emit name_Changed(name);
    }
}
void List_Item_Form::do_phone_changed(QString phone){
    //电话改变
    ui->label_3->setText(phone);
}
void List_Item_Form::do_p_addr_changed(Person *_p){
    //类型改变
    p = _p;
}
void List_Item_Form::do_delete_Item(){
    //删除时间
    on_toolButton_2_clicked();
}
void List_Item_Form::do_birth_changed(QDate *birth){
    //生日改变，重新设置标志
    QDate birth_1 = QDate::currentDate();
    QDate birth_2 = birth_1.addDays(7);
    birth->setDate(birth_1.year(),birth->month(),birth->day());
    if(*birth >= birth_1 && *birth <= birth_2){
        flg_recent_birth = 1;
        ui->label_4->setText(birth->toString("yyyy-M-d dddd"));
    }else {
        flg_recent_birth = 0;
    }
}
void List_Item_Form::on_toolButton_2_clicked(){
    //删除联系人
    addressbook.Delete(p);
    addressbook.Save();
    emit list_item_form_close(p);
    this->close();
    //QMessageBox::information(NULL,"标题","删除按钮");
}
void List_Item_Form::enterEvent(QEvent *){
    //鼠标进入，显示按钮
    ui->toolButton->setVisible(true);
    ui->toolButton_2->setVisible(true);
    if(flg_recent_birth){
        ui->label_4->setVisible(true);
        ui->toolButton_3->setVisible(true);
    }
}
void List_Item_Form::leaveEvent(QEvent *){
    //鼠标离开隐藏按钮
    ui->toolButton->setVisible(false);
    ui->toolButton_2->setVisible(false);
    if(flg_recent_birth){
        ui->label_4->setVisible(false);
        ui->toolButton_3->setVisible(false);
    }
}
void List_Item_Form::on_toolButton_3_clicked(){
    //生成祝贺文本文件
    string birth_file_name("birth_text.txt");
    fstream file(birth_file_name,ios::out);
    string birth_text = p->GetName() + ":\n\n    祝生日快乐，健康幸福。\n\n\t\t祝贺人:qhy 叶超\n";
    file<<birth_text;
    file.close();
    //使用notepad打开文本
    QString program = "notepad";
    QStringList arguments;
    arguments << birth_file_name.c_str();
    QProcess *myProcess = new QProcess(this);
    myProcess->start(program, arguments);

}


void List_Item_Form::mouseDoubleClickEvent(QMouseEvent *)
{
    on_toolButton_clicked();
}
