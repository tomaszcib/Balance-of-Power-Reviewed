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

#include "mainbox.h"

void MainBox::drawMap0(){ selectNothingEffect();drawMap(0,0,0);}
void MainBox::drawMap1(){ selectNothingEffect();drawMap(1,0,0);}
void MainBox::drawMap2(){ selectNothingEffect();drawMap(2,0,0);}
void MainBox::drawMap3(){ selectNothingEffect();drawMap(3,0,0);}
void MainBox::drawMap4(){ selectNothingEffect();drawMap(4,0,0);}
void MainBox::drawMap5(){ selectNothingEffect();drawMap(5,0,0);}
void MainBox::drawMap6(){ selectNothingEffect();drawMap(6,1,0);}
void MainBox::drawMap7(){ selectNothingEffect();drawMap(7,0,0); }
void MainBox::drawMap8(){ drawMap(8,curSelection,0);}
void MainBox::drawMap9(){ drawMap(8,curSelection,1);}
void MainBox::drawMap10(){ drawMap(10,curSelection,0);}
void MainBox::drawMap11(){ drawMap(10,curSelection,1);}
void MainBox::drawMap12(){ drawMap(12,curSelection,0);}
void MainBox::drawMap13(){ drawMap(12,curSelection,1);}
void MainBox::drawMap14(){ drawMap(14,curSelection,0);}
void MainBox::drawMap15(){ drawMap(14,curSelection,1);}
void MainBox::drawMap16(){ drawMap(16,curSelection,0);}
void MainBox::drawMap17(){ drawMap(16,curSelection,1);}
void MainBox::drawMap18(){ drawMap(18,curSelection,0);}
void MainBox::drawMap19(){ drawMap(20,curSelection,0);}
void MainBox::drawMap20(){ drawMap(22,curSelection,0);}
void MainBox::drawMap21(){ drawMap(24,curSelection,0);}
void MainBox::drawMap22(){ drawMap(26,curSelection,0);}
void MainBox::drawMap23(){ selectNothingEffect();drawMap(33,0,0);}
void MainBox::drawMap24(){ selectNothingEffect();drawMap(33,1,0);}
void MainBox::drawMap25(){ selectNothingEffect();drawMap(34,0,0);}
void MainBox::drawMap26(){ selectNothingEffect();drawMap(34,1,0);}
void MainBox::drawMap27(){ selectNothingEffect();drawMap(34,2,0);}
void MainBox::drawMap28(){ selectNothingEffect();drawMap(35,0,0);}
void MainBox::drawMap29(){ selectNothingEffect();drawMap(35,1,0);}
void MainBox::drawMap30(){ selectNothingEffect();drawMap(35,2,0);}
void MainBox::drawMap31(){ selectNothingEffect();drawMap(36,0,0);}
void MainBox::drawMap32(){ selectNothingEffect();drawMap(36,1,0);}
void MainBox::drawMap33(){ selectNothingEffect();drawMap(36,2,0);}
void MainBox::drawMap34(){ selectNothingEffect();drawMap(37,0,0);}
void MainBox::drawMap35(){ selectNothingEffect();drawMap(38,0,0);}
void MainBox::drawMap36(){ drawMap(39,curSelection,0);}
void MainBox::showNewsp(){ showNewsWindow(0); }
void MainBox::showUSAA(){ showNewsWindow(1); }
void MainBox::showUSAO(){ showNewsWindow(2); }
void MainBox::showUSSRA(){ showNewsWindow(3); }
void MainBox::showUSSRO(){ showNewsWindow(4); }
void MainBox::showMIN(){ showNewsWindow(5); }
void MainBox::doDestab(){ showPolcyWindow(0); }
void MainBox::doEconAid(){ showPolcyWindow(1); }
void MainBox::doMilAid(){ showPolcyWindow(2); }
void MainBox::doRebAid(){ showPolcyWindow(3); }
void MainBox::doMilIntv(){ showPolcyWindow(4); }
void MainBox::doRebIntv(){ showPolcyWindow(5); }
void MainBox::doPress(){ showPolcyWindow(6); }
void MainBox::doTreaty(){ showPolcyWindow(7); }
void MainBox::doAbout(){ aboutBox.exec(); }

