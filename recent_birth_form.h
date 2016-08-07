#ifndef RECENT_BIRTH_FORM_H
#define RECENT_BIRTH_FORM_H

#include <QWidget>
#include"person.h"
namespace Ui {
class recent_birth_form;
}

class recent_birth_form : public QWidget
{
    Q_OBJECT

public:
    explicit recent_birth_form(QWidget *parent = 0);
    ~recent_birth_form();
private slots:
    void do_list_item_form_close(Person * p);
private:
    Ui::recent_birth_form *ui;
};

#endif // RECENT_BIRTH_FORM_H
