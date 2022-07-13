#include "car.h"
#include "ui_car.h"
#include "car_add.h"
#include "reserv.h"

car::car(Database db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::car),
    db(db)
{
    ui->setupUi(this);
    this->on_refresh_btn_clicked();
}

car::~car()
{
    delete ui;
}

void car::on_refresh_btn_clicked()
{
    int i, column, line=0;
    QString temp;
    ui->table->clearContents();
    sprintf(query, "SELECT * FROM Car ORDER BY Car_model");
    sql_query.exec(QString::fromLocal8Bit(query));
    column = sql_query.record().count();
    ui->table->setRowCount(sql_query.size());
    ui->table->setColumnCount(column);
    if(sql_query.size() != 0)
    {
        while(sql_query.next())
        {
            for(i=0; i<column; i++)
            {
                ui->table->setItem(line, i, new QTableWidgetItem(sql_query.value(i).toString()));
            }
            line++;
        }
        ui->table->show();
    }

}

void car::on_add_btn_clicked()
{
    car_add window(db);
    window.setModal(true);
    window.exec();
    this->on_refresh_btn_clicked();
}

void car::on_remove_btn_clicked()
{
    int row;
    if(check==true)
        row = ui->table->currentRow();
    else
        return;

    QString model = ui->table->takeItem(row, 0)->text();
    sprintf(query, "DELETE FROM Car WHERE Car_name ='%s'", model.toLocal8Bit().data());
    sql_query.exec(QString::fromLocal8Bit(query));
    if(sql_query.lastError().type() == QSqlError::NoError)
    {
        QMessageBox::information(this, "message", "Delete Complete!");
        ui->table->removeRow(row);
    }
    else
    {
        QMessageBox::information(this, "error", "삭제 실패");
    }
    check = false;
}

void car::on_edit_btn_clicked()
{
    int row;
    if(check==true)
        row = ui->table->currentRow();
    else
        return;

    QString model = ui->table->takeItem(row, 0)->text();
    check = false;
    car_add window(model, db);
    window.setModal(true);
    window.exec();
    this->on_refresh_btn_clicked();
}

void car::on_reserv_btn_clicked()
{
    reserv window(db);
    window.setModal(true);
    window.exec();
}

void car::on_exit_btn_clicked()
{
    this->close();
}

void car::on_table_itemClicked()
{
    check=true;
}