void MainBox::showCountryCloseUp(){
    clsUp.setModal(true);
    clsUp.setParent(this,Qt::Dialog);
    clsUp.setWindowTitle(resrc.strg[curSelection+154]+" - close-up");
    bool visible; QString arrow;
    for(int i=0;i<20;i++) clsUp.paramName[i]->setText("");
    for(int i=0;i<24;i++) clsUp.sprpwrVal[i]->setText("");
    for(int i=0;i<12;i++) clsUp.otherVal[i]->setText("");
    for(int i=0;i<20;i++){
        if(i>5&&i<12&&core.level==1) {clsUp.paramName[i]->setText(""); continue; }
        if(i>7&&i<12&&core.level==2) {clsUp.paramName[i]->setText(""); continue; }
        if(curSelection<2&&i<2) { clsUp.paramName[i]->setText(""); continue; }
        clsUp.paramName[i]->setText("<b>"+resrc.strg[475+i]+"</b>");
        clsUp.paramName[i]->adjustSize();
    }
    int DAij, sum, oldVal, maxVal=5, maxNum=5, x,y,mode,val;
    if(curSelection>1){
        clsUp.topHead[0]->setText("<b>USA Value</b>");
        clsUp.topHead[1]->setText("<b>USSR Value</b>");
        clsUp.topHead[2]->setText("<b>Totals</b>");
        clsUp.hint->setText("Values in {brackets} are maximum possible");
        for(int spr=0;spr<2;spr++){
            core.MaxPolcy(spr);
            DAij=core.state[curSelection].overallRelationship[spr];

            for(int i=0;i<12;i++){
                visible=true;
                if(i==0) { maxVal=127; mode=8;val=DAij; }
                else if(i==1) { val=(DAij*core.state[curSelection].prestVal)/1024; clsUp.sprpwrVal[spr*12+1]->setText(QString::number(val)); continue;}
                else if(i==2){
                    mode=10;
                    maxVal=core.MilMax(DAij);
                    if(core.MaxCAid<maxVal) maxVal=core.MaxCAid;
                    oldVal=core.state[curSelection].OMilAid[spr];
                    val=core.state[curSelection].milAid[spr];
                }
                else if(i==3){
                    mode=12;
                    val=core.state[curSelection].rebAid[spr];
                    maxVal=core.MaxCAid;
                    x=0;
                    if(core.state[curSelection].strengthRatio<512) x=1;
                    if(core.state[curSelection].strengthRatio<128) x=2;
                    if(core.state[curSelection].strengthRatio<32) x=3;
                    if(core.state[curSelection].strengthRatio<8) x=4;
                    if(core.state[curSelection].strengthRatio<2) x=5;
                    if(x<maxVal) maxVal=x;
                    x=core.RebAMax(spr,curSelection);
                    if(x<maxVal) maxVal=x;
                    oldVal=core.state[curSelection].ORebAid[spr];
                }
                else if(i==4){
                    mode=14;
                    val=core.state[curSelection].milIntv[spr];
                    x=core.state[curSelection].treaty[spr];
                    oldVal=core.state[curSelection].OMilIntv[spr];
                    maxVal=core.IntvGMax(x,DAij);
                    if(core.MaxCIntv<maxVal) maxVal=core.MaxCIntv;
                }
                else if(i==5){
                    mode=16;
                    val=core.state[curSelection].rebIntv[spr];
                    x=core.state[curSelection].treaty[spr];
                    oldVal=core.state[curSelection].ORebIntv[spr];
                    x=core.RebIMax(spr,curSelection);
                    if(x<maxVal) maxVal=x;
                }
                else if(i==6){
                    mode=18;
                    val=core.state[curSelection].econAid[spr];
                    oldVal=core.state[curSelection].OEcon[spr];
                    maxVal=core.EconAMax(DAij);
                    sum=0;
                    for(int j=2;j<N;j++) sum+=(core.EconConv(core.state[j].econAid[spr]));
                    x=5;
                    y=(core.state[spr].gdp/88)-(2*sum);   // div 44(00)
                    for(int j=4;j>=0;j--) if(core.EconConv(j+1)>y) x=j;
                    if(x<maxVal) maxVal=x;
                    if(core.level<2) visible=false;
                }
                else if(i==7){
                    mode=20;
                    val=core.state[curSelection].destabilization[spr];
                    oldVal=core.state[curSelection].ODest[spr];
                    maxVal=5;
                    if(core.level<2) visible=false;
                }
                else if(i==8){
                    mode=22;
                    val=core.state[curSelection].pressure[spr];
                    oldVal=core.state[curSelection].OPress[spr];
                    maxVal=5;
                    if(core.level<3) visible=false;
                }
                else if(i==9){
                    mode=24;
                    val=core.state[curSelection].treaty[spr];
                    oldVal=core.state[curSelection].OTreat[spr];
                    maxVal=core.TreatMax(core.integrity[spr]+DAij-core.pugnacty[spr]);
                    if(core.level<3) visible=false;
                }
                else if(i==10){
                    mode=5;
                    val=core.state[curSelection].finlandization[spr];
                    maxVal=256;
                    if(core.level<3) visible=false;
                }
                else  if(i==11){
                    mode=5;
                    y=core.state[curSelection].finlandization[spr]-core.state[curSelection].OFinProb[spr];
                    if(y<-18) y=-18;
                    if(y>18) y=18;
                    val=(y+18)/4;
                    if(core.level<3) visible=false;
                }
                if(i>=2&&i<=9){
                    //print arrows if necessary
                    if(oldVal>val) arrow="\u25bc ";
                    else if(oldVal<val) arrow="\u25b2 ";
                    else arrow="";
                }
                else arrow="";
                if(!visible) continue;
                if(maxVal<=val) clsUp.sprpwrVal[spr*12+i]->setText(arrow+"{"+captionCreate(mode,0,val)+"}");
                else clsUp.sprpwrVal[spr*12+i]->setText(arrow+captionCreate(mode,0,val));
                if(i==11){ clsUp.sprpwrVal[spr*12+i]->setText(resrc.strg[623+val]); }
            }
            int sum;
            clsUp.otherVal[1]->setText(QString::number(core.state[curSelection].prestVal/8));
            }
            for(int i=0;i<4;i++){
                sum=0;
                if(i==0) for(int k=0;k<N;k++) sum+=(core.MAidConv(core.state[curSelection].milAid[k])*20);
                else if(i==1) for(int k=0;k<N;k++) sum+=(core.MAidConv(core.state[curSelection].rebAid[k])*20);
                else if(i==2) for(int k=0;k<N;k++) sum+=(core.IntvConv(core.state[curSelection].milIntv[k]));
                else if(i==3) for(int k=0;k<N;k++) sum+=(core.IntvConv(core.state[curSelection].rebIntv[k]));
                if(i<2) clsUp.otherVal[i+2]->setText("$"+QString::number(sum)+" million");
                else clsUp.otherVal[i+2]->setText(QString::number(sum)+" k men");
            }
    }
    if(curSelection<2){
        int avlRsrc, sumMilIntv=0, sumRebIntv=0, sumMilAid=0, sumRebAid=0, sumEconAid=0;
        clsUp.topHead[0]->setText("<b>Net Sent</b>");
        clsUp.topHead[1]->setText("<b>Amount Remaining</b>");
        for(int i=2;i<N;i++){
            sumMilIntv+=core.IntvConv(core.state[i].milIntv[curSelection]);
            sumRebIntv+=core.IntvConv(core.state[i].rebIntv[curSelection]);
            sumMilAid+=(core.MAidConv(core.state[i].milAid[curSelection]));
            sumRebAid+=(core.MAidConv(core.state[i].rebAid[curSelection]));
            sumEconAid+=core.EconConv(core.state[i].econAid[curSelection]);
        }
        for(int i=2;i<7;i++){
            if(i==2){
                y=sumMilAid*20;
                avlRsrc=(core.state[curSelection].gdpSpending[2]/18)+core.state[curSelection].govtAidBalance;  //*2
            }
            else if(i==3){
                y=sumRebAid*20;
                avlRsrc=(core.state[curSelection].gdpSpending[2]/18)+core.state[curSelection].govtAidBalance;  //*2
            }
            else if(i==4){
                y=sumMilIntv;
                avlRsrc=(core.state[curSelection].troopSize/4)-core.state[curSelection].totalIntv;
            }
            else if(i==5){
                y=sumRebIntv;
                avlRsrc=(core.state[curSelection].troopSize/4)-core.state[curSelection].totalIntv;
            }
            else if(i==6){
                y=sumEconAid*2;
                avlRsrc=(core.state[curSelection].gdp/88)-2*sumEconAid; //div 44(00)
            }
            if(i<4||i==6) {
                clsUp.sprpwrVal[i]->setText("$"+QString::number(y)+" million");
                clsUp.sprpwrVal[12+i]->setText("$"+QString::number(avlRsrc)+" million");
            }
            else {
                clsUp.sprpwrVal[i]->setText(QString::number(y)+" k men");
                clsUp.sprpwrVal[12+i]->setText(QString::number(avlRsrc)+" k men");
            }
        }

    }
    int maxVal1, mode1;
    for(int i=0;i<5;i++){
        if(i==0){
            mode=113; mode1=538;
            y=core.state[curSelection].strengthRatio; x=0;
            if(y>1) x=1;
            if(y>7) x=2;
            if(y>31) x=3;
            if(y>127) x=4;
            if(y>511) x=5;
            if(y>2047) x=6;
            maxVal=8;
            val=(core.state[curSelection].govStrength/((core.state[curSelection].rebStrength/5)+1))
                    -(core.state[curSelection].OGovStrength/((core.state[curSelection].ORebStrength/5)+1))+1;
            maxVal1=1;
        }
        else if(i==1) {
            mode=499;
            x=(core.state[curSelection].govIdeol+128)/16;
            maxVal=15;
        }
        else if(i==2){
            mode=516;
            x=0;
            y=core.state[curSelection].milPower;
            if(y>20) x=1;
            if(y>40) x=2;
            if(y>100) x=3;
            if(y>200) x=4;
            if(y>500) x=5;
            if(y>1000) x=6;
            if(y>2000) x=7;
            maxVal=7;
        }
        if(i==3) {
            mode=120;
            //x=(((core.state[curSelection].dontMess-core.AveDMess)*8)/core.AveDMess)+6;
            x=(core.state[curSelection].dontMess*N*5)/core.sumDontMess;
            maxVal=12;
        }
        if(i==4){
            mode=524; mode1=532;
            x=core.state[curSelection].govPopul/2;
            maxVal=7;
            val=3+core.state[curSelection].govPopul-core.state[curSelection].OGovPopul;
            maxVal1=5;
        }
        if(x>maxVal) x=maxVal;
        if(x<0) x=0;

        if(i==0||i==4) {
            if(val>maxVal1) val=maxVal1;
            if(val<0) val=0;
            clsUp.infoVal[i]->setText(resrc.strg[mode+x]+" -- "+resrc.strg[mode1+val]);
        }
        else clsUp.infoVal[i]->setText(resrc.strg[mode+x]);
    }
    clsUp.infoVal[5]->setText(resrc.strg[314+curSelection]);
    clsUp.infoVal[6]->setText(resrc.strg[540+core.state[curSelection].leaderTitle]+" "+core.state[curSelection].leaderName);
    clsUp.infoVal[7]->setText(resrc.rebels[core.state[curSelection].rebIdeol>=0][curSelection]);
    clsUp.show();
}

