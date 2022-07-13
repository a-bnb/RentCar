#include "reserv_add.h"
#include "ui_reserv_add.h"

reserv_add::reserv_add(Database db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reserv_add),
    db(db)
{
    ui->setupUi(this);
    this->on_refresh_btn_clicked();
    this->id="";
}

reserv_add::reserv_add(QString id, Database db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reserv_add),
    db(db),
    id(id)
{
    ui->setupUi(this);
    this->on_refresh_btn_clicked();
    this->edit_set();
}


reserv_add::~reserv_add()
{
    delete ui;
}

void reserv_add::edit_set()
{
    ui->ID_text->setText(id);
    sprintf(query, "SELECT * FROM reserv WHERE reserv_id=%s", id.toLocal8Bit().data());
    sql_query.exec(QString::fromLocal8Bit(query));
    if(sql_query.size() != 0)
    {
        sql_query.next();
        ui->model_text->setText(sql_query.value(1).toString());
        ui->rent_text->setText(sql_query.value(2).toString());
        ui->return_text->setText(sql_query.value(3).toString());
        ui->price_text->setText(sql_query.value(4).toString());
    }
    else
    {
        this->close();
    }

}

void reserv_add::on_refresh_btn_clicked()
{
    int line=0;
    ui->ID_text->clear();
    ui->model_text->clear();
    ui->rent_text->clear();
    ui->return_text->clear();
    ui->price_text->clear();
    ui->user_table->clearContents();
    ui->Car_table->clearContents();

    sprintf(query, "SELECT userid FROM user");
    sql_query.exec(QString::fromLocal8Bit(query));
    ui->user_table->setRowCount(sql_query.size());
    if(sql_query.size() != 0)
    {
        while(sql_query.next())
        {
            ui->user_table->setItem(line++, 0, new QTableWidgetItem(sql_query.value(0).toString()));
        }
        line=0;
    }
    else
        return;
    ui->user_table->show();

    sprintf(query, "SELECT Car_model FROM Car WHERE Car_stock>0");
    sql_query.exec(QString::fromLocal8Bit(query));
    ui->Car_table->setRowCount(sql_query.size());
    if(sql_query.size() != 0)
    {
        while(sql_query.next())
        {
            ui->Car_table->setItem(line++, 0, new QTableWidgetItem(sql_query.value(0).toString()));
        }
        line=0;
    }
    else
        return;
    ui->Car_table->show();

}

void reserv_add::on_add_btn_clicked()
{
    QList<QString> reserv_list;
    reserv_list.append(ui->ID_text->text());
    reserv_list.append(ui->model_text->text());
    reserv_list.append(ui->rent_text->text());
    reserv_list.append(ui->return_text->text());
    reserv_list.append(ui->price_text->text());

    if(id=="")
    {
        sprintf(query, "INSERT INTO reserv(client_id, Car_model, rental_date, return_date, reserv_price) VALUES('%s', '%s', '%s', '%s', '%s')",
                reserv_list.value(0).toLocal8Bit().data(),reserv_list.value(1).toLocal8Bit().data(),
                reserv_list.value(2).toLocal8Bit().data(),reserv_list.value(3).toLocal8Bit().data(),
                reserv_list.value(4).toLocal8Bit().data());
    }
    else
    {
        sprintf(query, "UPDATE resrv SET  client_id='%s', Car_model='%s', rental_date='%s', return_date='%s', reserv_price='%s' WHERE reserv_id=%s",
                reserv_list.value(0).toLocal8Bit().data(),reserv_list.value(1).toLocal8Bit().data(),
                reserv_list.value(2).toLocal8Bit().data(),reserv_list.value(3).toLocal8Bit().data(),
                reserv_list.value(4).toLocal8Bit().data(),id.toLocal8Bit().data());
    }
    sql_query.exec(QString::fromLocal8Bit(query));
    if(sql_query.lastError().type() != QSqlError::NoError)
    {
        QMessageBox::information(this, "error", "데이터베이스 접근 오류");
        std::cout<<sql_query.lastError().text().toStdString()<<std::endl;
    }
    else
    {
        QMessageBox::information(this,"message", ui->add_btn->text()+" 완료");
        this->close();
    }
}

void reserv_add::on_calendar_clicked(const QDate &date)
{
    if(ui->model_text->text()=="")
        return;
    if(ui->price_text->text()!="")
        return;
    int diff;
    if(ui->rent_text->text()=="")
        ui->rent_text->setText(date.toString());
    else if(ui->return_text->text()=="")
    {
        diff = date.daysTo(QDate::fromString(ui->rent_text->text()));
        std::cout<<diff<<std::endl;
        diff = diff*price_base*-1;
        std::cout<<diff<<std::endl;
        ui->price_text->setText(QString::number(diff));
        ui->return_text->setText(date.toString());
    }

}

void reserv_add::on_Car_table_itemClicked(QTableWidgetItem *item)
{
    if(ui->ID_text->text()=="")
        return;
    if(ui->price_text->text()!="")
        return;
    sprintf(query, "SELECT Car_price FROM Car WHERE Car_model='%s'", item->text().toLocal8Bit().data());
    sql_query.exec(QString::fromLocal8Bit(query));
    if(sql_query.size() != 0)
    {
        sql_query.next();
        std::cout<<sql_query.value(0).toString().toStdString()<<std::endl;
        price_base=sql_query.value(0).toInt();
        std::cout<<price_base<<std::endl;
        ui->model_text->setText(item->text());
    }
    else
        return;
}

void reserv_add::on_user_table_itemClicked(QTableWidgetItem *item)
{
    ui->ID_text->setText(item->text());
}

void reserv_add::on_exit_btn_clicked()
{
    this->close();
}
