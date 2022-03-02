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

    this->setMouseTracking(true);

    ui->tableWidget->setMouseTracking(true);
    ui->tableWidget->installEventFilter(this);
    ui->tableWidget->setAttribute(Qt::WA_Hover, true);
    ui->tableWidget->viewport()->installEventFilter(ui->tableWidget);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setAttribute(Qt::WA_Hover);
    ui->tableWidget->setMaximumHeight((ui->tableWidget->rowCount())*30+2);
    ui->tableWidget->setMinimumHeight((ui->tableWidget->rowCount())*30+2);
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->setShowGrid(false);

    ui->lineEdit->installEventFilter(this);
    ui->lineEdit->setVisible(false);
    ui->lineEdit->setStyleSheet("QLineEdit{background-color: none; border: none; height: 0px; max-height:0px;}");
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_2->setMaximumHeight((ui->tableWidget->rowCount())*30+2);
    ui->tableWidget_2->setMinimumHeight((ui->tableWidget->rowCount())*30+2);

    for(int i=0; i<2;i++)
    {
        buts[0]->setStyleSheet(BUTTON_STYLESHEET_TEMPLATE("actived_add.png", "disabled_add.png", "disabled_add.png"));
        buts[0]->setToolTip ("Импорт списка");
        buts[1]->setStyleSheet(BUTTON_STYLESHEET_TEMPLATE("disabled_export.png", "disabled_export.png", "disabled_export.png"));
        buts[1]->setToolTip ("Экспорт списка");
        layoubut[i]->setAlignment(Qt::AlignCenter);
        layoubut[i]->setContentsMargins(0,0,0,0);
        layoubut[i]->addWidget(buts[i]);
        ui->tableWidget->setCellWidget(0,i+2,but[i]);
    }

    QCheckBox *check = new QCheckBox();
    check->setChecked(true);
    QWidget *cbWidget = new QWidget();
    QHBoxLayout *lcBox = new QHBoxLayout(cbWidget);
    lcBox->addWidget(check);
    lcBox->setAlignment(Qt::AlignCenter);
    lcBox->setContentsMargins(0,0,0,0);
    cbWidget->setMouseTracking(true);
    ui->tableWidget->setCellWidget(0,0, cbWidget);

}

void Dialog::insertrow(QLabel *label, QString name, QCheckBox *check, QWidget *deleterrr)
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    check->setChecked(true);
    QWidget *checkBoxWidget = new QWidget();
    QHBoxLayout *layoutCheckBox = new QHBoxLayout(checkBoxWidget);
    layoutCheckBox->addWidget(check);
    layoutCheckBox->setAlignment(Qt::AlignCenter);
    layoutCheckBox->setContentsMargins(0,0,0,0);
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,0, checkBoxWidget);

    QPixmap pixmap(16,16);
    QPainter painter;
    painter.begin(&pixmap);
    painter.drawRect(0,0,16,16);
    painter.fillRect(0,0,16,16,QColor(qrand()%255));
    painter.end();
    label->setPixmap(pixmap);
    label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,3, label);

    QTableWidgetItem buf(name);
    buf.setIcon(QIcon(":/new/icon/icon/persoanl.png"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(buf));

    deleter.last()->setStyleSheet(BUTTON_STYLESHEET_TEMPLATE("trash.png", "trash.png", "trash.png"));
    deleter.last()->setToolTip ("Удалить список");
    QHBoxLayout *layoutPB = new QHBoxLayout(deleterrr);
    layoutPB->addWidget(deleter.last());
    layoutPB->setAlignment(Qt::AlignCenter);
    layoutPB->setContentsMargins(0,0,0,0);
    deleter.last()->setVisible(false);
    deleter.last()->installEventFilter(this);
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,2, deleterrr);

}

