#include "app_qt/todo.h"
#include "ui_todo.h"
#include <QMessageBox>

todo::todo(QWidget *parent) : QDialog(parent), ui(new Ui::todo) {
  ui->setupUi(this);
  ui->list_task->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

todo::~todo() { delete ui; }

void todo::on_button_add_clicked() {
  QString task = ui->input_task->text();

  if (task.isEmpty()) {
    QMessageBox::critical(this, "Error", "Task cannot be empty");
    return;
  }

  QListWidgetItem *item = new QListWidgetItem(task);
  ui->list_task->addItem(item);

  ui->input_task->clear();
}

void todo::on_button_delete_clicked() {
  QList<QListWidgetItem *> selected = ui->list_task->selectedItems();
  if (selected.size() <= 0) {
    QMessageBox::critical(this, "Error",
                          "Please Select at least 1 task for deletion");
    return;
  }
  qDeleteAll(ui->list_task->selectedItems());
}
