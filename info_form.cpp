#include "info_form.h"
#include "ui_info_form.h"
#include<QMessageBox>
#include <QFileDialog>
#include<QStringList>
#include <QCloseEvent>
#include"friend.h"
#include"addressbook.h"
#include"Relative.h"
#include"Colleague.h"
#include"Classmate.h"
#include<QDate>
extern AddressBook addressbook;

Info_Form::Info_Form(Person *pitem, QWidget *parent) :
    QWidget(parent),
    p(pitem),
    ui(new Ui::Info_Form)
{
    ui->setupUi(this);    
    ui->dateEdit->setCalendarPopup(true);//设置编辑日期的时候，弹出日期选择框
    if((p)->GetName() != ""){//通过名字判断是否是新建联系人
        Set_Edit_State(false);
    }else {
        Set_Edit_State(true);
        ui->pushButton_3->setText("关闭");//新建联系人，显示"关闭"而不是"取消"
    }    
    avastar_path = QString(p->Avastar_path);//获取头像路径
    if(avastar_path != ""){//头像为空使用默认图片
        ui->pushButton_5->setIcon(QIcon(avastar_path));
    }else ui->pushButton_5->setIcon(QIcon(QString(":/new/icon/avatar_add.png")));


    //设置默认的信息
    ui->lineEdit->setText(QString((p)->GetName().c_str()));//名字
    ui->lineEdit_2->setText(QString((p)->GetPhone().c_str()));//号码
    ui->lineEdit_3->setText(QString((p)->GetEmail().c_str()));//邮箱
    ui->lineEdit_4->setText(QString((p)->GetPostcode().c_str()));//邮政编码
    ui->lineEdit_5->setText(QString((p)->GetAdd().c_str()));//地址
    //设置生日的显示
    QDate birth(p->GetYear(),p->GetMonth(),p->GetDay());
    ui->dateEdit->setDate(birth);

    //显示对应的特性
    int type = (p)->GetType();
    if(type == Person::type_Friend){
        ui->tabWidget->setCurrentIndex(1);
        ui->lineEdit_7->setText(QString(((Friend*)(p))->GetMeetPlace().c_str()));
    }else if(type == Person::type_Relative){
        ui->tabWidget->setCurrentIndex(0);
        ui->lineEdit_8->setText(QString(((Relative*)(p))->GetRelation().c_str()));
    }else if(type == Person::type_Classmate){
        ui->tabWidget->setCurrentIndex(3);
        ui->lineEdit_11->setText(QString(((Classmate*)(p))->GetSchoolName().c_str()));
    }else if(type == Person::type_Colleague){
        ui->tabWidget->setCurrentIndex(2);
        ui->lineEdit_9->setText(QString(((Colleague*)(p))->GetCompany().c_str()));
        ui->lineEdit_10->setText(QString(((Colleague*)(p))->GetPos().c_str()));
    }
}
Info_Form::~Info_Form(){
    delete ui;
}

