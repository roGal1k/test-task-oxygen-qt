#include "dialog.cpp"

///
/// \brief Dialog::insertrow
/// \param label
/// \param name
/// \param check
/// \param deleterrr
///
void Dialog::insertrow(QLabel *label, QString *name, QCheckBox *check, QWidget *deleterrr)
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setMouseTracking(true);

    check->setChecked(true);
    check->setStyleSheet(checkBOX());
    check->setCursor(Qt::PointingHandCursor);
    QWidget *checkBoxWidget = new QWidget();
    QHBoxLayout *layoutCheckBox = new QHBoxLayout(checkBoxWidget);
    layoutCheckBox->addWidget(check);
    layoutCheckBox->setAlignment(Qt::AlignCenter);
    layoutCheckBox->setContentsMargins(3,0,0,0);
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,0, checkBoxWidget);

    QPixmap pixmap(16,16);
    QPainter painter;
    painter.begin(&pixmap);
    painter.drawRect(0,0,16,16);
    painter.fillRect(0,0,16,16,QColor(qrand()%255,qrand()%255,qrand()%255,255));
    painter.end();
    label->setPixmap(pixmap);
    label->setCursor(Qt::PointingHandCursor);
    label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,3, label);

    QTableWidgetItem buf;
    buf.setText(*name);
    buf.setIcon(QIcon(":/new/icon/icon/persoanl.png"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(buf));

    delete_button.last()->setStyleSheet(BUTTON_STYLESHEET_TEMPLATE("trash.png", "trash.png", "trash.png"));
    delete_button.last()->setToolTip ("Удалить список");
    QHBoxLayout *layoutPB = new QHBoxLayout(deleterrr);
    layoutPB->addWidget(delete_button.last());
    layoutPB->setAlignment(Qt::AlignCenter);
    layoutPB->setContentsMargins(0,0,0,0);
    delete_button.last()->setVisible(false);
    delete_button.last()->installEventFilter(this);
    delete_button.last()->setCursor(Qt::PointingHandCursor);
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,2, deleterrr);
    deleterrr->setMouseTracking(true);
}

///
/// \brief Dialog::deleterow
///
void Dialog::deleterow()
{
    int row = 0;
    for(int i=0; i<delete_button.size();i++)
    {
        if (delete_button[i]->isVisible())
        {
            row = i;
            labelWidget.removeAt(row);
            checkBoxWidget.removeAt(row);
            delete_button_widget.removeAt(row);
            delete_button.removeAt(row);
            name.removeAt(row);

            ui->tableWidget->removeRow(row);
            if( ui->tableWidget->maximumSize().height()+64<this->size().height()-80)
            {
                ui->tableWidget->setMaximumHeight((ui->tableWidget->rowCount())*30+2);
                ui->tableWidget->setMinimumHeight((ui->tableWidget->rowCount())*30+2);
                ui->tableWidget_2->setMaximumHeight((ui->tableWidget->rowCount())*30+2);
                ui->tableWidget_2->setMinimumHeight((ui->tableWidget->rowCount())*30+2);
            }
            ui->tableWidget_2->setMaximumHeight((ui->tableWidget->rowCount())*30+2);
            ui->tableWidget_2->setMinimumHeight((ui->tableWidget->rowCount())*30+2);

            this->setFocus();
        }
    }
}
