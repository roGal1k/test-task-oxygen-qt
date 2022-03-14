#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QMouseEvent>
#include "qss.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_addButton_clicked();                    //Button slot add new row
    void on_closeButton_clicked();                  //Button slot close window
    void on_tableWidget_cellPressed(int, int );     //Table element click slot
    void on_startedButton_clicked();                //Reset button slot
    void on_allChecked_clicked();                   //Slot change state hader checkbox

public slots:
    void deleterow();                               //Slot delete row in table "list"
    void disactive();                               //Slot desactive hader checkbox

private:
    QVector <QCheckBox*> checkBoxWidget;            //Vector for CB in first column table
    QVector <QString*> name;                        //vector for catalog's name in second column table
    QVector <QPushButton*> delete_button;           //Buffer vector for button in third column table
    QVector <QWidget*> delete_button_widget;        //Vector for button in third column table
    QVector <QLabel*> labelWidget;                  //Vector for pixmap in third column table
    int ind=-1;                                     //Buffer parameter for event handling

public:
    void insertrow(QLabel *label, QString *name, QCheckBox *check, QWidget *delete_button_widget); //Function insert row in table "list"

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
