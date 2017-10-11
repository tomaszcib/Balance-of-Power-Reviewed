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

#include <QtGui>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;
#include "mainbox.h"
#include "core.h"

//! [0]
MainBox::MainBox(){
    setMouseTracking(true);
    setBackgroundRole(QPalette::Base);
    createActions();
    createMenus();
    createToolbars();
    setContextMenuPolicy(Qt::NoContextMenu);
    setWindowTitle(tr("Balance of Power: Reviewed"));
    setFixedSize(935,559);
    connect(nwsWind.previous,SIGNAL(released()),this,SLOT(prevNews()));
    connect(nwsWind.next,SIGNAL(released()),this,SLOT(nextNews()));
    connect(plcyWind.accept,SIGNAL(released()),this,SLOT(enactPolicy()));
    connect(newGameWindow.accept,SIGNAL(released()),this,SLOT(setNewGame()));
    connect(nwsWind.question,SIGNAL(released()),this,SLOT(doCHumanTough()));
    connect(nwsWind.backDown,SIGNAL(released()),this,SLOT(doCHumanLoose()));
    QPixmap icon;
    icon.load(":/images/icon175x175.png","PNG");
    aboutBox.setIconPixmap(icon);
    aboutBox.setText("<font size=4><b>Balance of Power: Reviewed</b> ver beta 1.2</font><br><br><br>a complex turn-based Cold War geopolitical simulation game<br><br><b>original author:</b> Chris Crawford (1985, 1988)<br><b>author of the port:</b> Tomasz Ciborski (2016-2017)");
    saveBox.setIcon(QMessageBox::Information);
    saveBox.setText("The game has been saved.");

    //background
    QPalette pal;
    pal.setColor(QPalette::Window,QColor(173,223,255));

    setPalette(pal);

    //score section
    QPixmap flagImg[2];
    flagImg[0].load(":/images/USA.png","PNG");
    flagImg[1].load(":/images/USSR.png","PNG");
    for(int i=0;i<2;i++){
        flag[i]=new QLabel(this);
        flag[i]->move(292+120*i,482);
        flag[i]->setPixmap(flagImg[i]);
        sprLabel[i]=new QLabel(this);
        sprLabel[i]->move(330+120*i,476);
        score[i]=new QLabel(this);
        score[i]->move(330+120*i,486);
        holdsMouse[i]=new QLabel(this);
        holdsMouse[i]->move(300+120*i,457);
        geoLabel[i]=new QLabel(this);
    }
    geoLabel[0]->move(15,366);
    geoLabel[0]->setText("Central America");
    geoLabel[1]->move(72,394);
    geoLabel[1]->setText("Middle East");
    yearLabel=new QLabel(this);
    yearLabel->move(333,64);

    resrc.setStrings();
    core.resrc.setStrings();
    core.loadGame();
    correctMenus();
    drawScores();
    drawMapStaticStrings();

    yearLabel->setText("<font size=\"5\"><b>"+QString::number(core.year)+"</b></font>");
    initMapPolygons();
    initLegend();


    //DEBUG
    curSelection=0;
    mapMode=8;
    curAddParam=0;
    curIOMode=0;
    //ENDDEBUG
    selectNothingEffect();

    drawMap(mapMode,curAddParam,curIOMode);

}
//! [4]
void MainBox::drawMap(int t, int addParam, bool inOutMode){
    mapMode=t; curAddParam=addParam; curIOMode=inOutMode;
    int maxi=1, median, step;
    int tempVal[N];
    QString tempCpt;
    QColor colour;
    if(inOutMode) drawLegend(t+1,addParam);
    else drawLegend(t,addParam);

    for(int i=0;i<N;i++) tempVal[i]=0;

    if(t==0)
        for(int i=0;i<N;i++) tempVal[i]=((core.state[i].dontMess*N*5)/core.sumDontMess)*10;
    else if(t==2)
        for(int i=0;i<N;i++) tempVal[i]=core.state[i].prestVal/8;
    else if(t==3)
        for(int i=0;i<N;i++) tempVal[i]=core.state[i].strengthRatio;
    else if(t==4)
        for(int i=0;i<N;i++) tempVal[i]=core.state[i].govPopul;
    else if(t==5)
        for(int i=0;i<N;i++) tempVal[i]=core.state[i].finlandization[USA];
    else if(t==6)
        for(int i=0;i<N;i++) tempVal[i]=core.state[i].finlandization[USSR];

    else if(!inOutMode&&((t>=8&&t<=26)||t==39)){
        curSelection=addParam;
        //going out
        if(t==8)
            for(int i=0;i<N;i++) tempVal[i]=core.state[i].overallRelationship[addParam];
        else if(t==10)
             for(int i=0;i<N;i++) tempVal[i]=core.state[i].milAid[addParam];
        else if(t==12)
             for(int i=0;i<N;i++) tempVal[i]=core.state[i].rebAid[addParam];
        else if(t==14)
            for(int i=0;i<N;i++) tempVal[i]=core.state[i].milIntv[addParam];
        else if(t==16)
            for(int i=0;i<N;i++) tempVal[i]=core.state[i].rebIntv[addParam];
        else if(t==18)
            for(int i=0;i<N;i++) tempVal[i]=core.state[i].econAid[addParam];
        else if(t==20)
            for(int i=0;i<N;i++) tempVal[i]=core.state[i].destabilization[addParam];
        else if(t==22)
            for(int i=0;i<N;i++) tempVal[i]=core.state[i].pressure[addParam];
        else if(t==24)
            for(int i=0;i<N;i++) tempVal[i]=core.state[i].treaty[addParam];
        else if(t==26)
            for(int i=0;i<N;i++) tempVal[i]=core.state[i].tradePolicy[addParam];

        else if(t==39) {
            for(int i=0;i<N;i++){
                if(core.state[i].overallRelationship[addParam]<=-127&&i>1&&curSelection>1&&i!=curSelection) {
                        tempVal[i]=1;
                        colour=QColor(255,0,0);
                        tempCpt=resrc.strg[154+i]+" - "+resrc.strg[133];
                    }
                else {
                        colour=QColor(255,255,255);
                        tempCpt=resrc.strg[154+i]+" - "+resrc.strg[135];
                    }
                if(i==addParam) colour=QColor(0,0,0);
                shapeItems[i].setToolTip(tempCpt);
                shapeItems[i].setColor(colour);
                }
            countryHighlight->setText(resrc.strg[153]);
            countryHighlight->adjustSize();
            return;
        }
    }

    else if(inOutMode&&t>=8&&t<=26){
        curSelection=addParam;
        //going in
        if(t==8)
            for(int i=0;i<N;i++) tempVal[i]=core.state[addParam].overallRelationship[i];
        else if(t==10)
             for(int i=0;i<N;i++) tempVal[i]=core.state[addParam].milAid[i];
        else if(t==12)
             for(int i=0;i<N;i++) tempVal[i]=core.state[addParam].rebAid[i];
        else if(t==14)
            for(int i=0;i<N;i++) tempVal[i]=core.state[addParam].milIntv[i];
        else if(t==16)
            for(int i=0;i<N;i++) tempVal[i]=core.state[addParam].rebIntv[i];
        else if(t==18)
            for(int i=0;i<2;i++) tempVal[i]=core.state[addParam].econAid[i];
        else if(t==20)
            for(int i=0;i<2;i++) tempVal[i]=core.state[addParam].destabilization[i];
        else if(t==22)
            for(int i=0;i<2;i++) tempVal[i]=core.state[addParam].pressure[i];
        else if(t==24)
            for(int i=0;i<2;i++) tempVal[i]=core.state[addParam].treaty[i];
        else if(t==26)
            for(int i=0;i<2;i++) tempVal[i]=core.state[addParam].tradePolicy[i];
    }


    else if(t==33&&addParam==0)
        for(int i=0;i<N;i++) tempVal[i]=core.state[i].gdp;
    else if(t==33&&addParam==1)
        for(int i=0;i<N;i++) tempVal[i]=core.state[i].gdp/(core.state[i].population/1000);
    else if(t>=34&&t<=36&&addParam==0)
        for(int i=0;i<N;i++) tempVal[i]=core.state[i].gdpSpending[t-34];
    else if(t>=34&&t<=36&&addParam==1)
        for(int i=0;i<N;i++) tempVal[i]=(core.state[i].gdpSpending[t-34])/(core.state[i].population/1000);
    else if(t>=34&&t<=36&&addParam==2)
        for(int i=0;i<N;i++) tempVal[i]=(core.state[i].gdpFrac[t-34]*100000/255);
    else if(t==37)
        for(int i=0;i<N;i++) tempVal[i]=core.state[i].population;
    else if(t==38)
        for(int i=0;i<N;i++) tempVal[i]=core.state[i].troopSize;

    else if(t==7){
        for(int i=2;i<N;i++)
            for(int j=2;j<N;j++) {
                if(core.state[i].overallRelationship[j]<=-127&&i!=j) tempVal[j]=1;
            }
        for(int i=0;i<N;i++){
            if(tempVal[i]==1) {
                colour=QColor(255,0,0);
                tempCpt=resrc.strg[154+i]+" - "+resrc.strg[133];
            }
            else {
                colour=QColor(255,255,255);
                tempCpt=resrc.strg[154+i]+" - "+resrc.strg[135];
            }
            shapeItems[i].setToolTip(tempCpt);
            shapeItems[i].setColor(colour);
        }
        countryHighlight->setText(resrc.strg[153]);
        countryHighlight->adjustSize();
        return;
    }
    else if(t==1){
        for(int i=0;i<N;i++){
            if(core.state[i].coupFlag) {
                colour=QColor(0,255,0);
                tempCpt=resrc.strg[154+i]+" - "+resrc.strg[136];
            }
            else if(core.state[i].rebWinFlag) {
                colour=QColor(255,0,0);
                tempCpt=resrc.strg[154+i]+" - "+resrc.strg[137];
            }
            else if(core.state[i].finlFlag) {
                colour=QColor(0,0,255);
                tempCpt=resrc.strg[154+i]+" - "+resrc.strg[138];
            }
            else {
                colour=QColor(255,255,255);
                tempCpt=resrc.strg[154+i];
            }
            shapeItems[i].setToolTip(tempCpt);
            shapeItems[i].setColor(colour);
        }
        countryHighlight->setText(resrc.strg[153]);
        countryHighlight->adjustSize();
        return;
    }

    //maxval
    for(int i=0;i<N;i++) if(tempVal[i]>maxi) maxi=tempVal[i];

    //average
    int sum=0;
    for(int i=0;i<N;i++) sum+=tempVal[i];
    median=sum/N;


    if(t>=18&&t<=26&&inOutMode){
        for(int i=0;i<2;i++){
            if(addParam!=i) colour=QColor(255,255-(tempVal[i]*51),255-(tempVal[i]*51));
            tempCpt=resrc.strg[154+i]+QString(" - ")+captionCreate(t,addParam,tempVal[i]);
            shapeItems[i].setToolTip(tempCpt);
            shapeItems[i].setColor(colour);
        }
        for(int i=2;i<N;i++){
            if(addParam!=i) colour=QColor(255,255,255);
            else colour=QColor(0,0,0);
            shapeItems[i].setToolTip(tr("n/a"));
            shapeItems[i].setColor(colour);
        }
        return;
    }


    for(int i=0;i<N;i++){
        if(t>=33){
            if(tempVal[i]>=median){
                step=(maxi-median)/127;
                if(127-((tempVal[i]-median)/step)<0) colour=QColor(255,0,0);
                else colour=QColor(255,127-((tempVal[i]-median)/step),0);
            }
            else{
                step=median/127;
                colour=QColor(255,255-(tempVal[i]/step),0);
            }
        }
        else if(t==8){
            if(tempVal[i]>=0&&addParam!=i){
                colour=QColor(255-(tempVal[i]*2),255-tempVal[i],255-(tempVal[i]*2));
            }
            else if(tempVal[i]<0&&addParam!=i){
                colour=QColor(255,255+(tempVal[i]*2),255+(tempVal[i]*2));
            }
            else colour=QColor(0,0,0);
        }
        else if(t==0){
            if(tempVal[i]>=50){
                colour=QColor((-tempVal[i]+90)*5,(-tempVal[i]+90)*5,250);
            }
            else if(tempVal[i]<=40){
                colour=QColor(250,tempVal[i]*5,tempVal[i]*5);
            }
            else{
                colour=QColor(250,250,250);
            }
        }
        else if(t==5||t==6){
            if(addParam!=i){
                if(tempVal[i]>127) colour=QColor(255,0,0);
                else colour=QColor(255,255-(tempVal[i]*2),255-(tempVal[i]*2));
            }
            else colour=QColor(0,0,0);
        }
        else if(t==4) colour=QColor(255,tempVal[i]*12,tempVal[i]*12);
        else if(t==3){
            if(tempVal[i]==1) colour=QColor(255,0,0);
            if(tempVal[i]>1) colour=QColor(255,100,100);
            if(tempVal[i]>7) colour=QColor(255,150,150);
            if(tempVal[i]>31) colour=QColor(255,180,180);
            if(tempVal[i]>127) colour=QColor(255,210,210);
            if(tempVal[i]>511) colour=QColor(255,255,255);
        }
        else if(t==2){
            if(tempVal[i]>=median){
                step=(maxi-median)/127;
                colour=QColor(255,127-((tempVal[i]-median)/step),127-((tempVal[i]-median)/step));
            }
            else{
                step=median/127;
                colour=QColor(255,255-(tempVal[i]/step),255-(tempVal[i]/step));
            }
            if(i==1) colour=QColor(255,0,0); //kludge! :C
        }
        else {
            if(addParam!=i) colour=QColor(255,255-(tempVal[i]*51),255-(tempVal[i]*51));
            else colour=QColor(0,0,0);
        }
        tempCpt=resrc.strg[154+i]+QString(" - ")+captionCreate(t,addParam,tempVal[i]);
        shapeItems[i].setToolTip(tempCpt);
        shapeItems[i].setColor(colour);

    }
    if(t>=8&&t<=26)countryHighlight->setText(resrc.strg[28]);
    else countryHighlight->setText(resrc.strg[153]);
    countryHighlight->adjustSize();
}

