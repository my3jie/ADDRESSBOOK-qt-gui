#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"addressbook.h"
#include<QCompleter>
#include<QStringListModel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_toolMenuButton_clicked();//菜单按钮
    void on_pushButton_2_clicked();//搜索
    void on_pushButton_3_clicked();//关闭
    void on_pushButton_4_clicked();//最小化
    void do_menu_triggered(QAction *action);        //响应按钮菜单信号
    void do_list_item_form_close(Person * );        //响应删除信号
    void on_tabWidget_currentChanged(int index);    //响应Tab控件，
    void do_name_Changed(QString str);//响应名字更改消息
private:
    Ui::MainWindow *ui;    
protected:
    //下面用于实现按住标题栏进行拖动的功能
    QPoint last;
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    //创建菜单
    QMenu *popMenu;
    void createPopMenu();
    //自动补全单词列表
    QStringList cplist;
    QCompleter * cp;
    QStringListModel *string_list_model;
};

#endif // MAINWINDOW_H
