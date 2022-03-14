#include "dialog.h"
#include "ui_dialog.h"

#include <math.h>
#include <QCheckBox>

#include <QComboBox>
#include <QTableWidgetItem>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);

    this->setMouseTracking(true);
    this->installEventFilter(this);

    ui->tableWidget->setMouseTracking(true);
    ui->tableWidget->installEventFilter(this);
    ui->tableWidget->viewport()->installEventFilter(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setMaximumHeight((ui->tableWidget->rowCount())*30+2);
    ui->tableWidget->setMinimumHeight((ui->tableWidget->rowCount())*30+2);
    ui->tableWidget->setShowGrid(false);

    ui->textEdit->installEventFilter(this);
    ui->textEdit->setVisible(false);
    ui->textEdit->setStyleSheet("QTextEdit{background-color: none; border: none; height: 0px; max-height:0px;}");

    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_2->setMaximumHeight((ui->tableWidget->rowCount())*30+2);
    ui->tableWidget_2->setMinimumHeight((ui->tableWidget->rowCount())*30+2);

    ui->export_2->setDisabled(true);

}

///
/// \brief addButton's slot
///
void Dialog::on_addButton_clicked()
{
    ui->textEdit->clear();
    ui->addButton->setStyleSheet(buadd1());
    ui->textEdit->setDisabled(false);
    ui->textEdit->setFocus();
    ui->textEdit->setVisible(true);
    ui->textEdit->setStyleSheet(LE());
    ui->label->setVisible(false);
}

///
/// \brief Dialog::on_pushButton_clicked
///
void Dialog::on_closeButton_clicked()
{
    this->close();
}

///
/// \brief Dialog::eventFilter
/// \param watched - the object on which the cursor is hovering
/// \param event - the event captured by the element
/// \return eventFilter
///
bool Dialog::eventFilter(QObject *watched, QEvent *event)
{
    QModelIndex hover = ui->tableWidget->indexAt(ui->tableWidget->viewport()->mapFromGlobal(QCursor::pos()));
    if(watched == ui->tableWidget->viewport())
    {
        if (hover.row()>-1 && hover.row()<ui->tableWidget->rowCount())
        {
            delete_button.at(hover.row())->setVisible(true);
            connect(delete_button.at(hover.row()),SIGNAL(clicked()),this,SLOT(deleterow()));
            checkBoxWidget.at(hover.row())->setStyleSheet(checkBOX1());
            connect(checkBoxWidget.at(hover.row()),SIGNAL(clicked()),this,SLOT(disactive()));
            if (ui->tableWidget->rowCount()>1)
            {
                if (hover.row()==0 && ui->tableWidget->rowCount()>1)
                {
                    delete_button.at(hover.row()+1)->setVisible(false);
                    checkBoxWidget.at(hover.row()+1)->setStyleSheet(checkBOX());
                }
                else if (hover.row()==ui->tableWidget->rowCount()-1 && ui->tableWidget->rowCount()>1)
                {
                    delete_button.at(hover.row()-1)->setVisible(false);
                    checkBoxWidget.at(hover.row()-1)->setStyleSheet(checkBOX());
                }
                else
                {
                    checkBoxWidget.at(hover.row()-1)->setStyleSheet(checkBOX());
                    checkBoxWidget.at(hover.row()+1)->setStyleSheet(checkBOX());
                    delete_button.at(hover.row()-1)->setVisible(false);
                    delete_button.at(hover.row()+1)->setVisible(false);
                }
            }
        }
    }
    else if(watched == ui->textEdit)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if((event->type() == QEvent::KeyPress) &&
              ((keyEvent->key() == Qt::Key_Return|| keyEvent->key() == Qt::Key_Enter) &&
               (!ui->textEdit->toPlainText().isEmpty())))
            {
                labelWidget.push_back(new QLabel());
                checkBoxWidget.push_back(new QCheckBox());
                labelWidget.push_back(new QLabel());
                delete_button.push_back(new QPushButton());
                delete_button_widget.push_back(new QWidget());
                name.push_back(new QString(ui->textEdit->toPlainText()));
                insertrow(labelWidget.last(),name.last(),checkBoxWidget.last(), delete_button_widget.last());
                if(ui->tableWidget->maximumSize().height()+64<this->size().height()-80)
                {
                    ui->tableWidget->setMaximumHeight((ui->tableWidget->rowCount())*30+2);
                    ui->tableWidget->setMinimumHeight((ui->tableWidget->rowCount())*30+2);
                    ui->tableWidget_2->setMaximumHeight((ui->tableWidget->rowCount())*30+2);
                    ui->tableWidget_2->setMinimumHeight((ui->tableWidget->rowCount())*30+2);
                }
                this->setFocus();
                ui->textEdit->clear();
                ui->textEdit->setStyleSheet(LEnone());
                ui->textEdit->setVisible(false);
                ui->addButton->setStyleSheet(buadd0());
                ui->addButton->setVisible(true);
                ui->addButton->setDisabled(false);
                ui->textEdit->clear();
                ui->label->setVisible(true);
            }
        }
        if(event->type() == QEvent::FocusOut)
        {
            ui->textEdit->clear();
            ui->textEdit->setStyleSheet(LEnone());
            ui->textEdit->setVisible(false);
            ui->addButton->setStyleSheet(buadd0());
            ui->addButton->setVisible(true);
            ui->addButton->setDisabled(false);
            ui->textEdit->clear();
            ui->label->setVisible(true);
        }
    }
    else if(event->type() == QEvent::MouseButtonPress)
    {
        ui->tableWidget->clearSelection();
        ui->tableWidget_2->removeRow(0);
        this->setFocus();
        ui->export_2->setDisabled(true);
    }
    if (ind!=-1 && ind != hover.row() && hover.row()==-1)
    {
        for (int i=0; i<delete_button.size(); i++)
        {
            checkBoxWidget.at(i)->setStyleSheet(checkBOX());
            delete_button.at(i)->setVisible(false);
        }
    }
    ind=hover.row();
    return QDialog::eventFilter(watched, event);
}