void MainBox::drawLegend(int t, int addParam){
    if(t>=8&&t<=26)
        legendCaption->setText(resrc.strg[t]+resrc.strg[addParam+154]);
    else if(t==39) legendCaption->setText(resrc.strg[29]+resrc.strg[addParam+154]);
    else if(t>=33&&t<=38) {
        if(curAddParam==1) legendCaption->setText(resrc.strg[t]+" per capita");
        else if(curAddParam==2) legendCaption->setText(resrc.strg[t]+" as a % of GDP");
        else legendCaption->setText(resrc.strg[t]);
    }
    else legendCaption->setText(resrc.strg[t]);
    legendCaption->adjustSize();

    if(t>=33&&t!=39){
        shapeItems[80].setColor(QColor(255,0,0));
        shapeItems[81].setColor(QColor(255,127,0));
        shapeItems[82].setColor(QColor(255,255,0));
            for(int i=0;i<3;i++) {
                legendLabel[i]->setText(resrc.strg[i+130]);
                legendLabel[i]->adjustSize();
            }
    }
    else if(t==8){
        shapeItems[80].setColor(QColor(0,127,0));
        shapeItems[81].setColor(QColor(255,255,255));
        shapeItems[82].setColor(QColor(255,0,0));
        for(int i=0;i<3;i++) {
            legendLabel[i]->setText(resrc.strg[i+139]);
            legendLabel[i]->adjustSize();
        }
    }
    else if(t==0){
        shapeItems[80].setColor(QColor(0,0,255));
        shapeItems[81].setColor(QColor(255,255,255));
        shapeItems[82].setColor(QColor(255,0,0));
        for(int i=0;i<3;i++) {
            legendLabel[i]->setText(resrc.strg[i+142]);
            legendLabel[i]->adjustSize();
        }
    }
    else if(t==1){
        shapeItems[80].setColor(QColor(0,255,0));
        shapeItems[81].setColor(QColor(255,0,0));
        shapeItems[82].setColor(QColor(0,0,255));
        for(int i=0;i<3;i++) {
            legendLabel[i]->setText(resrc.strg[i+136]);
            legendLabel[i]->adjustSize();
        }
    }
    else if(t==7||t==39){
        shapeItems[80].setColor(QColor(255,0,0));
        shapeItems[81].setColor(QColor(255,255,255));
        shapeItems[82].setColor(QColor(255,255,255));
        for(int i=0;i<3;i++) {
            legendLabel[i]->setText(resrc.strg[i+133]);
            legendLabel[i]->adjustSize();
        }
    }
    else{
        shapeItems[80].setColor(QColor(255,0,0));
        shapeItems[81].setColor(QColor(255,127,127));
        shapeItems[82].setColor(QColor(255,255,255));
        for(int i=0;i<3;i++) {
            legendLabel[i]->setText(resrc.strg[i+130]);
            legendLabel[i]->adjustSize();
        }
    }

}

void MainBox::initLegend(){
    legend[0]=QRect(QPoint(618,374),QPoint(638,397));
    legend[1]=QRect(QPoint(618,404),QPoint(638,427));
    legend[2]=QRect(QPoint(618,434),QPoint(638,457));
    for(int i=0;i<3;i++) {
        legendPath[i].addRect(legend[i]);
        createShapeItem(legendPath[i],tr(""),QPoint(0,0),QColor(255,255,255));
    }

    for(int i=0;i<3;i++) {
        legendLabel[i]=new QLabel(this);
    }
    legendLabel[0]->move(QPoint(650,380));
    legendLabel[1]->move(QPoint(650,410));
    legendLabel[2]->move(QPoint(650,440));

    legendCaption=new QLabel(this);
    legendCaption->move(QPoint(618,470));

    countryHighlight=new QLabel(this);
    countryHighlight->move(QPoint(618,482));
}

