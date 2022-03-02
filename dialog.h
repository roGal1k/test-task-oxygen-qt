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
    void insertrow(QLabel *label, QString name, QCheckBox *check, QWidget *deleterrr);
    void deleterow(int row);

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_tableWidget_cellPressed(int, int );

private:
    QVector <QCheckBox*> checkBoxWidget;
    QVector <QString*> name;
    QVector <QPushButton*> deleter;
    QVector <QWidget*> deleterrr;
    QVector <QLabel*> labelWidget;

    //настраиваю хедер
    QWidget *but[3] = {new QWidget(),new QWidget(),new QWidget()};
    QPushButton *buts[3] = {new QPushButton(),new QPushButton(),new QPushButton()};
    QHBoxLayout *layoubut[3] = {new QHBoxLayout(but[0]),new QHBoxLayout(but[1]),new QHBoxLayout(but[2])};

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H

