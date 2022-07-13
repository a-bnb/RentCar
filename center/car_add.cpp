#include "car_add.h"
#include "ui_car_add.h"

car_add::car_add(Database db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::car_add),
    db(db)
{
    ui->setupUi(this);
    model="";
}

car_add::car_add(QString model, Database db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::car_add),
    db(db),
    model(model)
{
    ui->setupUi(this);
    this->edit_set();
}

car_add::~car_add()
{
    delete ui;
}

void car_add::edit_set()
{
    ui->name_text->setText(model);
    sprintf(query, "SELECT * FROM Car WHERE Car_model='%s'", model.toLocal8Bit().data());
    sql_query.exec(QString::fromLocal8Bit(query));
    if(sql_query.size() != 0)
    {
        sql_query.next();
        ui->price_text->setText(sql_query.value(1).toString());
        ui->stock_text->setText(sql_query.value(3).toString());
        ui->type_box->setCurrentIndex(ui->type_box->findText(sql_query.value(2).toString()));
    }
    else
    {
        this->close();
    }
}

void car_add::on_check_btn_clicked()
{
    QString check_text = ui->name_text->text();
    if(check_text == "")
    {
        QMessageBox::information(this, "error", "공백");
        return;
    }
    sprintf(query, "SELECT * FROM Car WHERE Car_name='%s'", check_text.toLocal8Bit().data());
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

void car_add::on_update_btn_clicked()
{
    QList<QString> tour_list;
    tour_list.append(ui->name_text->text());
    tour_list.append(ui->price_text->text());
    tour_list.append(ui->type_box->currentText());
    tour_list.append(ui->stock_text->text());


    if(model == tour_list.value(0))
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
        if(model =="")
        {
            sprintf(query, "INSERT INTO Car VALUES('%s',%s,'%s','%s')",
                    tour_list.value(0).toLocal8Bit().data(),tour_list.value(1).toLocal8Bit().data(),
                    tour_list.value(2).toLocal8Bit().data(), tour_list.value(3).toLocal8Bit().data());
        }
        else
        {
            sprintf(query, "UPDATE Car SET Car_model='%s', Car_price=%s, oil_type='%s', Car_stock=%s WHERE Car_name='%s'",
                    tour_list.value(0).toLocal8Bit().data(),tour_list.value(1).toLocal8Bit().data(),
                    tour_list.value(2).toLocal8Bit().data(), tour_list.value(3).toLocal8Bit().data(),
                    model.toLocal8Bit().data());
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


void car_add::on_exit_btn_clicked()
{
    this->close();
}