void Info_Form::Set_Edit_State(bool state){
    //设置编辑模式和查看模式
    //state：false：查看模式，true：编辑模式
    if(state){
        ui->pushButton_3->setText("取消");
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->lineEdit_3->setEnabled(true);
        ui->lineEdit_4->setEnabled(true);       
        ui->lineEdit_5->setEnabled(true);
        ui->dateEdit->setEnabled(true);
        ui->lineEdit_7->setEnabled(true);
        ui->lineEdit_8->setEnabled(true);
        ui->lineEdit_9->setEnabled(true);
        ui->lineEdit_10->setEnabled(true);
        ui->lineEdit_11->setEnabled(true);        
        ui->tabWidget->setEnabled(true);
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(true);
        ui->lineEdit->setStyleSheet("QLineEdit {border: 1px solid rgb(0, 0, 0);background:White;color: Black;}");
        ui->lineEdit_2->setStyleSheet("QLineEdit {border: 1px solid rgb(0, 0, 0);background:White;color: Black;}");
        ui->lineEdit_3->setStyleSheet("QLineEdit {border: 1px solid rgb(0, 0, 0);background:White;color: Black;}");
        ui->lineEdit_4->setStyleSheet("QLineEdit {border: 1px solid rgb(0, 0, 0);background:White;color: Black;}");
        ui->lineEdit_5->setStyleSheet("QLineEdit {border: 1px solid rgb(0, 0, 0);background:White;color: Black;}");
        ui->lineEdit_6->setStyleSheet("QLineEdit {border: 1px solid rgb(0, 0, 0);background:White;color: Black;}");
        ui->lineEdit_6->setVisible(false);
        ui->dateEdit->setVisible(true);
        ui->lineEdit_7->setStyleSheet("QLineEdit {border: 1px solid rgb(0, 0, 0);background:White;color: Black;}");        
        ui->lineEdit_8->setStyleSheet("QLineEdit {border: 1px solid rgb(0, 0, 0);background:White;color: Black;}");
        ui->lineEdit_9->setStyleSheet("QLineEdit {border: 1px solid rgb(0, 0, 0);background:White;color: Black;}");
        ui->lineEdit_10->setStyleSheet("QLineEdit {border: 1px solid rgb(0, 0, 0);background:White;color: Black;}");
        ui->lineEdit_11->setStyleSheet("QLineEdit {border: 1px solid rgb(0, 0, 0);background:White;color: Black;}");
    }
    else{
        ui->pushButton_3->setText("关闭");
        ui->lineEdit->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->lineEdit_3->setEnabled(false);
        ui->lineEdit_4->setEnabled(false);
        ui->lineEdit_5->setEnabled(false);
        ui->dateEdit->setEnabled(false);
        ui->lineEdit_7->setEnabled(false);
        ui->lineEdit_8->setEnabled(false);
        ui->lineEdit_9->setEnabled(false);
        ui->lineEdit_10->setEnabled(false);
        ui->lineEdit_11->setEnabled(false);
        ui->tabWidget->setEnabled(false);
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
        ui->lineEdit->setStyleSheet("QLineEdit {border: 0px;background:transparent;color: Black;}");
        ui->lineEdit_2->setStyleSheet("QLineEdit {border: 0px;background:transparent;color: Black;}");
        ui->lineEdit_3->setStyleSheet("QLineEdit {border: 0px;background:transparent;color: Black;}");
        ui->lineEdit_4->setStyleSheet("QLineEdit {border: 0px;background:transparent;color: Black;}");
        ui->lineEdit_5->setStyleSheet("QLineEdit {border: 0px;background:transparent;color: Black;}");
        ui->lineEdit_6->setStyleSheet("QLineEdit {border: 0px;background:transparent;color: Black;}");
        ui->lineEdit_6->setVisible(true);
        ui->dateEdit->setVisible(false);
        ui->lineEdit_7->setStyleSheet("QLineEdit {border: 0px;background:transparent;color: Black;}");
        ui->lineEdit_8->setStyleSheet("QLineEdit {border: 0px;background:transparent;color: Black;}");
        ui->lineEdit_9->setStyleSheet("QLineEdit {border: 0px;background:transparent;color: Black;}");
        ui->lineEdit_10->setStyleSheet("QLineEdit {border: 0px;background:transparent;color: Black;}");
        ui->lineEdit_11->setStyleSheet("QLineEdit {border: 0px;background:transparent;color: Black;}");
    }
}

void Info_Form::on_pushButton_clicked(){
    //进入编辑模式
    Set_Edit_State(true);
}
void Info_Form::on_pushButton_2_clicked(){
     Set_Edit_State(false);//进入查看模式
     if(ui->tabWidget->currentIndex() == 1){
            addressbook.Delete(p);
            p = addressbook.Enter(avastar_path.toStdString(),Person::type_Friend,"","","","","",2016,ui->dateEdit->date().month(),9,"","");
            (*(Friend *)p) =  Friend(
                         avastar_path.toStdString(),
                         ui->lineEdit->text().toStdString(),
                         ui->lineEdit_2->text().toStdString(),
                         ui->lineEdit_3->text().toStdString(),
                         ui->lineEdit_4->text().toStdString(),
                         ui->lineEdit_5->text().toStdString(),
                         ui->lineEdit_7->text().toStdString(),
                         ui->dateEdit->date().year(),
                         ui->dateEdit->date().month(),
                         ui->dateEdit->date().day(),
                         Person::type_Friend
                         );
     }else if(ui->tabWidget->currentIndex() == 0){
         addressbook.Delete(p);
         p = addressbook.Enter(avastar_path.toStdString(),Person::type_Relative,"","","","","",2016,ui->dateEdit->date().month(),9,"","");
         *(Relative *)p =  Relative(
                     avastar_path.toStdString(),
                     ui->lineEdit->text().toStdString(),
                     ui->lineEdit_2->text().toStdString(),
                     ui->lineEdit_3->text().toStdString(),
                     ui->lineEdit_4->text().toStdString(),
                     ui->lineEdit_5->text().toStdString(),
                     ui->lineEdit_8->text().toStdString(),
                     ui->dateEdit->date().year(),
                     ui->dateEdit->date().month(),
                     ui->dateEdit->date().day(),
                     Person::type_Relative
                     );
     }else if(ui->tabWidget->currentIndex() == 3){
         addressbook.Delete(p);
         p = addressbook.Enter(avastar_path.toStdString(),Person::type_Classmate,"","","","","",2016,ui->dateEdit->date().month(),9,"","");
        (*(Classmate *)p) =  Classmate(
                    avastar_path.toStdString(),
                    ui->lineEdit->text().toStdString(),
                    ui->lineEdit_2->text().toStdString(),
                    ui->lineEdit_3->text().toStdString(),
                    ui->lineEdit_4->text().toStdString(),
                    ui->lineEdit_5->text().toStdString(),
                    ui->lineEdit_11->text().toStdString(),
                     ui->dateEdit->date().year(),
                     ui->dateEdit->date().month(),
                     ui->dateEdit->date().day(),
                    Person::type_Classmate
                    );
     }else if(ui->tabWidget->currentIndex() == 2){
         addressbook.Delete(p);
         p = addressbook.Enter(avastar_path.toStdString(),Person::type_Colleague,"","","","","",2016,ui->dateEdit->date().month(),9,"","");
         (*(Colleague *)p) =  Colleague(
                         avastar_path.toStdString(),
                         ui->lineEdit->text().toStdString(),
                         ui->lineEdit_2->text().toStdString(),
                         ui->lineEdit_3->text().toStdString(),
                         ui->lineEdit_4->text().toStdString(),
                         ui->lineEdit_5->text().toStdString(),
                         ui->lineEdit_9->text().toStdString(),
                         ui->lineEdit_10->text().toStdString(),
                     ui->dateEdit->date().year(),
                     ui->dateEdit->date().month(),
                     ui->dateEdit->date().day(),
                         Person::type_Colleague
                         );
     }
     addressbook.Save();//保存数据
     //发出信息更改的信号
     emit name_changed(ui->lineEdit->text());
     emit phone_changed(ui->lineEdit_2->text());
     emit p_addr_changed(p);
     emit birth_changed(new QDate(ui->dateEdit->date()));
}