void MainBox::showHistory(){
    histWind.setModal(true);
    histWind.setParent(this,Qt::Dialog);
    histWind.setWindowTitle(resrc.strg[curSelection+154]+" - history");
    bool visible;

    QPixmap pixmap[9];
    int plot[4][9];
    int x=core.year-1982;
    int tmpx;
    QPen lineChartPen;
    lineChartPen.setWidth(2);
    QBrush barFill;

    for(int i=0;i<9;i++){
        visible=true;
        QPixmap tempPixmap(211,116);
        tempPixmap.fill(QColor("transparent"));
        QPainter painter(&tempPixmap);
        painter.drawLine(QPoint(5,0),QPoint(5,100));    //y-axis
        painter.drawLine(QPoint(5,100),QPoint(205,100));    //x-axis
        for(int j=0;j<6;j++){
            painter.drawLine(QPoint(3,100-(j+1)*20),QPoint(7,100-(j+1)*20));    //y-axis scale
        }
        for(int j=0;j<8;j++){
            painter.drawLine(QPoint(5+(j+1)*25,98),QPoint(5+(j+1)*25,102));    //x-axis scale
            painter.drawText(QPoint(10+(j)*25,114),QString("'")+QString::number(j+82));
        }
        lineChartPen.setColor(QColor(0,127,0));

        //now paint the history values
        tmpx=x;
        if(i==0){
            //QPolygon lineChart;
            QVector<QPoint> lineChart;
            painter.setBrush(QColor(0,127,0));
            for(int y=0;y<=x;y++) {
                plot[0][y]=core.history[y][curSelection][0];
                lineChart.append(QPoint(y*25+5,100-plot[0][y]));
                painter.drawEllipse(QPoint(y*25+5,100-plot[0][y]),3,3);
            }
            painter.setPen(lineChartPen);
            painter.setBrush(Qt::NoBrush);
            //painter.drawPolygon(lineChart);
            for(int y=0;y+1<lineChart.size();y++) painter.drawLine(lineChart[y],lineChart[y+1]);
        }

        else if(i==1){
            for(int y=0;y<=x;y++){
                for(int t=0;t<4;t++){
                    plot[t][y]=core.history[y][curSelection][t+1];
                    if(t<2) barFill.setStyle(Qt::SolidPattern);
                    else barFill.setStyle(Qt::Dense5Pattern);
                    if(t%2) barFill.setColor(Qt::red);
                    else barFill.setColor(Qt::blue);
                    painter.setBrush(barFill);
                    painter.drawRect(5+y*25+t*6,100,6,-plot[t][y]*20);
                }
            }
        }

        else if(i==2){
            if(x==8) tmpx=7;
            for(int y=0;y<=tmpx;y++){
                for(int t=0;t<4;t++){
                    plot[t][y]=core.history[y][curSelection][t+5];
                    if(t<2) barFill.setStyle(Qt::SolidPattern);
                    else barFill.setStyle(Qt::Dense5Pattern);
                    if(t%2) barFill.setColor(Qt::red);
                    else barFill.setColor(Qt::blue);
                    painter.setBrush(barFill);
                    painter.drawRect(5+y*25+t*6,100,6,-plot[t][y]*20);
                }
            }
        }
        else if(i==3){
            //QPolygon lineChart;
            QVector<QPoint> lineChart;
            painter.setBrush(QColor(0,127,0));
            for(int y=0;y<=x;y++) {
                plot[0][y]=core.history[y][curSelection][12];
                lineChart.append(QPoint(y*25+5,100-plot[0][y]*4));
                painter.drawEllipse(QPoint(y*25+5,100-plot[0][y]*4),3,3);
            }
            painter.setPen(lineChartPen);
            painter.setBrush(Qt::NoBrush);
            //painter.drawPolygon(lineChart);
            for(int y=0;y+1<lineChart.size();y++) painter.drawLine(lineChart[y],lineChart[y+1]);
            if(core.level<2) visible=false;
        }
        else if(i==4){
            if(x==8) tmpx=7;
            for(int y=0;y<=tmpx;y++){
                for(int t=0;t<4;t++){
                    plot[t][y]=core.history[y][curSelection][t+13];
                    if(t<2) barFill.setStyle(Qt::SolidPattern);
                    else barFill.setStyle(Qt::Dense5Pattern);
                    if(t%2) barFill.setColor(Qt::red);
                    else barFill.setColor(Qt::blue);
                    painter.setBrush(barFill);
                    painter.drawRect(5+y*25+t*6,100,6,-plot[t][y]*20);
                }
            }
            if(core.level<2) visible=false;
        }
        else if(i==5){
            //QPolygon lineChart[2];
            QVector<QPoint> lineChart[2];
            for(int t=0;t<2;t++){
                for(int y=0;y<=x;y++){
                    plot[t][y]=core.history[y][curSelection][t+9];
                    plot[t][y]+=128; plot[t][y]/=3;
                    lineChart[t].append(QPoint(y*25+5,100-plot[t][y]));
                    if(t==0) painter.setBrush(QColor(Qt::blue));
                    else painter.setBrush(QColor(Qt::red));
                    painter.drawEllipse(QPoint(y*25+5,100-plot[t][y]),3,3);
                }
            }
            painter.setBrush(Qt::NoBrush);
            lineChartPen.setColor(QColor(Qt::blue));
            painter.setPen(lineChartPen);
            //painter.drawPolygon(lineChart[0]);
            for(int y=0;y+1<lineChart[0].size();y++) painter.drawLine(lineChart[0][y],lineChart[0][y+1]);
            lineChartPen.setColor(QColor(Qt::red));
            painter.setPen(lineChartPen);
            //painter.drawPolygon(lineChart[1]);
            for(int y=0;y+1<lineChart[1].size();y++) painter.drawLine(lineChart[1][y],lineChart[1][y+1]);
        }
        else if(i==6){
            //QPolygon lineChart[2];
            QVector<QPoint> lineChart[2];
            for(int t=0;t<2;t++){
                for(int y=0;y<=x;y++){
                    plot[t][y]=core.history[y][curSelection][t+17];
                    plot[t][y]/=3;
                    lineChart[t].append(QPoint(y*25+5,100-plot[t][y]));
                    if(t==0) painter.setBrush(QColor(Qt::blue));
                    else painter.setBrush(QColor(Qt::red));
                    painter.drawEllipse(QPoint(y*25+5,100-plot[t][y]),3,3);
                }
            }
            painter.setBrush(Qt::NoBrush);
            lineChartPen.setColor(QColor(Qt::blue));
            painter.setPen(lineChartPen);
            //painter.drawPolygon(lineChart[0]);
            for(int y=0;y+1<lineChart[0].size();y++) painter.drawLine(lineChart[0][y],lineChart[0][y+1]);
            lineChartPen.setColor(QColor(Qt::red));
            painter.setPen(lineChartPen);
            //painter.drawPolygon(lineChart[1]);
            for(int y=0;y+1<lineChart[1].size();y++) painter.drawLine(lineChart[1][y],lineChart[1][y+1]);
            if(core.level<3) visible=false;
        }
        else if(i==7){
            if(x==8) tmpx=7;
            for(int y=0;y<=tmpx;y++){
                for(int t=0;t<4;t++){
                    plot[t][y]=core.history[y][curSelection][t+19];
                    if(t<2) barFill.setStyle(Qt::SolidPattern);
                    else barFill.setStyle(Qt::Dense5Pattern);
                    if(t%2) barFill.setColor(Qt::red);
                    else barFill.setColor(Qt::blue);
                    painter.setBrush(barFill);
                    painter.drawRect(5+y*25+t*6,100,6,-plot[t][y]*20);
                }
            }
            if(core.level<3) visible=false;
        }
        else{
            //QPolygon lineChart;
            QVector<QPoint> lineChart;
            painter.setBrush(QColor(0,127,0));
            for(int y=0;y<=x;y++) {
                plot[0][y]=core.history[y][curSelection][11]/4;
                lineChart.append(QPoint(y*25+5,100-plot[0][y]));
                painter.drawEllipse(QPoint(y*25+5,100-plot[0][y]),3,3);
            }
            painter.setPen(lineChartPen);
            painter.setBrush(Qt::NoBrush);
            //painter.drawPolygon(lineChart);
            for(int y=0;y+1<lineChart.size();y++) painter.drawLine(lineChart[y],lineChart[y+1]);
        }

        if(visible){
            pixmap[i]=tempPixmap;
            histWind.chart[i]->setPixmap(pixmap[i]);
            histWind.title[i]->setAlignment(Qt::AlignCenter);
            histWind.title[i]->setText("<b>"+resrc.strg[594+i]+"</b>");
        }

        //kludge to fix spacing bugs, duh
        else histWind.chart[i]->setFixedSize(211,116);

    }

    //paint the legend
    QPixmap legendPMap(700,15);
    legendPMap.fill(QColor("transparent"));
    QPainter legendPainter(&legendPMap);
    legendPainter.setBrush(barFill);

    for(int i=0;i<4;i++){
        if(i<2) barFill.setStyle(Qt::SolidPattern);
        else barFill.setStyle(Qt::Dense5Pattern);
        if(i%2) barFill.setColor(Qt::red);
        else barFill.setColor(Qt::blue);
        legendPainter.setBrush(barFill);
        legendPainter.drawRect(-50+130*(i+1),1,20,5);
        legendPainter.drawText(QPoint(-25+130*(i+1),9),QString(resrc.strg[603+i]));
    }
    histWind.legend->setPixmap(legendPMap);
    histWind.show();
}


