#ifndef TODO_H
#define TODO_H

#include <QDialog>
#include <qlistwidget.h>

namespace Ui {
class todo;
}

class todo : public QDialog
{
    Q_OBJECT

public:
    explicit todo(QWidget *parent = nullptr);
    ~todo();

private slots:
    void on_button_add_clicked();

    void on_button_delete_clicked();

private:
    Ui::todo *ui;
    QVector<QListWidgetItem *> oof;
};

#endif // TODO_H
