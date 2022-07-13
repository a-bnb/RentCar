#include "tour_add.h"
#include "ui_tour_add.h"

tour_add::tour_add(Database db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tour_add),
    db(db)
{
    ui->setupUi(this);
    name="";
}

tour_add::tour_add(QString name, Database db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tour_add),
    db(db),
    name(name)
{
    ui->setupUi(this);
    edit_set();
}

tour_add::~tour_add()
{
    delete ui;
}

void tour_add::edit_set()
{
    ui->name_text->setText(name);
    sprintf(query, "SELECT content_addr, content_type FROM content where content_name='%s'", name.toLocal8Bit().data());
    sql_query.exec(QString::fromLocal8Bit(query));
    if(sql_query.size() != 0)
    {
        sql_query.next();
        ui->addr_text->setText(sql_query.value(0).toString());
        ui->type_box->setCurrentIndex(ui->type_box->findText(sql_query.value(1).toString()));
    }
    else
    {
        this->close();
    }
}

void tour_add::on_check_btn_clicked()
{
    QString check_text = ui->name_text->text();
    if(check_text == "")
    {
        QMessageBox::information(this, "error", "공백");
        return;
    }
    sprintf(query, "SELECT * FROM content where content_name = '%s'", check_text.toLocal8Bit().data());
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

void tour_add::on_update_btn_clicked()
{
    QList<QString> tour_list;
    tour_list.append(ui->type_box->currentText());
    tour_list.append(ui->name_text->text());
    tour_list.append(ui->addr_text->text());


    if(name == tour_list.value(1))
        check=true;

    if(!check)
    {
        QMessageBox::information(this, "error", "중복확인");
        return;
    }

    for(int i=1; i<tour_list.length(); i++)
    {
        if(tour_list.value(i) == "")
            tour_list.value(i) = "0";
    }

    if(tour_list.value(0) != "")
    {
        if(name =="")
        {
            sprintf(query, "INSERT INTO content VALUES('%s','%s','%s')",
                    tour_list.value(0).toLocal8Bit().data(),tour_list.value(1).toLocal8Bit().data(),
                    tour_list.value(2).toLocal8Bit().data());
        }
        else
        {
            sprintf(query, "UPDATE content SET content_type='%s', content_name='%s', content_addr='%s' WHERE content_name='%s'",
                    tour_list.value(0).toLocal8Bit().data(),tour_list.value(1).toLocal8Bit().data(),
                    tour_list.value(2).toLocal8Bit().data(), name.toLocal8Bit().data());
        }
        sql_query.exec(QString::fromLocal8Bit(query));
        if(sql_query.lastError().type() != QSqlError::NoError)
        {
            QMessageBox::information(this, "error", "데이터베이스 접근 오류");

        }
        else
        {
            QMessageBox::information(this, "", ui->update_btn->text()+" 성공");
            this->close();
        }
    }
}

void tour_add::on_exit_btn_clicked()
{
    this->close();
}
