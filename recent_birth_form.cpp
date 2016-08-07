#include "recent_birth_form.h"
#include "ui_recent_birth_form.h"
#include"addressbook.h"
#include"list_item_form.h"
#include <QDate>
#include<QMessageBox>
extern AddressBook addressbook;
recent_birth_form::recent_birth_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recent_birth_form)
{

    ui->setupUi(this);    
    for(int i = 0; i < addressbook.Num; ++i){
        QString str = addressbook.Item[i]->GetBirth().c_str();
        QStringList list1 = str.split('-');
        QDate birth_1 = QDate::currentDate();
        QDate birth_2 = birth_1.addDays(7);
        QDate birth(QString(list1.at(0)).toInt(),QString(list1.at(1)).toInt(),QString(list1.at(2)).toInt());
        if(birth >= birth_1 && birth <= birth_2){
            List_Item_Form *custom1 = new List_Item_Form(addressbook.Item[i]);
            QListWidgetItem *listItem1 = new QListWidgetItem();
            listItem1->setSizeHint(QSize(0, 71));
            ui->listWidget->addItem(listItem1);
            ui->listWidget->setItemWidget(listItem1, custom1);
            connect(custom1,List_Item_Form::list_item_form_close,this,do_list_item_form_close);
        }
    }
}

recent_birth_form::~recent_birth_form()
{
    delete ui;
}

void recent_birth_form::do_list_item_form_close(Person *p)
{
    QMessageBox::information(NULL,"123","成功删除");
    int n = ui->listWidget->count();
    for(int i = 0 ; i < n ; ++i){
        List_Item_Form *pp =(List_Item_Form *) ui->listWidget->itemWidget( ui->listWidget->item(i));
        if( pp->p == p ){
            ui->listWidget->takeItem(i);
            break;
        }
    }
}
