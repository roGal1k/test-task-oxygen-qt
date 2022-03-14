#ifndef QSS_H
#define QSS_H

#define BUTTON_STYLESHEET_TEMPLATE(not_pressed, hovered, pressed)\
    "QPushButton{ border-image: url(:/new/icon/icon/" not_pressed "); background-repeat: no-repeat; width: 18px; height: 20px;}"\
    "QPushButton:hover{ border-image: url(:/new/icon/icon/" hovered ");}"\
    "QPushButton:pressed{ border-image: url(:/new/icon/icon/" pressed ");}"\

#define buadd0()\
    "QPushButton{ background-color: rgb(255, 255, 255); height: 25px; max-height:25px; border: none;  text-align: left; color: blue;}"\
    "QPushButton:hover{ color: rgb(155,50,255); text-decoration: underline; text-align: left;}"\

#define buadd1()\
    "QPushButton{ background-color: rgb(255, 255, 255); height: 0px; max-height:0px; border: none; color: blue; text-align: left;}"\
    "QPushButton:hover{ color: rgb(155,50,255);text-decoration: underline; text-align: left;}"\

#define LE()\
    "QTextEdit{ background-color: none; border: 1px solid blue; height:25px; max-height:25px;}"\

#define LEnone()\
    "QTextEdit{ background-color: none; border: none; height:none; max-height:none;}"\

#define checkBOX()\
    "QCheckBox::indicator{ subcontrol-origin: content; subcontrol-position: center; width: 15px; height: 15px;}"\
    "QCheckBox::indicator:checked {image: url(:/new/icon/icon/checkbox_normal_actived.png);}"\
    "QCheckBox::indicator:unchecked {image: url(:/new/icon/icon/checkbox_normal_unactived.png);}"\
    "QCheckBox::indicator:checked:hover {image: url(:/new/icon/icon/checkbox_hover_actived.png);}"\
    "QCheckBox::indicator:unchecked:hover {image: url(:/new/icon/icon/checkbox_hover_unactived.png);}"\

#define checkBOX1()\
    "QCheckBox::indicator{subcontrol-origin: content; subcontrol-position: center; width: 15px; height: 15px;}"\
    "QCheckBox::indicator:checked {image: url(:/new/icon/icon/checkbox_hover_actived.png);}"\
    "QCheckBox::indicator:unchecked {image: url(:/new/icon/icon/checkbox_hover_unactived.png);}"\
    "QCheckBox::indicator:checked:hover {image: url(:/new/icon/icon/checkbox_hover_actived.png);}"\
    "QCheckBox::indicator:unchecked:hover {image: url(:/new/icon/icon/checkbox_hover_unactived.png);}"\

#endif // QSS_H