void Info_Form::on_pushButton_5_clicked()
{
     //选择头像
     QFileDialog *fileDialog = new QFileDialog(this);
     fileDialog->setWindowTitle(tr("Open"));
     fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
     fileDialog->setFileMode(QFileDialog::AnyFile);
     fileDialog->setViewMode(QFileDialog::Detail);
     fileDialog->setGeometry(10,30,300,200);
     fileDialog->setDirectory(".");
     if(fileDialog->exec() == QDialog::Accepted) {
          avastar_path = fileDialog->selectedFiles()[0];
         //QMessageBox::information(NULL,"路径",path);
         ui->pushButton_5->setIcon(QIcon(avastar_path));
         memset(p->Avastar_path,0,sizeof(p->Avastar_path));
         memcpy_s(p->Avastar_path, 200, avastar_path.toStdString().c_str(), avastar_path.toStdString().length());
         addressbook.Save();
         emit avastar_changed(avastar_path);
     }
}
void Info_Form::on_pushButton_3_clicked(){
    //显示原来的数据
    if(ui->pushButton_3->text() == "取消"){
        Set_Edit_State(false);
        ui->lineEdit->setText(QString((p)->GetName().c_str()));
        ui->lineEdit_2->setText(QString((p)->GetPhone().c_str()));
        ui->lineEdit_3->setText(QString((p)->GetEmail().c_str()));
        ui->lineEdit_4->setText(QString((p)->GetPostcode().c_str()));
        ui->lineEdit_5->setText(QString((p)->GetAdd().c_str()));       
        QDate birth(p->GetYear(),p->GetMonth(),p->GetMonth());
        ui->dateEdit->setDate(birth);
        int type = (p)->GetType();
        if(type == Person::type_Friend){
            ui->tabWidget->setCurrentIndex(1);
            ui->lineEdit_7->setText(QString(((Friend*)(p))->GetMeetPlace().c_str()));
        }else if(type == Person::type_Relative){
            ui->tabWidget->setCurrentIndex(0);
            ui->lineEdit_8->setText(QString(((Relative*)(p))->GetRelation().c_str()));
        }else if(type == Person::type_Classmate){
            ui->tabWidget->setCurrentIndex(2);
            ui->lineEdit_11->setText(QString(((Classmate*)(p))->GetSchoolName().c_str()));
        }else if(type == Person::type_Colleague){
            ui->tabWidget->setCurrentIndex(3);
            ui->lineEdit_9->setText(QString(((Colleague*)(p))->GetCompany().c_str()));
            ui->lineEdit_10->setText(QString(((Colleague*)(p))->GetPos().c_str()));
        }
    }else{
        this->close();
    }
}
void Info_Form::closeEvent(QCloseEvent *e){
    if(p->GetName() == ""){
        if(QMessageBox::information(NULL,"注意","名字为空，关闭以后将删除记录，是否继续",QMessageBox::Close,QMessageBox::Cancel) == QMessageBox::Close){
            emit delete_Item();
            e->accept();
        }else e->ignore();//点了取消,忽略关闭时间
    }
}
void Info_Form::on_dateEdit_dateChanged(const QDate &date){
    //日期改变，label也跟着改变
    ui->lineEdit_6->setText(date.toString("yyyy-M-d"));
}
