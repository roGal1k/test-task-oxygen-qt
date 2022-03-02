#ifndef QSS_H
#define QSS_H

#endif // QSS_H

//
#define QSS()\
    "QLineEdit"\
    "{"\
    "background-color: rgba(0,0,0,0);"\
    "border:none;"\
    "color: rgb(0,52,255);"\
    "}"\
\
    "QLineEdit:hover:!pressed"\
    "{"\
    "background-color: rgba(0,0,0,0);"\
    "border:2px solid red;"\
    "color: rgb(0,170,255);"\
    "text-decoration: underline;"\
    "}"\

///кнопки импорта и экспорта
///
#define BUTTON_STYLESHEET_TEMPLATE(not_pressed, hovered, pressed)\
    "QPushButton"\
    "{"\
    "border-image: url(:/new/icon/icon/" not_pressed ");"\
    "background-repeat: no-repeat;"\
    "width: 18px;"\
    "height: 20px;"\
    "}"\
\
    "QPushButton:hover"\
    "{"\
    "border-image: url(:/new/icon/icon/" hovered ");"\
    "}"\
\
    "QPushButton:pressed"\
    "{"\
    "border-image: url(:/new/icon/icon/" pressed ");"\
    "}"\

///кнопка добавления
#define BUTTON_STYLESHEET_TEMPLATE1()\
    "QPushButton {"\
    "qproperty-iconSize: 18px;"\
    "background-color: none;"\
    "border:none;"\
    "background-repeat: no-repeat;"\
    "color: rgb(0,52,255)"\
    "}"\
\
    "QPushButton:hover"\
    "{"\
    "text-decoration: underline;"\
    "}"\
\
    "QPushButton:pressed"\
    "{"\
    "text-decoration: underline;"\
    "}"\

///кнопка добавления
#define buadd0()\
"QPushButton                            "\
"{                                      "\
"background-color: rgb(255, 255, 255);  "\
"height: 25px;                          "\
"max-height:25px;                       "\
"border: none;                          "\
"text-align: left;                      "\
"color: blue;                           "\
"}                                      "\
"QPushButton:hover                      "\
"{                                      "\
"color: rgb(155,50,255);                "\
"text-decoration: underline;            "\
"text-align: left;                      "\
"}                                      "\


#define buadd1()\
"QPushButton                            "\
"{                                      "\
"background-color: rgb(255, 255, 255);  "\
"height: 0px;                           "\
"max-height:0px;                        "\
"border: none;                          "\
"color: blue;                           "\
"text-align: left;                      "\
"}                                      "\
"QPushButton:hover                      "\
"{                                      "\
"color: rgb(155,50,255);                "\
"text-decoration: underline;            "\
"text-align: left;                      "\
"}                                      "\

#define firstrow()\
"QTableView::item                       "\
"{                                      "\
"    border-bottom=1px solid black;     "\
"}                                      "\