QString MainBox::captionCreate(int t, int addParam, int val){
    int temp;
    if(t==0){
        val/=10;
        return QString(resrc.strg[val+120]);
    }
    if(t==2) return QString::number(val);
    if(t==3) {
        temp=0;
        if(val>1) temp=1;
        if(val>7) temp=2;
        if(val>31) temp=3;
        if(val>127) temp=4;
        if(val>511) temp=5;
        if(val>2048) temp=6;
        return QString(resrc.strg[113+temp]);
    }
    if(t==4){
        temp=0;
        if(val<15) temp=1;
        if(val<12) temp=2;
        if(val<8) temp=3;
        if(val<4) temp=4;
        return QString(resrc.strg[108+temp]);
    }
    if(t==5||t==6){
        temp=0;
        if(val>25) temp=1;
        if(val>50) temp=2;
        if(val>75) temp=3;
        if(val>100) temp=4;
        return QString(resrc.strg[108+temp]);
    }
    if(t==8){
        if(val>-128) temp=0;
        if(val>-100) temp=1;
        if(val>-72) temp=2;
        if(val>-44) temp=3;
        if(val>-16) temp=4;
        if(val>16) temp=5;
        if(val>44) temp=6;
        if(val>72) temp=7;
        if(val>100) temp=8;
        return QString(resrc.strg[64+temp]);
    }
    if((t>=10&&t<=13)) return QString(resrc.strg[73+val]);
    if((t>=14&&t<=17)) return QString(resrc.strg[79+val]);
    if(t==18) return QString(resrc.strg[85+val]);
    if(t==20) return QString(resrc.strg[91+val]);
    if(t==22) return QString(resrc.strg[697+val]);
    if(t==24) return QString(resrc.strg[102+val]);

    if(t>=33&&t<=36){
        QString tmpstr;
        if(addParam==0) {
            tmpstr=QString(resrc.strg[145])+QString::number(val)+QString(resrc.strg[146]);
        }
        if(addParam==1){
            tmpstr=QString(resrc.strg[145])+QString::number(val);

        }
        if(addParam==2){
            tmpstr=QString::number(val)+QString(resrc.strg[150]);
            tmpstr.insert(tmpstr.size()-11,'.');
        }
        return tmpstr;
    }

    if(t==37) return QString::number(val)+QString(resrc.strg[147]);
    if(t==38) return QString::number(val)+QString(resrc.strg[148]);
}

