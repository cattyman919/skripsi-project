#include "app_qt/todo_auth.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  todo_auth w;
  w.show();
  return a.exec();
}
