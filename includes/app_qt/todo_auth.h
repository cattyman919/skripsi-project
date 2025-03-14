#ifndef TODO_AUTH_H
#define TODO_AUTH_H

#include <QMainWindow>
#include "todo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class todo_auth;
}
QT_END_NAMESPACE

class todo_auth : public QMainWindow
{
    Q_OBJECT

public:
    todo_auth(QWidget *parent = nullptr);
    ~todo_auth();

private slots:
    void on_button_login_clicked();

private:
    Ui::todo_auth *ui;
    todo *toDo;
};
#endif // TODO_AUTH_H