void MainBox::initMapPolygons(){
    //USA
    tmpx[0]=71; tmpy[0]=199;
    compass[0]="2nwnwnwnwn2wn2w4nw7ne4n2w2ne4nene2ne2ne2ne2nene2nenenenenen2e2ne3ne2ne4nw3nw2nw3n2eseses2ese2sw4s3ene3n9e9e9e9e9e9e9e9e9eses6es3e2s2ws4w2s5es3en4es2e3s3wswswswswsw2sw2sw5s2ene2nen2ene4nen2en3en2e2n2e5sw3se2swswsw2s3en2en6en2e3n7en3enen2en2en2en4es5en2enenenene2ne2nene3n2e4s2ese2sw6s2ws4ws3ws2wsws2w2sw5s5ws2ws4wswswswsws5ws2ws2w2sw4se4sw2swsws3ws2wsws2wswswswswswsws2wswswsw3sw6se9s3sws2wnw2nw3nwnw3ne7n2wn7wn2wn7wn3w3se2sws4wn2wn9wsws4wswsws2wsw2sw2sw2sw2s2wn2wnw5n2wnw5nwn5w2s3wn2w4nw2nwnw2n6ws9w3wnwn2wn7wn4w";

    //USSR
    tmpx[1]=496; tmpy[1]=123;
    compass[1]="2ne3ne4nenen2eses2e4n5en4enenenenen2ene5n2wswswsw2swsws9ww2nwnwnw8ne3ne2ne5n2e2n2e2n5e3nenen2en2es3es7es4es3es2es3es2ese2sws2ws8wn2wn3wn4w2ses2esesese2s2es3e2nen2es2es3ene3nenen4es2e2nwnw3nw2n4es2e4s3en3en2enen9es3en5enen3es2e3n9e2es3es2e2nw2nw3nenene2nen4eses2e4se2ses2e2sese2se3sws2w3s2en3e2s2e3nw2ne4nw3nwnwn2wnwnw3nen2e3s3e2n6e3n2en5en4ene2n2enenen2en9e7ene3n5es4es4es9ees4es2es2e2sws2wswsw2s3en3en5es9e5es6es5enen9es3es2e2s2es2es2es2es3e3n2es9e4e2nwnwnwnw2n4es3es2es3es4es5en5eses2es4es6es3enen2es4en2es3es3eses2es9e9e3en2eses2es3e3n4en8eses3es2e2n2es2es4eses4es3es2es3es6es2es2es7e2ses2ese2s4wn3wn6wn2wn4wn3w2ses2esese3s3es3e2s3ws4wsw2s2w2sw2s4wn6wsws4w4sw2s2es3eses2esese2se3sese2sw2se2sw8swnw2nwnwnwnwnwnwnwnwn3wnwnwn2wnwnwnwnw2nw5nene6ne2ne2nwnw2nwn2w3sw2s4wnwn6ws2w2sw3ses3e2s8wnwn7ws9w8wsw5swsw4sw2s2w2ses7eses3en3es3es2eseses2e3nw2n3e2se2seseses2e2seseses2eseseses2e2s2w3se2sese3s2wnwnw2nw2nwnwnw3nwnwn2w2nwnw2n2w2n3w2sese2se2sese2se3se8sw4sw3sw2sws2ws5wn3wnwnwnw3nen3e2ne2nw4nw3n3ws2ws6wnwnwn2wnwn2wn5wn2wn2wnwnwnwnwnwn2wnwnwnwn3wn3wn9wsw2sese9s5w7s2es4en6esese2s4ws2ws2wsws2ws2ws4wn2w3se5s2ws7ws3ws2ws8wn3wn3wn3ws7wn5wnw2n2wn2wn3wn2wn2wn3wn4wn2w3nw2nwnwnwnwn5wn2wnw3n5w5sw2s5wswsw5s3ws2w3se2se2se4s2w2sw2sw2sw3sws2ws4ws3wsw2s4wnwnwn2wswswsws9w2ws3w2sw2s2wswsws2wn3w3nwn2wn2wn2wn2wn3wn2wn3ws3wsws2w3nw2nw2nwnw3nw2nw3nwnwnwn2wnwnwnw4n2en2es3e3nw2nwnwn9ws2w2s2wswswsw3sese2se3se3s3ese2sese5s2w3n5ws3wn4wnw2nw2n3wn5wnw2nwnwn2wn2wnwn2wn2wnwnwn4w2n4enene4n3wsws2ws3wsw2s2e2swsws4wnw2ne2n4wnwn3ws2wnwnwnw2nwnwnwn3ws3ws3ws3wn5wnw4nen2e2ne5nw3ne3nwnwnwn8w";

    //Mexico
    tmpx[2]=125; tmpy[2]=223;
    compass[2]="2wn2wnw5n2wnw5nwn5w2s3wn2w4nw2nwnw2n6ws9w3wnwn2wn7wn5w4se7sesese3swsw3ses3ese6sese2seseses3e3n2wnwnw7nw2nw3nw6nwnw6n2es2e2se7se2sesesese2sese3se2sesese2sesese3se9sseseseseseses3es2eses2es2eses2es3es8en4es2eses3e2nen4e3nw3nen2es4enenenene2nenenenene3nwn6ws2wswsw2sw2swswsws3ws4ws4wn2wn3wnw3nwnw6nw6ne2ne2ne2ne2n";

    //Honduras
    tmpx[3]=150; tmpy[3]=268;
    compass[3]="5n2wnw3nen2es2en6en2eses3ese2sw2s3wn6w3swsws3w";

    //Nicaragua
    tmpx[4]=164; tmpy[4]=264;
    compass[4]="3wn6w3swsws2w4seseses8e4ne3ne4n";

    //Panama
    tmpx[5]=165; tmpy[5]=288;
    compass[5]="2ne3n6en2enen3es2es2e5s3wnwn4ws2sw2sws2wn2wn2w";

    //Cuba
    tmpx[6]=161; tmpy[6]=235;
    compass[6]="2n3enen2en6es5eses4e2s3es2eseses2es2e2se24enen2es6es2esesese2s5wn3ws5wn3ws2wn2wn3wnw2ne2n6wn3w3nwnwn5wn2wnwn3ws2ws";

    //Argentina
    tmpx[7]=251; tmpy[7]=507;
    compass[7]="3wnwn2w2n2wnwnwn3wn2wnw2nwn2w2nw2nw5nw6nw5nwnw3nwnw2nwnw4nw4nw5ne2nwnw3nw3n2e2nw9nw2nw2nw8nw6ne3nene5nw4nenene6n2e2n3es3es2en4e2ne3ne4n5en3es4e3se5ses2e2s2e2s5es2ese3se4sese4sws2wswswswsw2sw2sw2s2es2e2s2eses2es2es2ese6swsws7wn3w2sesese2se5sw2s2ws4ws2ws4w5swsws2wn2wsw2seses2ese2s2w6swswswsw3s2eses3ese4swswsw2se2s2wsw3se2s2ese2sesesese2s";

    //Colombia
    tmpx[8]=179; tmpy[8]=287;
    compass[8]="3e5n5e2ne3nen4en3enenen2en4e2s2w2s3wsw2sw4sw2sese3ses2es4eseses5ese9s5sws6w2se2swsw2se2se4sw2s5wn2ws4w2nw2nwnwnwnwn4w2n5wnwn2wn2w3ne2nenen2e3ne5nw3nw4nw2n";

    //Peru
    tmpx[9]=176; tmpy[9]=311;
    compass[9]="2wsws2wsw2sw9se5s2w4se2se3sesesese2sese2sese2sese2se2s2e4sesese2se3seseseseseseses2eses2es2es2es2es2es2ene3ne4nw9ne5n2w2nw2n3wnw3n2ws3w2n2wnw2nwnw2nw3nene3ne3n2enen3en4e6n5wn2ws4w2nw2nwnwnwnwn4w2n5wnwn2wn2w";

    //Venezuela
    tmpx[10]=202; tmpy[10]=275;
    compass[10]="3wsw2sw4sw2sese3ses2es4eseses5ese9s5sese2ses6e2n2en2e3nwnw4n6en3en2ene2nwnw3nenene2ne3nw2nwnwnwn2w2nwn4ws2ws5wn2wn6w2nw2n2wn3w2sws3w";

    //Brazil
    tmpx[11]=213; tmpy[11]=308;
    compass[11]="ese2ses6e2n2en2e3nwnw4n6en3en2ene2nwnw3nenene2ne2n3esesese2seses2es8es3es3esese2ses2e4se2se2se4sw2s2es3es2es3es3es2es3e2seses2en4es2es8es2eseses2e2ses2es5e2se2se7sw4swsw2swswswswsw2swswsw2sw4sw9s4sw7sw2sw2sw3swswswsws5ws3ws2wsws2ws2wswswswsw8se3sw2swswsw4swswswswsw2sw3s2w3nwn2wn2wn2wnwn2w2n2wn2w2ne2ne2nenenenen2ene4nwnw4nw3nwn2wn5w2n2w2n2wnw5nw3ne7nwnwnw2n2wn3wnw3nw2nwnwn2wnwn2wnwn2wn3wnwnwnwnwnw5n3ws3wswsws5w3wnw3n2ws3w2n2wnw2nwnw2nw3nene3ne3n2enen3en4e6n2ne4nw2nw2nene2nw2n6ene";

    //Chile
    tmpx[12]=251; tmpy[12]=507;
    compass[12]="3wnwn2w2n2wnwnwn3wn2wnw2nwn2w2nw2nw5nw6nw5nwnw3nwnw2nwnw4nw4nw5ne2nwnw3nw3n2e2nw9nw2nw2nw8nw6ne3nene5nw4nenene5n2w2nw2nw3nw3nw2nw4n2wn2wsw4se5se9s7se8sw9se6sw4sw9s2sw8se2se5se4se4se4se3se4se2se3se3se3se2se2sesese2sesesesese2seseses2eseses2es2es3es4es4en5e2n3wn2wn2wn2ws";

    //Canada
    tmpx[13]=241; tmpy[13]=155;
    compass[13]="2en3esw2s3w3s4enenen2en6enen4enene2n3wsws2wnwn5w4n2e4nwn5w3n2en7eseses4e3n9en2e2n2en5eswsw2s2wswswsws2wswswsw2s9eses4es2es3e4nwnw2ne2nwn4w4nene2nw2nene5n5ws2ws3w2n2enene2n4w2nw9nw6n2ws2wsw2s2ws2ws5ws2wnw2n2e2nw2n2e3nwn2wnw2n9wn3ws2w4sw2swswsws2wswsw2s2e5swswsws2ws2ws2ws3wsw4sw3sw2sw2s2ws6w4ne2nw2ne2nene3n7wn2wnwn2wn2wnwn7w3ne3n2w3nenenen2enen2en2enen2enen2e2n3en6en4en2en2e3n3e2sw2swsw2s5en4es4e3nwn3wnwnwnw2n2es2e5n3w4n3ws2w2nw2n2e6n7w2s2wswsw3se3s2w2nw2nwn4wsws2w2s2es2e2s5ws5wn7wn2wnwn2wsws9w3ws2s3wn4wn2w2n3wnwn4wn8w2wn2wn2ws2ws2wn5ws9ws2ws2ws5wn2wn2wn3ws2wsws2wswsws2wswswsws2wswswsws2wswsws2wswswswsws2wswswsws2wsw3s3e3s4en4e7sw3se2swswswswsw3s2e6sw5s3ese2se2s9e9e9e9e9e9e9e9e9eses6es3es5en2e2n6e2s2ese3seseses3es2esese2s2ws3wswswsws3w2swswsw2s3en2en6en2e3n7en3enen2en2en2en4es5en2enenenene2ne2nene3n2e4s2ese2sw6s";

    //Greece
    tmpx[14]=495; tmpy[14]=165;
    compass[14]="2se6se3se3ses2eseses2es3e5ne4nwnw2nwnw2n2en7es5enen3e2nwnwn9wwn2wn6ws2wswsws4w";

    //Sweden
    tmpx[15]=504; tmpy[15]=85;
    compass[15]="2n2e2n2e2n5e3nenen2en2wn2wn9w6ws5ws2ws2ws3ws2ws2wsws2wswswswswsw2s2w2sw2swsws2wsws2wsws2ws2wswswsw2sw4sese4s3es3en2en2enen2ese2sese2se3seseses4enen3en2e3ne5ne5nw2n2w2ne2nenenenenenen2enenenenenen5e";

    //UK
    tmpx[16]=442; tmpy[16]=135;
    compass[16]="3nenene2n3wnwnw2nwnwnw2nw2nwnw2nene3nw4n4wswswswsw3sw2sese3sese2se2se2s9w3nw2n5ws2ws2w2sw6ses2en3en2en2en5esw2se3swsw2s3enen5en8e";

    //France
    tmpx[17]=448; tmpy[17]=135;
    compass[17]="ses2es2es3es2es4e3sw2swswswswsw2s2e3se3se2swsws4wn6wsw2s5wn3wn5w5ne6nwnw2nwn2wn3wnw3n5es2ene2n3es3enenenene2n4e";

    //Spain
    tmpx[18]=447; tmpy[18]=164;
    compass[18]="5wn3wn5wn6wn8wn5ws3wsw4se3sw3sw2sw3s2e5sw2s7es2eses2en7en2en2enenene2ne5nenen2enenen2enene2n";

    //W. Germany
    tmpx[19]=448; tmpy[19]=135;
    compass[19]="ses2es2es3es2es4e3sw2s9e5enenene2nwnw4n8wnw4ne2nen2e2nw3nwnw3ne4nwn2ws2wswsw2sesese4s5ws3wswswswsws2wswswsws";

    //Romania
    tmpx[20]=527; tmpy[20]=151;
    compass[20]="nwnwnw2nwnwnwn3ws3ws3ws3wn6w2swsw2sw2swsw4seseses2es6es2e9eene4ne6nen3e";

    //Italy
    tmpx[21]=461; tmpy[21]=146;
    compass[21]="wswswswsw2s2e3se3ses2enen4esesese2se2seseses2es3esese2s3esese3sw3s2ene2ne4nes2ene2n2wn2wn2wnwnwn2w2nwnwnwn2wnwnwnw4nen2e3nwnwn2w2n9w4w";

    //E. Germany
    tmpx[22]=477; tmpy[22]=123;
    compass[22]="ses2e3se7s4ws9wnw4ne2nen2e2nw4n7e";

    //Poland
    tmpx[23]=504; tmpy[23]=140;
    compass[23]="n2e2ne5nw3ne3nwnwnwn9w2wn6ws2ws2ws3w3se7s4eses2es3eses9e3e";

    //Czechosl
    tmpx[24]=501; tmpy[24]=149;
    compass[24]="nene7n9w2wnwn3wn2wnwn8wsw4sese2s4eseses3es2es7es5e";

    //Yugoslavia
    tmpx[25]=478; tmpy[25]=143;
    compass[25]="4eseses3es2es7es5esw2swsw4seseses2e2s2wswsws5w2n3wn2wnwnwnwnwnwnwnwnwn3w3nwnwn2w2nenenene";

    //S. Africa
    tmpx[26]=522; tmpy[26]=435;
    compass[26]="nenenenenenenenenenenenenene2ne2nene5nw9n3nw5n9w2swsws2wswswswsw2sw3sw2swsws3wnwn2wswswsws3w3nwn2w9nne2n2e9n9n4wn3wn3wn9w6wn2w2s2wn2w3se2se2sesese3se2se2se2se5se4se2se6se4se2se2se2se2se2se2se7sese2seses4e2n6en9e2en4en";

    //Egypt
    tmpx[27]=515; tmpy[27]=203;
    compass[27]="9s3se9s9s4s9e9e9es2enenenen3e2nwnw2nw2nw2nw2nw3nw2nw2n2e2ne5nw2nw2n4wn5wn2ws2ws7wn3wn6w";

    //Tunisia
    tmpx[28]=467; tmpy[28]=204;
    compass[28]="enene3ne2ne2n2w4ne3nw4n2wn3w2s2w6swsw2sw2sesese2sese2sese";

    //Morocco
    tmpx[29]=409; tmpy[29]=219;
    compass[29]="7n2en2en2en4enen2en2ene2nen2en5e4nw4nw2n3wn6wnwn2wsw2sw3s2ws2wsws2wswsw2sw2sw4sw4swsws2ws2ws2ws2wswswswsw2swsw2sw2sw2sw2swsw2sw2sw3s9e3e6n3e7ne3n9ee4ne";

    //Algeria
    tmpx[30]=409; tmpy[30]=219;
    compass[30]="7n2en2en2en4enen2en2ene2nen2en5e4nw4nw2n2enenen3enenen7en6es2en6es2e6swsw2sw2sesese2sese2sese9s8sw3sese2s2es2esese2swsws2wsws2ws2ws2wsws2wswswswswsws3ws6wnwnwnwnwnwn2wnwnwn2wnwn2wnwnwnwnwnwn2wn2wnwnwn3w2nwnwn2wnwnwn3w";

    //Libya
    tmpx[31]=467; tmpy[31]=204;
    compass[31]="enene3ne2nee2s2en4es2es3eseseses4es2es2eses3ene7n2en2en3es2es2es2es2e9s4se9s9s9s2s3ws2wn2wn2wn2wn2wn2wnwn2wn2wn2wn2wn2wnwn3ws2ws4wn2wn4w2nwnwn2wn2wnwnw3ne9n8n";

    //Mali
    tmpx[32]=449; tmpy[32]=247;
    compass[32]="3wnwnwnwnwnwn2wnwnwn2wnwn2wnwnwnwnwnwn2wn2wnwnwn6w9sse3se9s9s4s8w7ws2wn2w2sw5sese4s8ese2se2s2es8e6nenene2nenen2en2enen5en6en9ene9n4n";

    //Nigeria
    tmpx[33]=463; tmpy[33]=299;
    compass[33]="nene4nenen4es2ene2ne2ne2ne3ne3ne2nen3e3nw2nw3n2ws9wws7wn6w2n5wswsw9ssw3sw2sw2sw6s6esesese2ses9e";

    //Sudan
    tmpx[34]=516; tmpy[34]=237;
    compass[34]="9e9e9es2enenenen4esese2se4se5sesesese3s4wsw4sw7sw5swsw2swsw2sw3sw4sw2s2w3sesesese2seses2ese4s5wswsws9w4w3n4ws2wnwnwnw3nwnwnw2n2wnwnwn2w2n3w6nwnw5nwnw3nw2ne4ne2ne2nen2e9n6n3e7n";

    //Ethiopia
    tmpx[35]=560; tmpy[35]=253;
    compass[35]="4wsw4sw7sw5swsw2swsw2sw3sw4sw2s2w3sesesese2seses2ese4s4e2s2e2s8e2n5e2sw2sw9s4se2senenen2ene2nenenenenenenenen2enenene2nene2nene2ne2ne2ne2ne2ne2ne2ne2ne3ne5n7ws5ws3ws8wn2w2nwnwn3w3nwnwnwnwn2wnw2nwnw3n2w6n2w";

    //Kenya
    tmpx[36]=536; tmpy[36]=303;
    compass[36]="9eenenen9e2s2e2s8e2n5e2sw2sw9s4se3sw2swswswsw2sw3s2wnwnwn2w3n3wnwn2w2n2wn2wn9w4wnw3nene4ne3nw4n";

    //Zaire
    tmpx[37]=476; tmpy[37]=337;
    compass[37]="5n9enene2ne4ne3nenenen2e9nne5ne5n7e2s6enen8en6eseseses2en4e3s3e4se3sw4swsw3sw2sw2sw9s2se2se4se2se2se2s5wsw2swsw2se3s2es2e7sws3wnwnwnwnwn5wn2wn3wn7w4nw8nwnwn3wn3w4s7w2nw2nw4n9w3ws2w";

    //Tanzania
    tmpx[38]=564; tmpy[38]=332;
    compass[38]="2wnwnwn2w3n3wnwn2w2n2wn2wn9w4wn2w2sw2sw9s2se2se4se2se2se2seses2eses2eses4e4se2s2es2en6en4en2e5nw9n9n";

    //Mozambique
    tmpx[39]=549; tmpy[39]=357;
    compass[39]="2es2en6en4en5e9s7sw2s2ws2ws2ws2ws2wsw2swswsws2wsw2sw2sw5se9sw2s2ws3ws2w5sws2w9n3nw6nene2ne2ne2ne2ne7nw2nwnwnwn2w4ne2n2en5enenene5nen";

    //Zambia
    tmpx[40]=537; tmpy[40]=345;
    compass[40]="6wsw2swsw2se3s2es2e7sws3wnwnwnwnwn5wn2wn4w5sws5wsw9s2sesese2s9en3en4en3es4enenen3e4ne2n2en5enenene5ne3nw4n4wnwn2wnwn2wnwnw";

    //Angola
    tmpx[41]=473; tmpy[41]=377;
    compass[41]="3ne4ne2ne3ne2ne2ne3ne6nw3nw3ne3nw3nw3nen9e3e4se2se2se7e4n3es3esese8se3s6e6sws5wsw9s2sesese3s2ws8wn3wn3wn9w6wn2w2s2wn2w";

    //Japan
    tmpx[42]=849; tmpy[42]=205;
    compass[42]="6ne2nen2ene2n3eses3e2n3en3en2ene7nw7nw2nwnwnwnwnw4n2es2ene2nene3n3wn2wn2wn4wnwn2w3sese3swsw3ses4e5se3se5sw2swswsws2w3s7ws2wswswswsw2sw3sese3se2ses2e";

    //N. Korea
    tmpx[43]=814; tmpy[43]=174;
    compass[43]="2n2e2n2enen4enenen3ese4swsw2swsw2s2eseses3wsws5wnwnw4nwn3w";

    //S. Korea
    tmpx[44]=825; tmpy[44]=181;
    compass[44]="nen4eseses2e2s3ese4sw2sws2wsws2ws2w2nw5nw3nwnwn";

    //Australia
    tmpx[45]=798; tmpy[45]=440;
    compass[45]="4en4en3en2en8es4en3ene2n2en2en2en3en9e7es2es2e2se2se4s3enwnwn2en2e2swsw2sw2swes3ese4sw2seses3es6en2e2s7en2en4en3e2ne2nenenen2enenene2nenenenenenenen2enenenene2nene3ne2ne2ne5ne3ne3nwnw4nw2nwnwnwnw2nw2nw2nw2nwnw2nwnwnw3nw9nnw2nw2nw2nw2nw3nw2nwn2w2sw2sw3sw4sw5sw2sw2sw3ws3wn2wnwn2wn2wnwn2w5ne2nene2ne3n9wwn2wn3w3s4ws2wswsw6sws2wn5w2nwn3wsws2wsws2w2swswswsw2s3wswsw2swswswsws2ws3ws2ws2ws3ws3ws4ws2ws2ws2wswsw4sw4sw6sw9s2se9ssw2swsw4seses";

    //China
    tmpx[46]=830; tmpy[46]=162;
    compass[46]="wnwnwnw3nen3e2ne2nw4nw3n3ws2ws6wnwnwn2wnwn2wn5wn2wn2wnwnwnwnwnwn2wnwnwnwn3wn3wn9wsw2sese9s5w7s2es4en6esese2s4ws2ws2wsws2ws2ws4wn2w3se5s2ws7ws3ws2ws8wn3wn3wn3ws7wn5wnw2n2wn2wn3wn2wn2wn3wn4wn2w3nw2nwnwnwnwn5wn2wnw3n5w5sw2s5wswsw5s3ws2w3se2se2se4s2w2sw2sw2sw3sws2ws4ws3wsw2se3s7eses2es2e2s5en4ese2se2sw9s2ses2eses3es3es3eses6es5es2es2es5es2es2en6en3enenen2en5eseses2es5e3se2se5swsw3ses2es2e2sese4seses4ene3nen7enen3es3ese2ses2es5es6en2en2en2en5en4enenenenenenenenen2e5ne2ne2ne9nw2nw2nw2nwnwnw2nwn2wnwnwnwnwnw4nenenen3e2n2wn2wn3wsws3w2nwn3wnw3n2enene2nenen2esese3s5en2e2n2e2n2enen4enenen3es2e4n";

    //Vietnam
    tmpx[47]=778; tmpy[47]=278;
    compass[47]="4se2s3enenen2ene2nenenenene9nw2nw2nw2n2wnwnwnwnwnwnwnwnwnw2nw2nen3e7nwnw2nwn3wn3wsws7wsw3sws3w3se3s2ese5s3en5es2esesese2sese5swsws5wsw3seses2e2ses3en3e4s2wsws";

    //Turkey
    tmpx[48]=526; tmpy[48]=169;
    compass[48]="swsws4wsw4se3se2se3s2es7en4eses5en3en4es2en4en7en9e4e4nw7nw2nw2n3wn5w2s2ws5wn7wn3wnwn9wsws7w";

    //Syria
    tmpx[49]=549; tmpy[49]=186;
    compass[49]="6sw2s3e2sw4s3enen2en2enen2enen2e4ne3ne3n5ws7ws4wsw";

    //Israel
    tmpx[50]=547; tmpy[50]=199;
    compass[50]="sw3sw2sw2se2se2nene2ne2ne3n3w";

    //Taiwan
    tmpx[51]=831; tmpy[51]=229;
    compass[51]="2nw4nenenene2n3e3sw4sw3sws3w";

    //Iraq
    tmpx[52]=574; tmpy[52]=183;
    compass[52]="8w3sw3sw4s2wsws2wsw3se2s3es2es3eseseseses2es2eseses8e4n3e2nw2nw3n2wnwnwnwnwnwnw3nene2nwnwnwnwnw2nw";

    //Saudi Arabia
    tmpx[53]=559; tmpy[53]=201;
    compass[53]="3es2es3eseseseses2es2eseses8eeseses2esesesesese2s2e2s2e2sese2ses7enen2e2nenen2e3ses4e2sesesesesese3sw3sw2swswsw2swswsw2s2ws2wswsw2s2ws5wswsw2s2wsws2ws2ws3ws2ws2ws2ws2ws2w2s2ws3wn2w2nw2nw2nw9nwnwnwnwnw2nw2nw2nwnwn2w2nwnw3nw3nw3nwnwnw2nwnw2nwnw2nwnwnw2nwnwnw2nw3n2es3en3e2n4n3ene3n";

    //Iran
    tmpx[54]=588; tmpy[54]=208;
    compass[54]="2nw2nw3n2wnwnwnwnwnwnw3nene2nwnwnwnwnw2nw4nw6n4es3en5e3s2e4seseseses2es2es5en2ene2n2enen3en3es2es3es2es2es2es2ese8sw2se2se5sesese2sw3se2seses2esesesese2sws3wsw4s9wwn2wnwnw2nw2n2ws2ws6wn3wn2wnwnwnwnwnwnwnwnwnwn2wn4w";

    //Pakistan
    tmpx[56]=633; tmpy[56]=226;
    compass[56]="4nen3ene2nwnwnwnwn2wnwnw2n6en9e3n2enen2en3e2ne4nene2n2e2ne2nw4nenen9eses2es2e2s2e2sws8w5sesesese6sw2sw2sw3sw3s2wn3ws2wswsw3sese2sesese3s7ws2wn2wnwn2wnwn4ws6ws3wn2w";

    //Afghanistan
    tmpx[55]=629; tmpy[55]=210;
    compass[55]="3ne2nwnwnw5nw2nw2ne5n3es2enenen2e2ne2n3en9e2enenenen2eseses5e3s2wswsw4se2sw2s2w2swsw4sw2s4ws2wsws2w3s9ws7w";

    //India
    tmpx[57]=656; tmpy[57]=229;
    compass[57]="4ses3e2sw3se2s3es2en2ene2n2e4se8se4se3sese3se3sese3sese2se3sese2sese3se3se2ses2en2en2e4ne4ne4ne9n4nen2enenenenenenenenenenene2nenenene2nenen2en3en3en2ene2nen4es2e2nenene2ne6nenenen2e4n2wnwnwn5ws2wswsws3ws6ws2wn2wn5wn2wn2wn5wn6wnwn3wn3wn3wnwn2wnw9n2ne2nw2nwn4ws3w2sws8w5sesesese6sw2sw2sw3sw3s2wn3ws2wswsw3sese2sesese3s7w";

    //Burma
    tmpx[58]=733; tmpy[58]=233;
    compass[58]="4se2sese2se2se2se2se2se4se2sese2ses2e2nenenene2ne7nen2en2en2en3nwnwnw4nwnw2n2wn2wnw3nene5nw2nw3n5w3s2wswswsw6sw2swswsw2s2w";

    //Thailand
    tmpx[59]=752; tmpy[59]=253;
    compass[59]="ese2se2se5se3se2se2sw3sw3sw3sw3s2e4s2ese2sesese2se2se3se2se3se2s2ese2ses2es3e5nw4nw3nw2nwn2wnwnwnwnwnwnwnwnw2nw2nwnw7ne4ne2n3e2s2es2ese2seseseses4enen2e4n3ws3wnw2n2wnwnw3nen5enene5nwnw2nwnwnwn2wn5ws3w5nwn2w3n3ws2ws2wsw7s";

    //Indonesia - Sumatra+Java
    tmpx[60]=748; tmpy[60]=296;
    compass[60]="3se2seses2esesese2sesese2sese2se2se2sese2se2se2seseseseseseseseseses3e2s2e2seses2es2es7es2es9e3es7es6e2n4wn4wn4wn4wn2wn2wnwn2ws2ws3wn2wn2wnwn4wn2w9nnwnwnwnwnwnwnw2nw2nwnwnwn2wnw2n3wnwnwnwnw2nwnwnwnwnwn3wn3wn2w";

    //Philippines
    tmpx[61]=825; tmpy[61]=251;
    compass[61]="3sw4se3se2ses2e5sesese2s2es2e2se2s3e2se3sw3s2w2s3e2se3seseses2ene2ne2ne2nw8nw2nwsw4s2wnw4ne6nwnwn2w5n3wn2ws2w2n9n3nwn6w";

    //Guatemala
    tmpx[62]=135; tmpy[62]=261;
    compass[62]="2seses2es3enene3n3e2ne2nw3n2e4nwsws4wn2wsw3se3s4wsw2sw";

    //El Salvador
    tmpx[63]=144; tmpy[63]=264;
    compass[63]="3n3eses2e4swn2wn2wnw";

    //Costa Rica
    tmpx[64]=155; tmpy[64]=275;
    compass[64]="4seses2ese2seseses2ene4n2wnw2nw4n7w";

    //Mauritania
    tmpx[65]=394; tmpy[65]=262;
    compass[65]="3e2n2es2en9e7e9n9n3nw3nw9nn3e2nwnwn2wnwnwn4w4s9ww3sw7s3w6s9w4w2se2se4se5sw4s6eses2e2seses";

    //Guinea
    tmpx[66]=382; tmpy[66]=256;
    compass[66]="5sw7se2se2sesesese2sesesesese3se2ses2e3nw2n2ene2nenenenenen4e2nwn8w4nwnw5n2wnwnw2n2wnwn7w";

    //Ivory Coast
    tmpx[67]=395; tmpy[67]=285;
    compass[67]="e5seseseses2eseseses2es8e2n9e2e8ne7n3wnwn4w2n9wn2w2n5wswswswswsw2sws2w2s";

    //Burkina Faso
    tmpx[68]=427; tmpy[68]=282;
    compass[68]="5n9eeses2es8e9nn2w3n5w2n2w3n6ws5wsws2ws2wswsw2swswsw6se2s4eses3e";

    //Ghana
    tmpx[69]=426; tmpy[69]=297;
    compass[69]="eses3enenenen2en3en5e6ne2ne2ne3n7wn2wnwn9ww9s3sw8s";

    //Niger
    tmpx[70]=448; tmpy[70]=270;
    compass[70]="enenen5e2s6es7en9ee5ne2ne2nenenenene9n3ne2nw2nw2nw4n4wn2wn5wsws2wsws2ws2ws2wsws2wswswswswsws3ws3w9s4sws9w4s2e2s5e3s2e";

    //Chad
    tmpx[71]=479; tmpy[71]=268;
    compass[71]="2e3se2se3se4s2wswsesesese2ses9e2e2ne2n4enenenenenenen2e3nwnw3nw2ne4ne2ne2nen2e9n5n2wn2wn2wn2wn2wn2wnwn2wn2wn2wn2wn2wnwn3ws2w5se2se2se2sw9s3swswswswsw2sw2sw4s";

    //Cameroon
    tmpx[72]=468; tmpy[72]=307;
    compass[72]="6en9e2e2nw5nw4ne3ne3ne2nw2nwnwnwnwnen2e4n4wsw2sw3sw3sw2sw2sw2sws2wn4wswsw4swsw2ses2esese4s";

    //C. Africa
    tmpx[73]=483; tmpy[73]=299;
    compass[73]="4ne3ne3nen9e2e2ne2n4enenenenenenen2e2sese6s3e2s2eseses2e2sesese2s6ws8wsws6w2n7w3s3wn6wn4w";

    //Congo
    tmpx[74]=467; tmpy[74]=307;
    compass[74]="3sw5sw4se2sese2sese2sese2seses2en9enene2ne4ne3nenenen2e9nne5ne2n3wn6wn3w5se2s9w2ws7w";

    //Zimbabwe
    tmpx[75]=528; tmpy[75]=395;
    compass[75]="9enene2ne2ne2ne2ne7nw2nwnwnwn4wswsws4wn3ws4ws3ws3wsesese2se2sesesese2sesesese2s";

    //Botswana
    tmpx[76]=501; tmpy[76]=410;
    compass[76]="2ese3s3enenenen2eses3enene2ne3ne2nenenenen2enene4nwnwnwnw2nwnwnwnw2nw2nwnwnwn6ws2ws4w9s9s2w2sw9ss";

    //Jordan
    tmpx[77]=547; tmpy[77]=211;
    compass[77]="2nw2nene2ne2ne2n3enen2en2e2se5sws3w4sw2s3ws3wnw";

    //Lebanon
    tmpx[78]=547; tmpy[78]=199;
    compass[78]="3e3ne2n3wsw4s";

    //Bolivia
    tmpx[79]=218; tmpy[79]=396;
    compass[79]="2nw2nw3nw3nw2nw4n2wnw3ne4nw9ne5n2w2nw2n5enenen3en3e5seseseseses3es2eses2eses2esese2se3ses3es2e2sesese7s5wn3ws5w4sw3sw2s4ws2wn3wn3w2s2ws2w";

    //minor elements
    //USA - Alaska
    tmpx[80]=107; tmpy[80]=75;
    compass[80]="sws2wswsws2wswswsws3wswswsws2wswsws2wswswswsws2wswswsws2wsw5s2wn7wn3wn3wn4w2s2wnwn4wsw4s4wnwn5ws2wswsw2swswswswsws3w3n2wsws4ws4ws3ws3ws3ws2ws2w2nenen3en3en3en4en4ene2n3wn2ws4w2n2ene3nw4n2enen2enen5en6en4enen2e2n9w3w2n2e2n7en2en2es2es2en5e2nwn2wnw4n2en4en4en4en3en6en3en9e3es6es9es9eses";

    //Indonesia - Borneo+Celebes
    tmpx[81]=798; tmpy[81]=327;
    compass[81]="2nw2nw3nwnw2nw3nw3nen2en5enenenenenenenen2en2enenenenenenenen3esesesese4swswsw5se2sese3swsw2sw2swsw2sw2s8e3nenen2e2s7e2s3w3sese2se3se4s2wnw2nwn2w5n3w9s3w3ne2nw2nw3n8w2sw2s2ws3wnwn3ws3wn3wn4w";

    //Indonesia - Papua
    tmpx[82]=870; tmpy[82]=331;
    compass[82]="2nw6nwnwn2w2nenen7es2e8ses3enen2en2en8es2es3es2es3es2es4e2s4ese3sese2se3seseseseseseseseses2es2es2eseses2e2s5wn3wn2wn2wn3wn2wn2wnwn2wnw2nwnwn3ws2wswswswsws2wn3wnwnwn7w3n2e4nw2nwnwn3wn3wn4wn2wn5w";

    //Israel - big
    tmpx[83]=32; tmpy[83]=502;
    compass[83]="3w4nw3nw3nw2nw4n2w6nwnw2nw2nw3nw6nenenenene3n2e5ne2ne3ne4ne5ne2ne5n4es2enene2n2e9ssw7s2wnwn4wsw2sw8sesese2s2wswsw4s6en2e9ssw2sw4sw2sw9sw6sw4s";

    //Jordan - big
    tmpx[84]=31; tmpy[84]=502;
    compass[84]="3ses9e2es8enen2enen2e2nenenene3n4en6ene2nene2ne2nenenen2e3nwnwnwnw2nwnwnwnw2nwnwnwnwnw2n4en4en3en4en3en4en4en3en6en3enen2e2nwnw2nw2nw2nw3n2w2nw2nw2nw2nwnw2nw2nw2nw2n3ws2wsws2wswsws2wsws2wsw2s3wsws2ws2wswswsws2wsws2wsws6wnwn4w2nwnwn7w7s2wnwn4wsw2sw8sesese2s2wswsw4s6en2e9ssw2sw4sw2sw9sw6sw4sw";

    //Lebanon - big
    tmpx[85]=32; tmpy[85]=433;
    compass[85]="3es2enene2n2en2enenenene2nw2nenen3e2nen2e2nene5nwnwnw2n8w2swswsw2swsw7sw2s2w2sw3swsw3sw3sws";

    //Guatemala - big
    tmpx[86]=22; tmpy[86]=322;
    compass[86]="5ne4ne2ne2ne2n9e2ene2nwnw2nwnwnw2n2e5nen9e5en3enenen2ese2sw3sw8swswswswswsw2ses2ese2s3wsws2wswsw4sw2s2wswswsws2ws2wn3ws2wn3wnwnwnwn3w";

    //Honduras - big
    tmpx[87]=59; tmpy[87]=334;
    compass[87]="3e2n2e5n4enen2es2en2enene2nene2n3es3en5en2e2n2wn4w2ne2n4wn4ws3wnwn3wsws9wwn3ws2ws2ws3wsws2wswsw4sw3s2eseseses2en2es3e4s2e3s";

    //El Salvador - big
    tmpx[88]=38; tmpy[88]=328;
    compass[88]="2n2enenenen2es2eseseses2en2es3e4s2w2s3wn6wnwn6w2nw";

    //Nicaragua - big
    tmpx[89]=57; tmpy[89]=334;
    compass[89]="3sesesesesese2sesesesese2ses5es7eses5e2nwnw2ne2ne5ne3nw2nene7ne2nenene5nw3n2ws5ws3wn3w2swsw2swsws2ws2wn2wsws4w5s2w2s5w";

    //Costa Rica - big
    tmpx[90]=71; tmpy[90]=351;
    compass[90]="5swsw3ses2es2e2n2es2ese3s2es2eses2e5s4e3s2e4ne3nw4n2e2nwn2wnw2nwnw2nw2n5wnwn7wn3w";

    //Panama - big
    tmpx[91]=92; tmpy[91]=376;
    compass[91]="5es3esese2s3en2e5s4en3e3nw2n2w2ne2n4ene2n2enen4es2e2ses3e3swsw4seseses2e3n2en2e4nw4nwnwnwnwnwnwn2wn5wn5ws2w2s2ws4wsws7wn4wnw3n3wn2w4se3sw4s";

    //i==92
    for(int i=0;i<92;i++){
        countryShape[i].append(QPoint(tmpx[i],tmpy[i]));
        for(int j=0;j<compass[i].length();j++){
            if(compass[i][j]>=48&&compass[i][j]<=57){
                delta=compass[i][j]-48;
                j++;
            }
            else delta=1;
            if(compass[i][j]=='n') tmpy[i]-=delta;
            if(compass[i][j]=='s') tmpy[i]+=delta;
            if(compass[i][j]=='e') tmpx[i]+=delta;
            if(compass[i][j]=='w') tmpx[i]-=delta;
            countryShape[i].append(QPoint(tmpx[i],tmpy[i]));
        }
        if(i<80) mypath[i].addPolygon(countryShape[i]);
    }
    mypath[0].addPolygon(countryShape[80]);
    mypath[60].addPolygon(countryShape[81]);
    mypath[60].addPolygon(countryShape[82]);
    mypath[50].addPolygon(countryShape[83]);
    mypath[77].addPolygon(countryShape[84]);
    mypath[78].addPolygon(countryShape[85]);
    mypath[62].addPolygon(countryShape[86]);
    mypath[3].addPolygon(countryShape[87]);
    mypath[63].addPolygon(countryShape[88]);
    mypath[4].addPolygon(countryShape[89]);
    mypath[64].addPolygon(countryShape[90]);
    mypath[5].addPolygon(countryShape[91]);

    for(int i=0;i<80;i++)
        createShapeItem(mypath[i],tr(""),QPoint(0,0),QColor(255,255,255));

}