void MainBox::prevNews(){
    if(curPage>0) {
        curPage--;
        nwsWind.page->setText(QString("page ")+QString::number(curPage+1)+" of "+QString::number(newsCount));
        nwsWind.newsHeadline->setText(QString("In ")+resrc.strg[154+core.news[listNews[curPage]].host]+",\n"+core.news[listNews[curPage]].headLine);
        unloadAdvPanel();
        if(!core.news[listNews[curPage]].crisisVal&&core.news[listNews[curPage]].actor!=core.human) {
            createAdvPanel();
            nwsWind.question->setDisabled(false);
        }
        else {
            nwsWind.question->setDisabled(true);
            nwsWind.backDown->setDisabled(true);
        }
        if(curPage==0) nwsWind.previous->setDisabled(true);
        if(!nwsWind.next->isEnabled()) nwsWind.next->setDisabled(false);
    }
}

void MainBox::nextNews(){
    if(curPage<newsCount-1) {
        curPage++;
        nwsWind.page->setText(QString("page ")+QString::number(curPage+1)+" of "+QString::number(newsCount));
        nwsWind.newsHeadline->setText(QString("In ")+resrc.strg[154+core.news[listNews[curPage]].host]+",\n"+core.news[listNews[curPage]].headLine);
        unloadAdvPanel();
        if(!core.news[listNews[curPage]].crisisVal&&core.news[listNews[curPage]].actor!=core.human){
            createAdvPanel();
            nwsWind.question->setDisabled(false);
        }
        else {
            nwsWind.question->setDisabled(true);
            nwsWind.backDown->setDisabled(true);
        }
        if(curPage==newsCount-1) nwsWind.next->setDisabled(true);
        if(!nwsWind.previous->isEnabled()) nwsWind.previous->setDisabled(false);
    }
}

