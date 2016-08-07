#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include"list_item_form.h"
#include<QListWidgetItem>
#include<QMenu>
#include<QDate>
#include<QStringList>
#include <QMouseEvent>
#include <QCompleter>
extern AddressBook addressbook;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint |Qt::WindowSystemMenuHint|Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint);
    createPopMenu();//创建菜单

    addressbook.Read();//读取数据
    addressbook.Sort(1);//排个序
    //读取数据到 ListWidget控件上
    for(int i = 0; i < addressbook.Num; ++i){
        cplist.append(addressbook.Item[i]->GetName().c_str());//把每组数据的名字和电话加入List中，用于搜索编辑框的自动补全功能
        cplist.append(addressbook.Item[i]->GetPhone().c_str());
        List_Item_Form *custom1 = new List_Item_Form(addressbook.Item[i]);//创建窗口
        QListWidgetItem *listItem1 = new QListWidgetItem();               //创建一个listItem
        listItem1->setSizeHint(QSize(0, 71));                             //设置大小
        ui->listWidget->addItem(listItem1);                               //把创建的ListItem加入ListWidget
        ui->listWidget->setItemWidget(listItem1, custom1);                //设置窗口
        connect(custom1,List_Item_Form::list_item_form_close,this,do_list_item_form_close);//关联子窗口和父窗口的信号和槽函数，这里是子窗口删除信号
        connect(custom1,List_Item_Form::name_Changed,this,do_name_Changed);
    }
    cplist.sort();//先对List里面的字符串进行排序
    //添加自动补全 compeleter 到 LineEdit
    string_list_model = new QStringListModel();
    cp = new QCompleter(string_list_model,this);
    ui->lineEdit->setCompleter(cp);
    string_list_model->setStringList(cplist);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolMenuButton_clicked(){
    //弹出下拉菜单
    popMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
}

void MainWindow::do_menu_triggered(QAction *action){
    if(action->text() == "查看[家人]"){
        ui->tabWidget->setCurrentIndex(0);
    }else if(action->text() == "查看[朋友]"){
        ui->tabWidget->setCurrentIndex(1);
    }else if(action->text() == "查看[同事]"){
        ui->tabWidget->setCurrentIndex(2);
    }else if(action->text() == "查看[同学]"){
        ui->tabWidget->setCurrentIndex(3);
    }else if(action->text() == "查看[所有]"){
        ui->tabWidget->setCurrentIndex(4);
    }else if(action->text() == "查询[最近生日]"){
        ui->tabWidget->setCurrentIndex(5);
    }else if(action->text() == "添加[联系人]"){
        ui->tabWidget->setCurrentIndex(6);        
    }else if(action->text() == "查看[统计信息]"){
        QString txt;
        txt += "通讯录共" + QString::number(addressbook.Num) + "个联系人\n";
        char str[][30] = {"","亲人","朋友","同事","同学"};
        for(int i = 1 ; i <= 4;++i){
            txt += str[i] + QString("分组有") + QString::number(addressbook.statistic_group[i]) + "人。\n";
        }
        txt += "\n\n";
        for(int i = 1 ; i <= 12 ; ++i){
            txt += QString::number(i) + "月生日有 " + QString::number(addressbook.statistic_birth_month[i]) + " 人。\n";
        }
        QMessageBox::information(NULL,"统计",txt);
    }else if(action->text() == "关于此程序"){
        QMessageBox::information(NULL,"关于","简单通讯录管理程序\nQtGUI入门程序\nC++大作业2程序\n作者：叶超 qhy");
    }else if(action->text() == "退出"){
        this->close();
    }
}

void MainWindow::do_list_item_form_close(Person *p)
{
    //QMessageBox::information(NULL,"123","成功删除");
    int n = ui->listWidget->count();
    for(int i = 0 ; i < n ; ++i){
        List_Item_Form *pp =(List_Item_Form *) ui->listWidget->itemWidget( ui->listWidget->item(i));
        if( pp->p == p ){
            ui->listWidget->takeItem(i);
            break;
        }
    }
}
void MainWindow::on_pushButton_2_clicked()
{
    //QMessageBox::information(NULL,"标题","查找联系人");
    Person *p = addressbook.Search(ui->lineEdit->text().toStdString());
    if(p){
        int n = ui->listWidget->count();
        for(int i = 0 ; i < n ; ++i){
            List_Item_Form *pp =(List_Item_Form *) ui->listWidget->itemWidget(ui->listWidget->item(i));
            if( (pp->p) == p ){
                pp->on_toolButton_clicked();
                break;
            }
        }
    }else QMessageBox::information(NULL,"查找结果","联系人或电话不存在");
}

