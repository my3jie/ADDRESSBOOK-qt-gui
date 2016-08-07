#ifndef INFO_FORM_H
#define INFO_FORM_H

#include <QWidget>
#include "person.h"
namespace Ui {
class Info_Form;
}

class Info_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Info_Form(Person *pitem,QWidget *parent = 0);
    ~Info_Form();
    //设置控件的编辑模式和显示模式
    void Set_Edit_State(bool state);
private slots:
    void on_pushButton_clicked();//进入编辑模式
    void on_pushButton_2_clicked();//保存信息
    void on_pushButton_5_clicked();//选择头像
    void on_pushButton_3_clicked();//取消编辑
    void on_dateEdit_dateChanged(const QDate &date);//日期选择改变，用来改变Label变量的显示的文本

signals:
    void avastar_changed(QString des);//头像改变信号
    void name_changed(QString des);//名字改变信号
    void phone_changed(QString des);//电话改变信号
    void p_addr_changed(Person *_p);//类型改变信号
    void birth_changed(QDate *);//生日改变信号
    void delete_Item();//名字为空，删除项目
private:
    Ui::Info_Form *ui;
    Person *p;//关联的数据的地址
    QString avastar_path;//联系的地址
protected:
    //关闭前，判断是否为空，确定是否删除项目
    virtual void closeEvent(QCloseEvent *event);
};

#endif // INFO_FORM_H
