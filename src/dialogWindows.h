/*Balance of Power: Reviewed: A complex turn-based geopolitical simulation game
* Copyright (c) 2016-2017 Tomasz Ciborski (author of the port)
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DIALOGWINDOWS_H
#define DIALOGWINDOWS_H
#include <QDialog>
#include <QtWidgets>
//#include <QtGui>
class QLabel;
class QPushButton;
class QBoxLayout;
class QGroupBox;

class CloseUp:public QDialog{
    Q_OBJECT
public:
    CloseUp(QWidget *parent=0);
    QLabel *paramName[20];
    QLabel *sprpwrVal[24];
    QLabel *otherVal[12];
    QLabel *infoVal[8];
    QLabel *topHead[3];
    QLabel *label;
    QLabel *hint;
    QPushButton *button;

    QBoxLayout *mainLayout, *mainTableLayout, *headerLayout, *mainLowerLayout;
    QBoxLayout *column0, *column1, *column2, *column3, *lowerColumn1, *lowerColumn0;
};

class History:public QDialog{
    Q_OBJECT
public:
    History(QWidget *parent=0);
    QLabel *legend;
    QLabel *chart[9];
    QLabel *title[9];
    QBoxLayout *column[3];
    QBoxLayout *mainLayout, *columnLayout;
    //void paintEvent(QPaintEvent *event);
};

class NewsWindow:public QDialog{
    Q_OBJECT
public:
    NewsWindow(QWidget *parent=0);
    void keyPressEvent(QKeyEvent *event);
    QBoxLayout *mainLayout, *rightLayout, *leftLayout, *headsLayout, *middleLayout, *bottomLayout, *headsColumn[2], *head[4], *dataCol[2], *bottomCol[3];
    QBoxLayout *buttons[2], *leftInfoLayout[3];
    QLabel *newspaperTitle, *page;
    QLabel *newsHeadline, *reactionLine, *leftInfo[3], *leftInfoVal[3];
    QLabel *advisory, *picture[4], *advice[4], *data[3], *dataVal[3], *header[3], *colB[6], *colBVal[12];
    QPushButton *next, *previous, *question, *backDown;
};

class PolicyWindow:public QDialog{
    Q_OBJECT
public:
    QBoxLayout *mainLayout, *topLayout, *buttonLayout;
    PolicyWindow(QWidget *parent=0);
    QGroupBox *policy;
    QRadioButton *opt[6];
    QPushButton *cancel, *accept;
    QLabel *remain;
};

class ScoreWindow:public QDialog{
    Q_OBJECT
public:
    ScoreWindow(QWidget *parent=0);
    QBoxLayout *mainLayout, *columnLayout, *column[3];
    QLabel *chart, *cell[9], *level;
};

class NGameWindow:public QDialog{
    Q_OBJECT
public:
    NGameWindow(QWidget *parent=0);
    QGroupBox *level, *side, *mode;
    QRadioButton *lev[4], *sid[2], *mod[2];
    QBoxLayout *columnLayout, *column[3], *buttonLayout, *mainLayout;
    QLabel *topText;
    QPushButton *cancel, *accept;
};

class LostGameWindow:public QDialog{
    Q_OBJECT
public:
    LostGameWindow(QWidget *parent=0);
    QLabel *text;
    QBoxLayout *mainLayout;
    QPushButton *quit;
};

#endif // DIALOGWINDOWS_H
