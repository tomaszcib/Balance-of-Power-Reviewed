/*Balance of Power: Reviewed: A complex turn-based geopolitical simulation game
* Copyright (c) 2016 Tomasz Ciborski (author of the port)
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

#include <QtGui>
#include "dialogWindows.h"

CloseUp::CloseUp(QWidget *parent):QDialog(parent){
    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom);
    mainTableLayout=new QBoxLayout(QBoxLayout::LeftToRight);
    headerLayout=new QBoxLayout(QBoxLayout::LeftToRight);
    mainLowerLayout=new QBoxLayout(QBoxLayout::LeftToRight);
    column0=new QBoxLayout(QBoxLayout::TopToBottom);
    column1=new QBoxLayout(QBoxLayout::TopToBottom);
    column2=new QBoxLayout(QBoxLayout::TopToBottom);
    column3=new QBoxLayout(QBoxLayout::TopToBottom);
    lowerColumn0=new QBoxLayout(QBoxLayout::TopToBottom);
    lowerColumn1=new QBoxLayout(QBoxLayout::TopToBottom);
    hint=new QLabel;
    headerLayout->addSpacing(172);
    headerLayout->addWidget(hint);
    for(int i=0;i<3;i++){
        //header row
        topHead[i]=new QLabel(tr(""));
    }
    column0->addSpacing(20);
    column1->addWidget(topHead[0]);
    column2->addWidget(topHead[1]);
    column3->addWidget(topHead[2]);

    for(int i=0;i<20;i++){
        //left upper & lower column
        paramName[i]=new QLabel;
        if(i<=11) column0->addWidget(paramName[i]);
        else lowerColumn0->addWidget(paramName[i]);
    }
    for(int i=0;i<24;i++){
        //2nd and 3rd upper column
        sprpwrVal[i]=new QLabel(tr(""));
        if(i<12) column1->addWidget(sprpwrVal[i]);
        else column2->addWidget(sprpwrVal[i]);
    }
    for(int i=0;i<12;i++){
        //4th upper column
        otherVal[i]=new QLabel(tr(""));
        column3->addWidget(otherVal[i]);
    }
    for(int i=0;i<8;i++){
        //2nd lower column
        infoVal[i]=new QLabel(tr(""));
        lowerColumn1->addWidget(infoVal[i]);
    }

    //now putting it all together
    mainTableLayout->addLayout(column0);
    mainTableLayout->addLayout(column1);
    mainTableLayout->addLayout(column2);
    mainTableLayout->addLayout(column3);
    mainLowerLayout->addLayout(lowerColumn0);
    mainLowerLayout->addLayout(lowerColumn1);
    mainLayout->addLayout(mainTableLayout);
    mainLayout->addLayout(headerLayout);
    mainLayout->addSpacing(5);
    mainLayout->addLayout(mainLowerLayout);
    setLayout(mainLayout);
    setFixedSize(700,440);

}

History::History(QWidget *parent):QDialog(parent){
    columnLayout=new QBoxLayout(QBoxLayout::LeftToRight);
    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom);
    legend=new QLabel;
    mainLayout->addWidget(legend);
    for(int i=0;i<3;i++) {
        column[i]=new QBoxLayout(QBoxLayout::TopToBottom);
        columnLayout->addLayout(column[i]);
    }
    for(int i=0;i<9;i++){
        chart[i]=new QLabel;
        title[i]=new QLabel;
        column[i/3]->addWidget(title[i]);
        column[i/3]->addWidget(chart[i]);
    }
    legend->setFixedHeight(15);
    mainLayout->addLayout(columnLayout);
    setWindowTitle("");
    setFixedSize(700,520);
    setLayout(mainLayout);
}

void NewsWindow::keyPressEvent(QKeyEvent *event){
    if(event->key()!=Qt::Key_Escape) QDialog::keyPressEvent(event);
    else {}
}

NewsWindow::NewsWindow(QWidget *parent):QDialog(parent){
    mainLayout=new QBoxLayout(QBoxLayout::LeftToRight);

    //left half - news
    for(int i=0;i<2; i++) buttons[i]=new QBoxLayout(QBoxLayout::LeftToRight);
    leftLayout=new QBoxLayout(QBoxLayout::TopToBottom);
    newsHeadline=new QLabel;
    newspaperTitle=new QLabel;
    page=new QLabel;
    leftLayout->addWidget(newspaperTitle);
    leftLayout->addSpacing(40);
    leftLayout->addWidget(newsHeadline);
    newsHeadline->setFixedHeight(40);
    leftLayout->addSpacing(40);
    leftLayout->addWidget(page);
    previous=new QPushButton;
    next=new QPushButton;
    question=new QPushButton;
    backDown=new QPushButton;
    previous->setText("Previous");
    next->setText("Next");
    question->setText("Question");
    backDown->setText("Back Down");
    buttons[0]->addWidget(previous);
    buttons[1]->addWidget(question);
    buttons[0]->addWidget(next);
    buttons[1]->addWidget(backDown);
    leftLayout->addSpacing(40);
    leftLayout->addLayout(buttons[0]);
    reactionLine=new QLabel;
    reactionLine->setFixedHeight(30);
    reactionLine->setWordWrap(true);
    leftLayout->addWidget(reactionLine);
    leftLayout->addLayout(buttons[1]);
    for(int i=0;i<3;i++){
        leftInfoLayout[i]=new QBoxLayout(QBoxLayout::LeftToRight);
        leftInfo[i]=new QLabel("");
        leftInfoVal[i]=new QLabel("");
        leftInfoLayout[i]->addWidget(leftInfo[i]);
        leftInfoLayout[i]->addWidget(leftInfoVal[i]);
        leftLayout->addLayout(leftInfoLayout[i]);
    }

    //right half - advisory
    rightLayout=new QBoxLayout(QBoxLayout::TopToBottom);
    advisory=new QLabel;
    rightLayout->addWidget(advisory);
    headsLayout=new QBoxLayout(QBoxLayout::LeftToRight);
    for(int i=0;i<2;i++) headsColumn[i]=new QBoxLayout(QBoxLayout::TopToBottom);
    for(int i=0;i<4;i++) {
        head[i]=new QBoxLayout(QBoxLayout::LeftToRight);
        picture[i]=new QLabel("");
        advice[i]=new QLabel("");
        advice[i]->setWordWrap(true);
        head[i]->addWidget(picture[i]);
        head[i]->addWidget(advice[i]);
        headsColumn[i/2]->addLayout(head[i]);
    }
    for(int i=0;i<2;i++) headsLayout->addLayout(headsColumn[i]);


    middleLayout=new QBoxLayout(QBoxLayout::LeftToRight);
    for(int i=0;i<2;i++) dataCol[i]=new QBoxLayout(QBoxLayout::TopToBottom);
    for(int i=0;i<3;i++){
        data[i]=new QLabel("");
        dataCol[0]->addWidget(data[i]);
        dataVal[i]=new QLabel("");
        dataCol[1]->addWidget(dataVal[i]);
    }
    for(int i=0;i<2;i++) middleLayout->addLayout(dataCol[i]);

    bottomLayout=new QBoxLayout(QBoxLayout::LeftToRight);
    for(int i=0;i<3;i++){
        bottomCol[i]=new QBoxLayout(QBoxLayout::TopToBottom);
        header[i]=new QLabel("");
        bottomCol[i]->addWidget(header[i]);
    }
    for(int i=0;i<6;i++){
        colB[i]=new QLabel("");
        bottomCol[0]->addWidget(colB[i]);
    }
    for(int i=0;i<12;i++){
        colBVal[i]=new QLabel("");
        bottomCol[(i/6)+1]->addWidget(colBVal[i]);
    }
    for(int i=0;i<3;i++) bottomLayout->addLayout(bottomCol[i]);
    rightLayout->addLayout(headsLayout);
    rightLayout->addLayout(middleLayout);
    rightLayout->addLayout(bottomLayout);
    rightLayout->setGeometry(QRect(350,0,350,300));

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    newsHeadline->setWordWrap(true);
    connect(question,SIGNAL(released()),this,SLOT(close()));
    setLayout(mainLayout);
    setFixedSize(800,400);
    setWindowTitle("News");
}

PolicyWindow::PolicyWindow(QWidget *parent):QDialog(parent){
    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom);
    topLayout=new QBoxLayout(QBoxLayout::TopToBottom);
    buttonLayout=new QBoxLayout(QBoxLayout::LeftToRight);
    policy=new QGroupBox;
    remain=new QLabel;
    for(int i=0;i<6;i++){
        opt[i]=new QRadioButton(tr("Radio ")+QString::number(i));
        topLayout->addWidget(opt[i]);
    }
    policy->setLayout(topLayout);

    cancel=new QPushButton(tr("Cancel"));
    accept=new QPushButton(tr("OK"));
    buttonLayout->addWidget(cancel);
    connect(cancel,SIGNAL(released()),this,SLOT(close()));
    buttonLayout->addWidget(accept);
    mainLayout->addWidget(policy);
    mainLayout->addWidget(remain);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    setFixedSize(300,250);
    setWindowTitle("Enact policy");

}

ScoreWindow::ScoreWindow(QWidget *parent):QDialog(parent){
    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom);
    columnLayout=new QBoxLayout(QBoxLayout::LeftToRight);
    for(int i=0;i<3;i++) {
        column[i]=new QBoxLayout(QBoxLayout::TopToBottom);
        columnLayout->addLayout(column[i]);
    }
    for(int i=0;i<9;i++){
        cell[i]=new QLabel;
        column[i/3]->addWidget(cell[i]);
    }
    chart=new QLabel;
    level=new QLabel;

    mainLayout->addWidget(level);
    mainLayout->addLayout(columnLayout);
    mainLayout->addWidget(chart);
    setLayout(mainLayout);
    setFixedSize(300,400);
    setWindowTitle("Scores");

}

NGameWindow::NGameWindow(QWidget *parent):QDialog(parent){
    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom);
    columnLayout=new QBoxLayout(QBoxLayout::LeftToRight);
    buttonLayout=new QBoxLayout(QBoxLayout::LeftToRight);
    for(int i=0;i<3;i++) column[i]=new QBoxLayout(QBoxLayout::TopToBottom);
    level=new QGroupBox(tr("Level of play"));
    for(int i=0;i<4;i++){
        lev[i]=new QRadioButton;
        column[0]->addWidget(lev[i]);
    }
    side=new QGroupBox(tr("Side to play"));
    mode=new QGroupBox(tr("Number of players"));
    for(int i=0;i<2;i++){
        sid[i]=new QRadioButton;
        column[1]->addWidget(sid[i]);
        mod[i]=new QRadioButton;
        column[2]->addWidget(mod[i]);
    }
    level->setLayout(column[0]);
    side->setLayout(column[1]);
    mode->setLayout(column[2]);
    columnLayout->addWidget(level);
    columnLayout->addWidget(side);
    columnLayout->addWidget(mode);

    topText=new QLabel(tr("Your goal in this game is to increase the geopolitical prestige of your chosen superpower"
                          " while avoiding a nuclear war. The four levels provide increasingly complex and accurate representations"
                          " of the real world of geopolitics."));
    topText->setWordWrap(true);
    cancel=new QPushButton(tr("Cancel"));
    connect(cancel,SIGNAL(released()),this,SLOT(close()));
    accept=new QPushButton(tr("OK"));
    buttonLayout->addWidget(cancel);
    buttonLayout->addWidget(accept);
    mainLayout->addWidget(topText);
    mainLayout->addLayout(columnLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    setFixedSize(400,250);
    setWindowTitle("New game");

}

LostGameWindow::LostGameWindow(QWidget *parent):QDialog(parent){
    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom);
    mainLayout->setAlignment(Qt::AlignHCenter);
    quit=new QPushButton(tr("Exit"));
    connect(quit,SIGNAL(released()),this,SLOT(close()));
    text=new QLabel;
    QPalette pal;
    pal.setColor(QPalette::Window,QColor(0,0,0));
    setPalette(pal);
    mainLayout->addWidget(text);
    mainLayout->addWidget(quit);
    setLayout(mainLayout);
    setFixedSize(400,400);
    setWindowTitle("End of Game");
}
