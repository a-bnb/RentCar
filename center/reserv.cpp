#include "reserv.h"
#include "ui_reserv.h"
#include "reserv_add.h"

reserv::reserv(Database db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reserv),
    db(db)
{
    ui->setupUi(this);
}

reserv::~reserv()
{
    delete ui;
}

void reserv::on_refresh_btn_clicked()
{
    int i, column, line=0;
    QString temp;
    ui->table->clearContents();
    sprintf(query, "SELECT * FROM reserv");
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

void reserv::on_add_btn_clicked()
{
    reserv_add window(db);
    window.setModal(true);
    window.exec();
    this->on_refresh_btn_clicked();
}

void reserv::on_remove_btn_clicked()
{
    int row;
    if(check==true)
        row = ui->table->currentRow();
    else
        return;

    QString id = ui->table->takeItem(row, 1)->text();
    sprintf(query, "DELETE FROM reserv WHERE reserv_id ='%s'", id.toLocal8Bit().data());
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

void reserv::on_edit_btn_clicked()
{
    int row;
    if(check==true)
        row = ui->table->currentRow();
    else
        return;

    QString name = ui->table->takeItem(row, 1)->text();
    check = false;
    reserv_add window(name, db);
    window.setModal(true);
    window.exec();
    this->on_refresh_btn_clicked();
}

void reserv::on_exit_btn_clicked()
{
    this->close();
}

void reserv::on_table_itemClicked()
{
    check=true;
}