void MainBox::createAdvPanel(){
    int x,y,victim;
    victim=core.news[listNews[curPage]].victim;
    //host=core.news[listNews[curPage]].host;
    QPixmap head[4];
    head[0].load(":/images/adv1.png","PNG");
    head[1].load(":/images/adv2.png","PNG");
    head[2].load(":/images/adv3.png","PNG");
    head[3].load(":/images/adv4.png","PNG");
    //if military-related crisis
    if(core.news[listNews[curPage]].verb>1&&core.news[listNews[curPage]].verb<6){
        nwsWind.data[1]->setText("<b>"+resrc.strg[494]+"</b>");
        y=core.state[victim].strengthRatio; x=0;
        if(y>1) x=1;
        if(y>7) x=2;
        if(y>31) x=3;
        if(y>127) x=4;
        if(y>511) x=5;
        if(y>2047) x=6;
        nwsWind.dataVal[1]->setText(resrc.strg[113+x]);

        x=(core.state[victim].govStrength/((core.state[victim].rebStrength/5)+1))
                -(core.state[victim].OGovStrength/((core.state[victim].ORebStrength/5)+1))+1;
        if(x>1) x=1;
        else if(x<0) x=0;
        nwsWind.dataVal[2]->setText(resrc.strg[537+x]);

        for(int i=2;i<6;i++)nwsWind.colB[i]->setText("<b>"+resrc.strg[475+i]+"</b>");
        nwsWind.colBVal[2]->setText(captionCreate(10,0,core.state[victim].milAid[0]));
        nwsWind.colBVal[3]->setText(captionCreate(12,0,core.state[victim].rebAid[0]));
        nwsWind.colBVal[4]->setText(captionCreate(14,0,core.state[victim].milIntv[0]));
        nwsWind.colBVal[5]->setText(captionCreate(16,0,core.state[victim].rebIntv[0]));
        nwsWind.colBVal[8]->setText(captionCreate(10,0,core.state[victim].milAid[1]));
        nwsWind.colBVal[9]->setText(captionCreate(12,0,core.state[victim].rebAid[1]));
        nwsWind.colBVal[10]->setText(captionCreate(14,0,core.state[victim].milIntv[1]));
        nwsWind.colBVal[11]->setText(captionCreate(16,0,core.state[victim].rebIntv[1]));
    }

    //if not-military related
   else{
        nwsWind.data[1]->setText("<b>"+resrc.strg[491]+"</b>");
        x=core.state[victim].govPopul/2;
        y=3+core.state[victim].govPopul-core.state[victim].OGovPopul;
        if(x>7) x=7; if(y>5) y=5;
        nwsWind.dataVal[1]->setText(resrc.strg[524+x]);
        nwsWind.dataVal[2]->setText(resrc.strg[531+y]);
        for(int i=2;i<5;i++) nwsWind.colB[i]->setText("<b>"+resrc.strg[479+i]+"</b>");
        nwsWind.colBVal[2]->setText(captionCreate(18,0,core.state[victim].econAid[0]));
        nwsWind.colBVal[3]->setText(captionCreate(20,0,core.state[victim].destabilization[0]));
        nwsWind.colBVal[4]->setText(captionCreate(22,0,core.state[victim].pressure[0]));
        nwsWind.colBVal[8]->setText(captionCreate(18,0,core.state[victim].econAid[1]));
        nwsWind.colBVal[9]->setText(captionCreate(20,0,core.state[victim].destabilization[1]));
        nwsWind.colBVal[10]->setText(captionCreate(22,0,core.state[victim].pressure[1]));
    }
    nwsWind.data[0]->setText("<b>"+resrc.strg[490]+"</b>");
    x=(core.state[victim].dontMess*N*5)/core.sumDontMess;
    nwsWind.dataVal[0]->setText(resrc.strg[120+x]);
    nwsWind.data[2]->setText("<b>Rate of Change</b>");
    nwsWind.colB[0]->setText("<b>Relationship</b>");
    nwsWind.colB[1]->setText("<b>Treaty</b>");
    nwsWind.colBVal[0]->setText(captionCreate(8,0,core.state[victim].overallRelationship[0]));
    nwsWind.colBVal[1]->setText(captionCreate(24,0,core.state[victim].treaty[0]));
    nwsWind.colBVal[6]->setText(captionCreate(8,0,core.state[victim].overallRelationship[1]));
    nwsWind.colBVal[7]->setText(captionCreate(24,0,core.state[victim].treaty[1]));
    nwsWind.header[1]->setText("<b>USA Value</b>");
    nwsWind.header[2]->setText("<b>USSR Value</b>");
    for(int i=0;i<4;i++){
        x=core.GImpt(victim,core.news[listNews[curPage]].verb,core.news[listNews[curPage]].actor,core.news[listNews[curPage]].oldNVal,core.news[listNews[curPage]].newNVal,i);
        x/=8;
        x++;
        if(x<-15)x=-15;
        if(x>16)x=16;
        x+=16;
        nwsWind.advice[i]->setText(resrc.strg[553+x]);
        nwsWind.picture[i]->setPixmap(head[i]);
    }
    nwsWind.question->setText("Question: "+resrc.strg[154+core.news[listNews[curPage]].actor]);
    nwsWind.advisory->setText("<p align=\"center\"><b>Advisory on: </b>"+resrc.strg[154+core.news[listNews[curPage]].host]+"</p>");
}

void MainBox::unloadAdvPanel(){
    QPixmap emptHead;
    emptHead.load(":/images/noAdv.png","PNG");
    for(int i=0;i<4;i++){
        nwsWind.picture[i]->setPixmap(emptHead);
        nwsWind.advice[i]->setText("");
    }
    for(int i=0;i<3;i++){
        nwsWind.data[i]->setText("");
        nwsWind.dataVal[i]->setText("");
        nwsWind.header[i]->setText("");
    }
    for(int i=0;i<12;i++){
        if(i<6) nwsWind.colB[i]->setText("");
        nwsWind.colBVal[i]->setText("");
    }
    nwsWind.question->setText("Question");
    nwsWind.advisory->setText("");
}

