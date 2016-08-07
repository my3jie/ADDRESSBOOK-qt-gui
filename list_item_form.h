#ifndef LIST_ITEM_FORM_H
#define LIST_ITEM_FORM_H

#include <QWidget>
#include<string>
#include"person.h"
#include"friend.h"
namespace Ui {
class List_Item_Form;
}

class List_Item_Form : public QWidget
{
    Q_OBJECT

public:
    explicit List_Item_Form(Person *pitem, QWidget *parent = 0);
    ~List_Item_Form();
signals :
    void list_item_form_close(Person *);//给主窗口发出关闭信号
    void name_Changed(QString str);//给主窗口发送名字更改/增加信号，用以自动补全功能的更新
public slots:
    void on_toolButton_clicked();//查看详细信息
    void on_toolButton_2_clicked();//删除信息
    void on_toolButton_3_clicked();//生成祝贺文本
    void do_avastar_changed(QString);//响应头像改变信号
    void do_name_changed(QString);//响应名字改变信号
    void do_phone_changed(QString);//响应电话号码改变信号
    void do_p_addr_changed(Person* _p);//响应联系人类型 改变信号
    void do_delete_Item();//响应删除信号
    void do_birth_changed(QDate *birth);//响应生日改变信号
private:
    Ui::List_Item_Form *ui;
protected:
    //用来鼠标移入显示按钮，移出隐藏按钮
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
public:
    Person *p;//关联的数据变量
    bool flg_recent_birth;//标记是否最近生日
private slots:


    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *);
};

#endif // LIST_ITEM_FORM_H
