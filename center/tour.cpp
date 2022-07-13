#include "tour.h"
#include "ui_tour.h"
#include "tour_add.h"

tour::tour(Database db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tour),
    db(db)
{
    ui->setupUi(this);
    this->on_refresh_btn_clicked();
}

tour::~tour()
{
    delete ui;
}

void tour::on_refresh_btn_clicked()
{
    int i, column, line=0;
    QString temp;
    ui->table->clearContents();
    sprintf(query, "SELECT * FROM content ORDER BY content_type");
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

void tour::on_add_btn_clicked()
{
    tour_add window(db);
    window.setModal(true);
    window.exec();
    this->on_refresh_btn_clicked();

}



void tour::on_remove_btn_clicked()
{
    int row;
    if(check==true)
        row = ui->table->currentRow();
    else
        return;

    QString name = ui->table->takeItem(row, 1)->text();
    sprintf(query, "DELETE FROM content WHERE content_name='%s'", name.toLocal8Bit().data());
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

void tour::on_table_itemClicked()
{
    check=true;
}

void tour::on_edit_btn_clicked()
{
    int row;
    if(check==true)
        row = ui->table->currentRow();
    else
        return;

    QString name = ui->table->takeItem(row, 1)->text();
    check = false;
    tour_add window(name, db);
    window.setModal(true);
    window.exec();
    this->on_refresh_btn_clicked();
}

void tour::on_exit_btn_clicked()
{
    this->close();
}