void Dialog::deleterow(int row)
{
    labelWidget.removeAt(row);
    checkBoxWidget.removeAt(row);
    deleterrr.removeAt(row);
    deleter.removeAt(row);
    ui->tableWidget->removeRow(row+1);
    if(ui->tableWidget->maximumSize().height()+32<this->size().height()-80)
    {
        ui->tableWidget->setMaximumHeight((ui->tableWidget->rowCount())*30+2+2);
        ui->tableWidget->setMinimumHeight((ui->tableWidget->rowCount())*30+2);
        ui->tableWidget_2->setMaximumHeight((ui->tableWidget->rowCount())*30+2);
        ui->tableWidget_2->setMinimumHeight((ui->tableWidget->rowCount())*30+2);
    }
    ui->tableWidget_2->setMaximumHeight((ui->tableWidget->rowCount())*30+2);
    ui->tableWidget_2->setMinimumHeight((ui->tableWidget->rowCount())*30+2);
}

void Dialog::on_pushButton_3_clicked()
{
    ui->pushButton_3->setStyleSheet(buadd1());
    ui->lineEdit->setStyleSheet("QLineEdit{background-color: rgb(255, 255, 255); border: 1px rgb(0,52,255); height: 25px; max-height: 25px;}");
    ui->lineEdit->setDisabled(false);
    ui->lineEdit->setFocus();
    ui->lineEdit->setVisible(true);
    ui->label->setVisible(false);
}