void MainBox::showNewsWindow(int t){
    curNewsMode=t;
    newsCount=0;
    for(int i=1;i<core.NewsQCtr;i++){
        if(curNewsMode==0) {if(core.news[i].actor==curSelection||core.news[i].victim==curSelection) { listNews[newsCount]=i; newsCount++;} }
        else if(curNewsMode==1) {if(core.news[i].actor==0&&core.news[i].newNVal>core.news[i].oldNVal) { listNews[newsCount]=i; newsCount++;} }
        else if(curNewsMode==2) {if(core.news[i].actor==0&&core.news[i].newNVal<core.news[i].oldNVal) { listNews[newsCount]=i; newsCount++;} }
        else if(curNewsMode==3) {if(core.news[i].actor==1&&core.news[i].newNVal>core.news[i].oldNVal) { listNews[newsCount]=i; newsCount++;} }
        else if(curNewsMode==4) {if(core.news[i].actor==1&&core.news[i].newNVal<core.news[i].oldNVal) { listNews[newsCount]=i; newsCount++;} }
        else if(curNewsMode==5) {if(core.news[i].actor>1) { listNews[newsCount]=i; newsCount++;} }
    }
    curPage=0;
    if(curNewsMode==0) nwsWind.newspaperTitle->setText(QString("The ")+resrc.strg[234+curSelection]+" Yearly News "+QString::number(core.year));
    else nwsWind.newspaperTitle->setText("");
    if(newsCount>0) {
        nwsWind.previous->setDisabled(true);
        nwsWind.next->setDisabled(false);
        unloadAdvPanel();
        if(!core.news[listNews[curPage]].crisisVal&&core.news[listNews[curPage]].actor!=core.human){
            createAdvPanel();
            nwsWind.question->setDisabled(false);
        }
        else {
            nwsWind.question->setDisabled(true);
            nwsWind.backDown->setDisabled(true);
        }
        if(newsCount==1) nwsWind.next->setDisabled(true);
        nwsWind.newsHeadline->setText(QString("In ")+resrc.strg[154+core.news[listNews[curPage]].host]+",\n"+core.news[listNews[curPage]].headLine);
        nwsWind.page->setText(QString("page ")+QString::number(curPage+1)+" of "+QString::number(newsCount));

    }
    else {
        unloadAdvPanel();
        nwsWind.next->setDisabled(true);
        nwsWind.previous->setDisabled(true);
        nwsWind.question->setDisabled(true);
        nwsWind.backDown->setDisabled(true);
        nwsWind.newsHeadline->setText(QString("Nothing to display"));
        nwsWind.page->setText(QString("page 0 of 0"));
    }

    nwsWind.setWindowTitle(resrc.strg[548+curNewsMode]);
    nwsWind.setModal(true);
    nwsWind.setParent(this,Qt::Dialog);
    //activate window exit
    nwsWind.setWindowFlags(nwsWind.windowFlags()|Qt::WindowCloseButtonHint);
    nwsWind.show();

}

void MainBox::showPolcyWindow(int t){
    curPolicyMode=t;
    int base,x,Max,oldCtrl,avlResrc,sum;
    if(t==0) base=91;
    else if(t==1) base=85;
    else if(t==2||t==3) base=73;
    else if(t==4||t==5) base=79;
    else if(t==6) base=697;
    else if(t==7) base=102;
    for(int i=0;i<6;i++) plcyWind.opt[i]->setText(resrc.strg[base+i]);
    for(int i=0;i<6;i++) plcyWind.opt[i]->setDisabled(false);

    Max=5;
    x=core.state[curSelection].overallRelationship[core.human];
    if(t==2){
        oldCtrl=core.state[curSelection].milAid[core.human];
        Max=core.MilMax(x);
        x=5;
        avlResrc=(core.state[core.human].gdpSpending[2]/18)+core.state[core.human].govtAidBalance;
        for(int i=4;i>=0;i--) if(core.MAidConv(i+1)*20>avlResrc) x=i;
        if(x<Max) Max=x;
    }
    else if(t==3){
        oldCtrl=core.state[curSelection].rebAid[core.human];
        x=0;
        if(core.state[curSelection].strengthRatio<512) x=1;
        if(core.state[curSelection].strengthRatio<128) x=2;
        if(core.state[curSelection].strengthRatio<32) x=3;
        if(core.state[curSelection].strengthRatio<8) x=4;
        if(core.state[curSelection].strengthRatio<2) x=5;
        Max=x;
        x=core.RebAMax(core.human,curSelection);
        if(x<Max) Max=x;
        avlResrc=(core.state[core.human].gdpSpending[2]/18)+core.state[core.human].govtAidBalance;
        for(int i=4;i>=0;i--) if(core.MAidConv(i+1)*20>avlResrc) x=i;
        if(x<Max) Max=x;
    }
    else if(t==4){
        oldCtrl=core.state[curSelection].milIntv[core.human];
        Max=core.IntvGMax(core.state[curSelection].treaty[core.human],core.state[curSelection].overallRelationship[core.human]);
        x=5;
        avlResrc=(core.state[core.human].troopSize/4)-core.state[core.human].totalIntv;
        for(int i=4;i>=0;i--) if(core.IntvConv(i+1)>avlResrc) x=i;
        if(x<Max) Max=x;
    }
    else if(t==5){
        oldCtrl=core.state[curSelection].rebIntv[core.human];
        Max=core.RebIMax(core.human,curSelection);
        x=5;
        avlResrc=(core.state[core.human].troopSize/4)-core.state[core.human].totalIntv;
        for(int i=4;i>=0;i--) if(core.IntvConv(i+1)>avlResrc) x=i;
        if(x<Max) Max=x;
    }
    else if(t==1){
        oldCtrl=core.state[curSelection].econAid[core.human];
        Max=core.EconAMax(x);
        sum=0;
        for(int i=2;i<N;i++) sum+=(core.EconConv(core.state[i].econAid[core.human]));
        x=5;
        avlResrc=(core.state[core.human].gdp/88)-(2*sum);
        for(int i=4;i>=0;i--)
            if(core.EconConv(i+1)>((avlResrc/2)+core.EconConv(oldCtrl))) x=i;
        if(x<Max) Max=x;
    }
    else if(t==7){
        oldCtrl=core.state[curSelection].treaty[core.human];
        Max=core.TreatMax(core.integrity[core.human]+x-core.pugnacty[core.human]);
        if(Max<=core.state[curSelection].treaty[core.human]) Max=core.state[curSelection].treaty[core.human];
        if(core.state[curSelection].treaty[core.human]>0){
            for(int i=0;i<core.state[curSelection].treaty[core.human];i++)
                plcyWind.opt[i]->setDisabled(true);
        }
    }
    else if(t==6) oldCtrl=core.state[curSelection].pressure[core.human];
    else if(t==0) oldCtrl=core.state[curSelection].destabilization[core.human];

    if(Max<5){
        for(int i=Max+1;i<6;i++)
            plcyWind.opt[i]->setDisabled(true);
    }

    if(t==1||t==2||t==3)
        plcyWind.remain->setText("Available: $"+QString::number(avlResrc)+" million");
    else if(t==4||t==5)
        plcyWind.remain->setText("Available: "+QString::number(avlResrc)+" k men");
    else plcyWind.remain->setText("");

    plcyWind.opt[oldCtrl]->setChecked(true);

    oldPlcy=oldCtrl;

    plcyWind.setWindowTitle(resrc.strg[154+curSelection]+" - set "+resrc.strg[586+t]);
    plcyWind.setModal(true);
    plcyWind.setParent(this,Qt::Dialog);
    plcyWind.show();

}