bool MainBox::event(QEvent *event){
    if (event->type() == QEvent::ToolTip) {
        QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
        int index = itemAt(helpEvent->pos());
        if (index != -1) {
            QToolTip::showText(helpEvent->globalPos(), shapeItems[index].toolTip());
            if((mapMode>=8&&mapMode<=26)||mapMode==39){
                countryHighlight->setText(shapeItems[index].toolTip());
                countryHighlight->adjustSize();
            }
        } else {
            QToolTip::hideText();
            if((mapMode>=8&&mapMode<=26)||mapMode==39){
                countryHighlight->setText(resrc.strg[28]);
                countryHighlight->adjustSize();
            }
            event->ignore();
        }

        return true;
    }
    return QWidget::event(event);
}

void MainBox::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    foreach (ShapeItem shapeItem, shapeItems) {
        painter.translate(shapeItem.position());
        painter.setBrush(shapeItem.color());
        painter.drawPath(shapeItem.path());
        painter.translate(-shapeItem.position());
    }
    painter.setBrush(Qt::NoBrush);
    painter.drawLine(12,391,12,285);
    painter.drawLine(12,285,70,285);
    painter.drawLine(70,285,158,361);
    painter.drawLine(158,361,158,391);
    painter.drawLine(158,391,12,391);
    painter.drawRect(12,401,120,111);

}

void MainBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        int index = itemAt(event->pos());
        if(index<N){
        if (index != -1) {
            curSelection=index;
            if((mapMode>=8&&mapMode<=16)||mapMode==39){
                drawMap(mapMode,curSelection,curIOMode);
                countryHighlight->setText(resrc.strg[28]);
                shapeItems[index].setColor(QColor(0,0,0));
                countryHighlight->adjustSize();
            }
            else if((mapMode>=18&&mapMode<=26)){
                if(index>1) { curSelection=curAddParam; drawMap(mapMode,curAddParam,curIOMode); update(); return; }
                else {
                    curAddParam=index;
                    drawMap(mapMode,curAddParam,curIOMode);
                    countryHighlight->setText(resrc.strg[28]);
                    shapeItems[index].setColor(QColor(0,0,0));
                    countryHighlight->adjustSize();
                }
            }
            else {
                drawMap(mapMode,curAddParam,curIOMode);
                countryHighlight->setText(shapeItems[index].toolTip());
                shapeItems[index].setColor(QColor(0,0,0));
                countryHighlight->adjustSize();
            }
            if(index>1) selectCountryEffect();
            else selectSuperPowerEffect();
            update();
        }
        else {
            if((mapMode>=8&&mapMode<=26)||mapMode==39){
                mapModeAct[1]->setChecked(true);
                curSelection=0;
                curAddParam=0;
                mapMode=1;
                curIOMode=0;
                drawMap(mapMode,curSelection,curIOMode);
                update();
            }
            else {
                curSelection=-1;
                drawMap(mapMode,curAddParam,curIOMode);
                update();
                countryHighlight->setText(resrc.strg[153]);
                countryHighlight->adjustSize();
            }
            selectNothingEffect();
        }
        }
    }
    if(event->button()==Qt::RightButton){
        int index = itemAt(event->pos());
        if(index<N){
            if (index != -1) {
                curSelection=index;
                if((mapMode>=8&&mapMode<=16)||mapMode==39){
                    drawMap(mapMode,curSelection,curIOMode);
                    countryHighlight->setText(resrc.strg[28]);
                    shapeItems[index].setColor(QColor(0,0,0));
                    countryHighlight->adjustSize();
                }
                else if((mapMode>=18&&mapMode<=26)){
                    if(index>1) { curSelection=curAddParam; drawMap(mapMode,curAddParam,curIOMode); update(); return; }
                    else {
                        curAddParam=index;
                        drawMap(mapMode,curAddParam,curIOMode);
                        countryHighlight->setText(resrc.strg[28]);
                        shapeItems[index].setColor(QColor(0,0,0));
                        countryHighlight->adjustSize();
                    }
                }
                else {
                    drawMap(mapMode,curAddParam,curIOMode);
                    countryHighlight->setText(shapeItems[index].toolTip());
                    shapeItems[index].setColor(QColor(0,0,0));
                    countryHighlight->adjustSize();
                }
                if(index>1) selectCountryEffect();
                else selectSuperPowerEffect();
                update();
                if(index==0) {
                    contTitle->setText("United States");
                    contMenu[0]->exec(QCursor::pos());
                }
                else if(index==1) {
                    contTitle->setText("Soviet Union");
                    contMenu[1]->exec(QCursor::pos());
                }
                else if(index>1&&index<N){
                    contTitle->setText(resrc.strg[154+index]);
                    contMenu[2]->exec(QCursor::pos());
                }
            }
        }
        else {
            if((mapMode>=8&&mapMode<=26)||mapMode==39){
                mapModeAct[1]->setChecked(true);
                curSelection=0;
                curAddParam=0;
                mapMode=1;
                curIOMode=0;
                drawMap(mapMode,curSelection,curIOMode);
                update();
            }
            else {
                curSelection=-1;
                drawMap(mapMode,curAddParam,curIOMode);
                update();
                countryHighlight->setText(resrc.strg[153]);
                countryHighlight->adjustSize();
            }
            selectNothingEffect();
        }
    }
}