void Dialog::on_pushButton_clicked()
{
    this->close();
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->tableWidget)
    {
        int c =ui->tableWidget->mapFromGlobal(QCursor::pos()).y();
        c/=30+2;
        qDebug()<<c<<event->type();
        if(event->type() == QEvent::Enter)
        {
            if (ui->tableWidget->rowCount()>1 && c<ui->tableWidget->rowCount())
            {
                if (c==0)
                {
                    deleter.at(c)->setVisible(true);
                    checkBoxWidget.at(c)->setStyleSheet("QCheckBox{color: blue} QCheckBox::indicator{color: blue;}");
                }
                else
                {
                    deleter.at(c-1)->setVisible(true);
                    checkBoxWidget.at(c-1)->setStyleSheet("QCheckBox{color: blue} QCheckBox::indicator{color: blue;}");

                }
            }
            return true;
        }
        else if(event->type() == QEvent::HoverMove)
        {
            // c - корректное значение
            if (c<ui->tableWidget->rowCount() && c>-1)
            {
                //выбран хедер
                if(c==0)
                {
                    if (ui->tableWidget->rowCount()>1)
                    {
                    deleter.at(0)->setVisible(false);
                    checkBoxWidget.at(0)->setStyleSheet("QCheckBox{color: black} QCheckBox::indicator{color: black;}");
                    }


                }
                //выбрана первая
                else if (c==1)
                {
                    deleter.at(c-1)->setVisible(true);
                    checkBoxWidget.at(c-1)->setStyleSheet("QCheckBox{color: blue} QCheckBox::indicator{color: blue;}");
                    if (ui->tableWidget->rowCount()>2)
                        if(deleter.at(c)->isVisible())
                        {
                        deleter.at(c)->setVisible(false);
                        checkBoxWidget.at(c)->setStyleSheet("QCheckBox{color: black} QCheckBox::indicator{color: black;}");
                        }
                }
                //выбрана не первая и не посленяя
                else if(c!=1 && c!=ui->tableWidget->rowCount()-1)
                {
                    deleter.at(c-2)->setVisible(false);
                    checkBoxWidget.at(c-2)->setStyleSheet("QCheckBox{color: black} QCheckBox::indicator{color: black;}");
                    deleter.at(c-1)->setVisible(true);
                    checkBoxWidget.at(c-1)->setStyleSheet("QCheckBox{color: blue} QCheckBox::indicator{color: blue;}");
                    deleter.at(c)->setVisible(false);
                    checkBoxWidget.at(c)->setStyleSheet("QCheckBox{color: black} QCheckBox::indicator{color: black;}");

                }
                //выбрана последняя строка
                else if(c==ui->tableWidget->rowCount()-1)
                {
                    deleter.at(c-2)->setVisible(false);
                    checkBoxWidget.at(c-2)->setStyleSheet("QCheckBox{color: black} QCheckBox::indicator{color: black;}");

                    deleter.at(c-1)->setVisible(true);
                    checkBoxWidget.at(c-1)->setStyleSheet("QCheckBox{color: blue} QCheckBox::indicator{color: blue;}");
                }
            }
            return true;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            if (ui->tableWidget->rowCount()>1)
            {
                deleter.at(0)->setVisible(false);
                checkBoxWidget.at(0)->setStyleSheet("QCheckBox{color: black} QCheckBox::indicator{color: black;}");

            }
            if (ui->tableWidget->rowCount()>2)
            {
                deleter.at(0)->setVisible(false);
                checkBoxWidget.at(0)->setStyleSheet("QCheckBox{color: black} QCheckBox::indicator{color: black;}");

                deleter.at(deleter.size()-1)->setVisible(false);
                checkBoxWidget.at(deleter.size()-1)->setStyleSheet("QCheckBox{color: black} QCheckBox::indicator{color: black;}");
            }
        }
        if(event->type() == QEvent::Leave)
        {
            if (ui->tableWidget->rowCount()>1)
            {
                if (c<ui->tableWidget->rowCount())
                {
                    if (c==0)
                    {
                        deleter.at(0)->setVisible(false);
                        checkBoxWidget.at(0)->setStyleSheet("QCheckBox{color: black} QCheckBox::indicator{color: black;}");

                    }
                    else if (deleter.at(c-1)->isVisible()==true)
                    {
                        deleter.at(c-1)->setVisible(false);
                        checkBoxWidget.at(c-1)->setStyleSheet("QCheckBox{color: black} QCheckBox::indicator{color: black;}");
                    }
                }
            }
            return true;
        }
    }
    for (int i=0; i<deleter.size(); i++)
    {
        if(watched == deleter[i])
        {
            if(event->type() == QEvent::MouseButtonPress)
            {
                deleterow(i);
                break;
            }
        }
    }
    if(watched == ui->lineEdit)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
            {
                if(ui->lineEdit->text()!=nullptr)
                {
                    labelWidget.push_back(new QLabel());
                    checkBoxWidget.push_back(new QCheckBox());
                    labelWidget.push_back(new QLabel());
                    deleter.push_back(new QPushButton());
                    deleterrr.push_back(new QWidget());
                    insertrow(labelWidget.last(),ui->lineEdit->text(),checkBoxWidget.last(), deleterrr.last());
                    if(ui->tableWidget->maximumSize().height()+32<this->size().height()-80)
                    {
                        ui->tableWidget->setMaximumHeight((ui->tableWidget->rowCount())*30+2);
                        ui->tableWidget->setMinimumHeight((ui->tableWidget->rowCount())*30+2);
                        ui->tableWidget_2->setMaximumHeight((ui->tableWidget->rowCount())*30+2);
                        ui->tableWidget_2->setMinimumHeight((ui->tableWidget->rowCount())*30+2);
                    }
                }
                ui->lineEdit->clear();
                ui->pushButton_3->setStyleSheet(buadd0());
                ui->lineEdit->setStyleSheet("QLineEdit{background-color: none; border: none; height: 0px; max-height:0px;}");
                ui->lineEdit->setDisabled(true);
                ui->lineEdit->setVisible(false);
                ui->label->setVisible(true);
                this->setFocus();
            }
        }
    }
    return QDialog::eventFilter(watched, event);

}


void Dialog::on_tableWidget_cellPressed(int, int)
{
     buts[1]->setStyleSheet(BUTTON_STYLESHEET_TEMPLATE("actived_export.png", "disabled_export.png", "disabled_export.png"));
     if(ui->tableWidget_2->rowCount()!=2)
     {
        ui->tableWidget_2->insertRow(1);
        ui->tableWidget_2->setItem(1,0,new QTableWidgetItem("Введите новое ключевое слово"));
        ui->tableWidget_2->item(1,0)->setTextColor(Qt::blue);
     }
}