void MainBox::enactPolicy(){
    int New;
    for(int i=0;i<6;i++){
        if(plcyWind.opt[i]->isChecked()){
            New=i;
            break;
        }
    }
    core.DoPolicy(curSelection,curPolicyMode,core.human,New,(New<oldPlcy));
    plcyWind.close();
}

void MainBox::showScores(){
    scrWind.setModal(true);
    scrWind.setParent(this,Qt::Dialog);
    //table data
    scrWind.cell[1]->setText("<b>gain this year:</b>");
    scrWind.cell[2]->setText("<b>gain to date:</b>");
    scrWind.cell[3]->setText("<b>USA</b>");
    scrWind.cell[4]->setText(QString::number(core.score[0]-core.OScore[0]));
    scrWind.cell[5]->setText(QString::number(core.score[0]-core.initScore[0]));
    scrWind.cell[6]->setText("<b>USSR</b>");
    scrWind.cell[7]->setText(QString::number(core.score[1]-core.OScore[1]));
    scrWind.cell[8]->setText(QString::number(core.score[1]-core.initScore[1]));

    //chart outlays
    QPixmap pxmp(270,230);
    pxmp.fill(QColor("transparent"));
    QPainter painter(&pxmp);
    painter.drawLine(QPoint(29,0),QPoint(29,200));  //y-axis
    painter.drawLine(QPoint(29,200),QPoint(270,200));    //x-axis
    for(int i=0;i<8;i++){
        painter.drawLine(QPoint(29+(i+1)*30,197),QPoint(29+(i+1)*30,203));
        painter.drawText(QPoint(37+i*30,215),QString("'")+QString::number(i+82));
    }
    painter.drawLine(QPoint(26,0),QPoint(32,0));
    painter.drawLine(QPoint(26,100),QPoint(32,100));
    painter.drawText(QPoint(0,10),QString("+700"));
    painter.drawText(QPoint(10,110),QString("0"));
    painter.drawText(QPoint(5,200),QString("-700"));
    int x=core.year-1982;

    //now the proper chart
    int plot[2][9];
    //QPolygon lineChart[2];
    QVector<QPoint> lineChart[2];
    QPen pen;
    for(int t=0;t<2;t++){
        for(int y=0;y<=x;y++){
            plot[t][y]=core.historyScore[y][t];
            plot[t][y]+=700; plot[t][y]/=7;
            lineChart[t].append(QPoint(y*30+29,200-plot[t][y]));
            if(t==0) painter.setBrush(QColor(Qt::blue));
            else painter.setBrush(QColor(Qt::red));
            painter.drawEllipse(QPoint(y*30+29,200-plot[t][y]),3,3);
        }
    }
    painter.setBrush(Qt::NoBrush);
    pen.setWidth(2);

    for(int t=0;t<2;t++){
        if(t==0) pen.setColor(Qt::blue);
        else pen.setColor(Qt::red);
        painter.setPen(pen);
        //painter.drawPolygon(lineChart[t]);
        for(int y=0;y+1<lineChart[t].size();y++) painter.drawLine(lineChart[t][y],lineChart[t][y+1]);
    }
    scrWind.chart->setPixmap(pxmp);
    scrWind.show();
}

void MainBox::showNewGame(){
    for(int i=0;i<4;i++)
        newGameWindow.lev[i]->setText(resrc.strg[607+i]);
    for(int i=0;i<2;i++){
        newGameWindow.sid[i]->setText(resrc.strg[611+i]);
        newGameWindow.mod[i]->setText(resrc.strg[613+i]);
    }
    newGameWindow.lev[0]->setChecked(true);
    newGameWindow.sid[0]->setChecked(true);
    newGameWindow.mod[0]->setChecked(true);
    newGameWindow.setModal(true);
    newGameWindow.setParent(this,Qt::Dialog);
    newGameWindow.show();
}

void MainBox::setNewGame(){
    for(int i=0;i<4;i++)
        if(newGameWindow.lev[i]->isChecked()) core.level=i+1;
    if(newGameWindow.sid[0]->isChecked()){ core.human=0; core.cmptr=1; }
    else { core.human=1; core.cmptr=0; }
    if(newGameWindow.mod[0]->isChecked()) core.TwoPFlag=false;
    else core.TwoPFlag=true;
    core.clearAllData();
    core.year=1981;
    core.loadData();
    core.gameInit();
    core.PrePlanMove();
    core.MainMove();
    curSelection=core.human;
    mapMode=1;
    curAddParam=0;
    curIOMode=0;
    drawMap(mapMode,curAddParam,curIOMode);
    for(int i=0;i<6;i++) doNews[i]->setDisabled(false);
    for(int i=0;i<8;i++) doPolicy[i]->setDisabled(false);
    saveGameAct->setDisabled(false);
    chgSideAct->setDisabled(false);
    nextTurnAct->setDisabled(false);
    scrWind.setWindowTitle("Scores - "+resrc.strg[606+core.level]+" level");
    scrWind.level->setText("");
    correctMenus();
    selectNothingEffect();
    drawMapStaticStrings();
    drawScores();
    yearLabel->setText("<font size=\"5\"><b>"+QString::number(core.year)+"</b></font>");
    newGameWindow.close();
}

void MainBox::changeSides(){
    if(core.human==0){ core.human=1; core.cmptr=0; }
    else { core.human=0; core.cmptr=1; }
    holdsMouse[core.human]->setText("(holds the mouse)");
    holdsMouse[core.cmptr]->setText("");
    nextTurnAct->setDisabled(false);
}

void MainBox::doNextTurn(){
    core.PrePlanMove();
    ReactNews();
}