void MainBox::mouseDoubleClickEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        int index = itemAt(event->pos());
        if(index<N){
        if (index != -1) {
            curSelection=index;
            if((mapMode>=8&&mapMode<=16)||mapMode==39){
                drawMap(mapMode,curSelection,curIOMode);
                countryHighlight->setText(resrc.strg[28]);
                shapeItems[index].setColor(QColor(0,0,0));
                countryHighlight->adjustSize();
            }
            else if((mapMode>=18&&mapMode<=26)){
                if(index>1) { curSelection=curAddParam; drawMap(mapMode,curAddParam,curIOMode); update(); return; }
                else {
                    curAddParam=index;
                    drawMap(mapMode,curAddParam,curIOMode);
                    countryHighlight->setText(resrc.strg[28]);
                    shapeItems[index].setColor(QColor(0,0,0));
                    countryHighlight->adjustSize();
                }
            }
            else {
                drawMap(mapMode,curAddParam,curIOMode);
                countryHighlight->setText(shapeItems[index].toolTip());
                shapeItems[index].setColor(QColor(0,0,0));
                countryHighlight->adjustSize();
            }
            if(index>1) selectCountryEffect();
            else selectSuperPowerEffect();
            update();
            showCountryCloseUp();
        }
        else {
            if((mapMode>=8&&mapMode<=26)||mapMode==39){
                mapModeAct[1]->setChecked(true);
                curSelection=0;
                curAddParam=0;
                mapMode=1;
                curIOMode=0;
                drawMap(mapMode,curSelection,curIOMode);
                update();
            }
            else {
                curSelection=-1;
                drawMap(mapMode,curAddParam,curIOMode);
                update();
                countryHighlight->setText(resrc.strg[153]);
                countryHighlight->adjustSize();
            }
            selectNothingEffect();
            }
        }
    }
}

