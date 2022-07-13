#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QDialog
{
    Q_OBJECT

public:
    mainwindow(Database db, QWidget *parent = nullptr);
    ~mainwindow();

private slots:
    void on_user_btn_clicked();

    void on_rent_btn_clicked();

    void on_tour_btn_clicked();

    void on_chat_btn_clicked();

private:
    Ui::mainwindow *ui;
    Database db;
};
#endif // MAINWINDOW_H