void MainWindow::on_pushButton_3_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_4_clicked()
{
    this->showMinimized();
}
void MainWindow::mousePressEvent(QMouseEvent * e)
{
     last = e->globalPos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent * e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x()+dx, y()+dy);
}

void MainWindow::mouseMoveEvent(QMouseEvent * e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    last = e->globalPos();
    move(x()+dx, y()+dy);
}

void MainWindow::createPopMenu()
{
    popMenu = new QMenu(this);
    popMenu->addAction(new QAction(QIcon(":/new/icon/icon_home.png"),"查看[家人]", this));
    popMenu->addAction(new QAction(QIcon(":/new/icon/icon_friend.png"),"查看[朋友]", this));
    popMenu->addAction(new QAction(QIcon(":/new/icon/icon_colleague.png"),"查看[同事]", this));
    popMenu->addAction(new QAction(QIcon(":/new/icon/icon_classmate.png"),"查看[同学]", this));
    popMenu->addAction(new QAction(QIcon(":/new/icon/icon_all.png"),"查看[所有]", this));
    popMenu->addAction(new QAction(QIcon(":/new/icon/icon_birth.png"),"查询[最近生日]", this));
    popMenu->addAction(new QAction(QIcon(":/new/icon/plus.png"),"添加[联系人]", this));
    popMenu->addAction(new QAction(QIcon(":/new/icon/more.png"),"查看[统计信息]", this));
    popMenu->addAction(new QAction(QIcon(":/new/icon/mini.png"),"关于此程序", this));
    popMenu->addAction(new QAction(QIcon(":/new/icon/close.png"),"退出", this));    
    popMenu->setStyleSheet("QMenu{background:white;border:1px solid gray;padding:5px}"
                              "QMenu::item{padding:0px 40px 0px 30px;height:25px}"
                              "QMenu::item:selected{background:lightblue;color:white;}"
                              "QMenu::separator{height:1px ;background:lightgray;margin:5px,0px,5px,0px;}");
    connect(popMenu,&QMenu::triggered,this,&MainWindow::do_menu_triggered);
    //popMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 6){
        List_Item_Form *custom1 = new List_Item_Form(NULL);
        QListWidgetItem *listItem1 = new QListWidgetItem();
        listItem1->setSizeHint(QSize(0, 71));
        ui->listWidget->addItem(listItem1);
        ui->listWidget->setItemWidget(listItem1, custom1);
        connect(custom1,List_Item_Form::list_item_form_close,this,do_list_item_form_close);
        connect(custom1,List_Item_Form::name_Changed,this,do_name_Changed);
        ui->tabWidget->setCurrentIndex(4);
        return ;
    }
    int n = ui->listWidget->count();
    for(int i = 0 ; i < n ; ++i){
        List_Item_Form *pp = (List_Item_Form *)ui->listWidget->itemWidget( ui->listWidget->item(i));
        int flg_recent_birth = 0;
        if(index == 5){
            QDate birth_1 = QDate::currentDate();
            QDate birth_2 = birth_1.addDays(7);
            QDate birth(birth_1.year(),pp->p->GetMonth(),pp->p->GetDay());
            if(birth >= birth_1 && birth <= birth_2){
                flg_recent_birth = 1;
            }
        }
        ui->listWidget->item(i)->setHidden(
                    !((((pp->p->GetType()) == Person::type_Relative && index == 0) ||
                    ((pp->p->GetType()) ==  Person::type_Friend && index == 1) ||
                    ((pp->p->GetType()) ==  Person::type_Colleague && index == 2) ||
                    ((pp->p->GetType()) ==  Person::type_Classmate && index == 3)) || index == 4 || flg_recent_birth)
                     );
    }
}

void MainWindow::do_name_Changed(QString str)
{
    if(!cplist.contains(str)){
        cplist.append(str);
        cplist.sort();
        string_list_model->setStringList(cplist);
    }
}