void MainBox::continueNextTurn(){
    int x;
    for(int i=0;i<numOfBDs;i++){
        core.DoPolicy(BDQVictim[i],BDQVer[i],BDQAct[i],BDQNew[i],true);
    }
    core.NewsQCtr=0;
    if(core.TwoPFlag) nextTurnAct->setDisabled(true);
    for(int i=0;i<MAXNEWS;i++){
        core.news[i].actor=0;
        core.news[i].verb=0;
        core.news[i].victim=0;
        core.news[i].crisisVal=0;
        core.news[i].headLine="";
        core.news[i].newNVal=0;
        core.news[i].oldNVal=0;
        core.news[i].worth=0;
        core.news[i].host=0;
    }
    if(core.year>1982){
        for(int i=2;i<N;i++){
            for(int j=0;j<2;j++){
                core.MinorRej(j,i);
                x=(25*((256*(core.EconConv(core.state[i].econAid[j])))/core.state[i].gdp))/(core.state[i].govPopul+1)
                        -(32*core.state[i].destabilization[j])
                        +((core.state[i].milAid[j]*core.state[i].milPress)/8)
                        -(12*core.state[i].rebAid[j])
                        +((core.state[i].milIntv[j]*core.state[i].milPress)/4)
                        -(64*core.state[i].rebIntv[j])
                        -(16*core.state[i].pressure[j])
                        +((((core.state[i].treaty[j]*core.integrity[j])/128)*core.state[i].milPress)/8);
                x/=8;
                core.ChgDipAff(i,j,x);
            }
            if(core.level==4){
                for(int j=2;j<N;j++){
                    x=((core.state[i].milAid[j]*core.state[i].milPress)/8)
                            -(12*core.state[i].rebAid[j])
                            +((core.state[i].milIntv[j]*core.state[i].milPress)/4)
                            -(64*core.state[i].rebIntv[j]);
                    x/=8;
                    core.ChgDipAff(i,j,x);
                }
            }
        }
    }
    if(core.year==1990) { core.WinFlag=true; EndGame(); }
    if(!core.QuitFlag) core.MainMove();
    drawScores();
    yearLabel->setText("<font size=\"5\"><b>"+QString::number(core.year)+"</b></font>");
    mapMode=1;
    curAddParam=0;
    curIOMode=0;
    drawMap(1,0,0);
    selectNothingEffect();
}

void MainBox::ReactNews(){
    int x,y,z;
    numOfBDs=0;
    questSize=0;
    for(int i=0;i<core.NewsQCtr;i++){
        if(core.news[i].actor!=core.news[i].victim){
            if((core.news[i].verb==5||core.news[i].verb==3||core.news[i].verb==0||core.news[i].verb==6)&&core.news[i].actor<2){
                core.nastiness+=(core.news[i].newNVal-core.news[i].oldNVal);
                if(core.nastiness<1) core.nastiness=1;
                if(core.nastiness>127) core.nastiness=127;
            }
            //cmptr-human crisis
            if(core.news[i].actor==core.human&&(core.news[i].newNVal>core.news[i].oldNVal)&&!core.TwoPFlag&&!core.news[i].crisisVal){
                x=-core.GImpt(core.news[i].victim,core.news[i].verb,core.news[i].actor,core.news[i].oldNVal,core.news[i].newNVal,0);
                y=core.USAImpt; z=core.USSRImpt;
                if(core.cmptr==0) z=y;
                if(z<0) x=256;
                if(x<abs((rand()%32768)/1024)){
                    QuestQueue[questSize]=i;
                    questSize++;
                }
            }
            else if(core.news[i].actor>1&&core.news[i].newNVal>core.news[i].oldNVal&&!core.TwoPFlag&&core.Influence(core.cmptr,core.news[i].actor>3)){
                x=-(core.GImpt(core.news[i].victim,core.news[i].verb,core.news[i].actor,core.news[i].oldNVal,core.news[i].newNVal,0));
                y=core.USAImpt; z=core.USSRImpt;
                if(core.cmptr==0) z=y;
                if(z>abs((rand()%32768)/1024)) CmptrCrisis(i);
            }
        }
    }
    if(questSize>0) {
        cris.resetCrisData();
        curQuest=0;
        listNews[curPage]=QuestQueue[0];
        doCrisis(listNews[curPage]);
    }
    else continueNextTurn();
}

void MainBox::EndGame(){
    core.QuitFlag=true;
    if(core.WinFlag&&!core.ANWFlag&&!core.crisis){
        core.calcScores();
        drawScores();
        for(int i=0;i<2;i++) {
            core.OScore[i]=core.score[i];
            core.historyScore[8][i]=core.score[i]-core.initScore[i];
        }
        core.SaveHistory();
        scrWind.setWindowTitle("End of Game");
        scrWind.level->setText("You have kept the peace.<br><br><br><p align=\"center\">Your scores:</p>");
        showScores();
    }
    else{
        QString string="<font color=\"white\"><p align=\"center\">You have ignited ";
        if(core.ANWFlag) string+=("an accidental ");
        else string+=("a ");
        string+=("nuclear war.<br>And no, there is no animated display of a mushroom cloud<br>"
               "with parts of bodies flying through the air.<br><br><br>"
               "We do not reward failure.</p></font>");
        LGameWindow.text->setText(string);
        LGameWindow.show();
    }
    for(int i=0;i<6;i++) doNews[i]->setDisabled(true);
    for(int i=0;i<8;i++) doPolicy[i]->setDisabled(true);
    saveGameAct->setDisabled(true);
    chgSideAct->setDisabled(true);
    nextTurnAct->setDisabled(true);
    nwsWind.setWindowFlags(nwsWind.windowFlags()|Qt::WindowCloseButtonHint);
    nwsWind.question->setDisabled(false);
    nwsWind.backDown->setDisabled(true);
    nwsWind.reactionLine->setText("");
    cris.resetCrisData();
    numOfBDs=0;
}

void MainBox::drawScores(){
    for(int i=0;i<2;i++) score[i]->setText("Score: "+QString::number(core.score[i]-core.initScore[i]));
}

void MainBox::drawMapStaticStrings(){
    QString string;
    for(int i=0;i<2;i++){
        string="";
        if(i==0) string+="<b>USA";
        else string+="<b>USSR";
        if(!core.TwoPFlag){
            if(i==core.human) string+=" (human)";
            else string+=" (AI)";
            holdsMouse[i]->setText("");
        }
        else {
            if(i==core.human) holdsMouse[i]->setText("(holds the mouse)");
            else holdsMouse[i]->setText("");
        }
        sprLabel[i]->setText(string+("</b>"));
    }
}