///
/// \brief Dialog::on_tableWidget_cellPressed
///
void Dialog::on_tableWidget_cellPressed(int, int)
{
     ui->export_2->setDisabled(false);
     if(ui->tableWidget_2->rowCount()!=1)
     {
        ui->tableWidget_2->insertRow(0);
        ui->tableWidget_2->setItem(0,0,new QTableWidgetItem("Введите новое ключевое слово"));
        ui->tableWidget_2->item(0,0)->setTextColor(Qt::blue);
     }
}

///
/// \brief Dialog::on_startedButton_clicked
///
void Dialog::on_startedButton_clicked()
{
    ui->tableWidget->clearSelection();
    while(ui->tableWidget->rowCount()!=0)
    {
        checkBoxWidget.removeAt(ui->tableWidget->rowCount()-1);
        name.removeAt(ui->tableWidget->rowCount()-1);
        delete_button.removeAt(ui->tableWidget->rowCount()-1);
        delete_button_widget.removeAt(ui->tableWidget->rowCount()-1);
        ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
        ui->tableWidget->setMaximumHeight((ui->tableWidget->rowCount())*30+2);
        ui->tableWidget->setMinimumHeight((ui->tableWidget->rowCount())*30+2);
    }
}

void Dialog::disactive()
{
    ui->allChecked->setChecked(false);
}

///
/// \brief Dialog::on_allChecked_clicked
///
void Dialog::on_allChecked_clicked()
{
    for(int i=0; i<checkBoxWidget.size();i++)
    {
        checkBoxWidget[i]->setChecked(ui->allChecked->checkState());
    }
}

Dialog::~Dialog()
{
    delete ui;
}
