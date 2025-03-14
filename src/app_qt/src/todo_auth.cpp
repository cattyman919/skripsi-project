#include <QLibrary>
#include <QMessageBox>

#include "app_qt/todo_auth.h"
#include "ui_todo_auth.h"

#include "vxlang/vxlib.h"

#ifndef _WIN64
#pragma comment(lib, "vxlib32.lib")
#else
#pragma comment(lib, "vxlib64.lib")
#endif

todo_auth::todo_auth(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::todo_auth) {
  ui->setupUi(this);
}

todo_auth::~todo_auth() { delete ui; }

void todo_auth::on_button_login_clicked() {
  VL_VIRTUALIZATION_BEGIN;

  QString username = ui->input_User->text();
  QString password = ui->input_Pass->text();

  if (username.isEmpty() || password.isEmpty()) {
    QMessageBox::critical(this, "Error",
                          "Username and Password cannot be empty");
    return;
  }

  if (username == "seno" && password == "rahman") {
    QMessageBox::information(this, "Login", "Authentication Sucess");
    hide();
    toDo = new todo();
    toDo->show();
  } else {
    QMessageBox::critical(this, "Login", "Authentication Failed");
  }

  VL_VIRTUALIZATION_END;
}
