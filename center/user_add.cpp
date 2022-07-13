#include "user_add.h"
#include "ui_user_add.h"
#include <iostream>

user_add::user_add(Database dbs, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_add),
    db(dbs)
{
    ui->setupUi(this);
    this->u_id = "";
}

user_add::user_add(QString u_id, Database dbs, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_add),
    db(dbs),
    u_id(u_id)
{
    ui->setupUi(this);
    edit_set();
}

user_add::~user_add()
{
    delete ui;
}

void user_add::edit_set()
{
    ui->ID_text->setText(u_id);
    sprintf(query, "SELECT userpw, username, usertype FROM user WHERE userid = '%s'", u_id.toLocal8Bit().data());
    sql_query.exec(QString::fromLocal8Bit(query));
    if(sql_query.size() != 0)
    {
        sql_query.next();
        ui->PW_text->setText(sql_query.value(0).toString());
        ui->PW2_text->setText(sql_query.value(0).toString());
        ui->Name_text->setText(sql_query.value(1).toString());
        ui->class_box->setCurrentIndex(ui->class_box->findText(sql_query.value(2).toString()));

        ui->signup_btn->setText("회원정보 수정");
    }
    else
    {
        this->close();
    }
}

void user_add::on_check_btn_clicked()
{
    QString id = ui->ID_text->text();
    if(id == "")
    {
        QMessageBox::information(this, "error", "공백");
        return;
    }
    sprintf(query, "SELECT * FROM user WHERE userid = '%s'", id.toLocal8Bit().data());
    sql_query.exec(QString::fromLocal8Bit(query));
    if(sql_query.size() == 0)
    {
        check = true;
        QMessageBox::information(this, "OK", "통과");
    }
    else
    {
        QMessageBox::information(this, "error", "중복");
    }
}



void user_add::on_signup_btn_clicked()
{
    QString id = ui->ID_text->text();
    QString pw = ui->PW_text->text();
    QString name = ui->Name_text->text();
    QString type = ui->class_box->currentText();

    std::cout<<this->u_id.toStdString()+"\n"<<id.toStdString()<<std::endl;
    if(this->u_id == id)
        check=true;
    if(!check)
    {
        QMessageBox::information(this, "error", "중복확인");
        return;
    }


    if(pw == "" || name == "")
        QMessageBox::information(this, "error", "공백");
    else
    {
        if(ui->PW_text->text() != ui->PW2_text->text())
            QMessageBox::information(this, "error", "비밀번호 불일치");
        else
        {
            if(u_id=="")
            {
                sprintf(query, "INSERT INTO user(userid, userpw, username, usertype) VALUES('%s','%s','%s','%s')",
                        id.toLocal8Bit().data(), pw.toLocal8Bit().data(), name.toLocal8Bit().data(), type.toLocal8Bit().data());
            }
            else
            {
                sprintf(query, "UPDATE user SET userid = '%s', userpw='%s', username='%s', usertype='%s' WHERE userid='%s'",
                         id.toLocal8Bit().data(), pw.toLocal8Bit().data(), name.toLocal8Bit().data(), type.toLocal8Bit().data(), u_id.toLocal8Bit().data());
            }
            sql_query.exec(QString::fromLocal8Bit(query));
            if(sql_query.lastError().type() != QSqlError::NoError)
            {
                QMessageBox::information(this, "error", "데이터베이스 접근 오류");
            }
            else
            {

                QMessageBox::information(this, "축", ui->signup_btn->text()+" 성공");

                this->close();
            }

        }
    }
}


void user_add::on_exit_btn_clicked()
{
    this->close();
}