void MainBox::selectNothingEffect(){
    for(int i=8;i<23;i++)
        mapModeAct[i]->setDisabled(true);
    for(int i=0;i<8;i++)
        doPolicy[i]->setDisabled(true);
    mapModeAct[36]->setDisabled(true);
    doCloseUp->setDisabled(true);
    doEconomy->setDisabled(true);
    doHistory->setDisabled(true);
    doNews[0]->setDisabled(true);
}

void MainBox::selectCountryEffect(){
    selectNothingEffect();
    for(int i=8;i<18;i++)
        mapModeAct[i]->setDisabled(false);
    if(core.level==1) for(int i=2;i<6;i++) doPolicy[i]->setDisabled(false);
    if(core.level==2) for(int i=0;i<6;i++) doPolicy[i]->setDisabled(false);
    if(core.level>=3) for(int i=0;i<8;i++) doPolicy[i]->setDisabled(false);
    if(core.level==4) mapModeAct[36]->setDisabled(false);
    doCloseUp->setDisabled(false);
    doEconomy->setDisabled(false);
    doHistory->setDisabled(false);
    doNews[0]->setDisabled(false);
}

void MainBox::selectSuperPowerEffect(){
    selectNothingEffect();
    if(core.level==1) for(int i=8;i<18;i++) mapModeAct[i]->setDisabled(false);
    if(core.level==2) for(int i=8;i<20;i++) mapModeAct[i]->setDisabled(false);
    if(core.level>=3) for(int i=8;i<23;i++) mapModeAct[i]->setDisabled(false);
    if(core.level==4) mapModeAct[36]->setDisabled(false);
    doCloseUp->setDisabled(false);
    doEconomy->setDisabled(false);
    doHistory->setDisabled(true);
    doNews[0]->setDisabled(true);
}

int MainBox::itemAt(const QPoint &pos){
    for (int i = shapeItems.size() - 1; i >= 0; --i) {
        const ShapeItem &item = shapeItems[i];
        if (item.path().contains(pos - item.position()))
            return i;
    }
    return -1;
}

void MainBox::createShapeItem(const QPainterPath &path,
                                 const QString &toolTip, const QPoint &pos,
                                 const QColor &color){
    ShapeItem shapeItem;
    shapeItem.setPath(path);
    shapeItem.setToolTip(toolTip);
    shapeItem.setPosition(pos);
    shapeItem.setColor(color);
    shapeItems.append(shapeItem);
    update();
}

QPoint MainBox::initialItemPosition(const QPainterPath &path){
    int x;
    int y = (height() - (int)path.controlPointRect().height()) / 2;
    if (shapeItems.size() == 0)
        x = ((3 * width()) / 2 - (int)path.controlPointRect().width()) / 2;
    else
        x = (width() / shapeItems.size()
             - (int)path.controlPointRect().width()) / 2;
    return QPoint(x, y);
}
