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
#include "mainbox.h"
#include "crisis.h"

void Crisis::resetCrisData(){
    sumLoser=0, sumWinner=0;
    crisisLevel=0,base=0,savHuman=0,HLoss=0,CGain=0,t=0,x=0,y=0,z=0,H=0,DAow=0,DAol=0,Usex=0,Usez=0,rand1=0,rand2=0,victim=0,who=0,temp=0;
    backDown=0,aggrFlag=0,isBegun=0;
    whichHead=0;
}

void MainBox::HangLoose(int loser, int winner){
    int t,x,y,z;
    if(cris.crisisLevel<8){
        //no penalty for early withdrawal
        core.pugnacty[winner]+=((130-core.pugnacty[winner])/4);
        x=core.state[cris.victim].treaty[loser];
        t=core.Impt(cris.victim,core.news[cris.whichHead].verb,loser,core.news[cris.whichHead].oldNVal,core.news[cris.whichHead].newNVal);
        core.integrity[loser]=core.integrity[loser]-2*((core.Should(x)*t)/256);
        if(core.integrity[loser]<1) core.integrity[loser]=1;
        if(core.integrity[loser]>127) core.integrity[loser]=127;
        y=core.GImpt(cris.victim,core.news[cris.whichHead].verb,cris.who,core.news[cris.whichHead].oldNVal,core.news[cris.whichHead].newNVal,0);
        t=core.USAImpt; z=core.USSRImpt;
        x=(abs(t)/cris.crisisLevel)+(abs(z)/cris.crisisLevel)+8-cris.crisisLevel;
        y=0;
        for(int i=2;i<N;i++){
            z=x/32;
            y+=(x%32);
            if(y>32) { z++; y-=32; }
            core.ChgDipAff(i,loser,-z);
            core.ChgDipAff(i,winner,z);
        }
    }
    if(cris.crisisLevel%2){
        x=core.news[cris.whichHead].newNVal;
        core.news[cris.whichHead].newNVal=core.news[cris.whichHead].oldNVal;
        core.news[cris.whichHead].oldNVal=x;
        core.news[cris.whichHead].crisisVal=true;
        if(cris.who==core.cmptr) core.DoPolicy(cris.victim,core.news[cris.whichHead].verb,cris.who,core.news[cris.whichHead].newNVal,true);
        else {
            BDQVictim[numOfBDs]=cris.victim;
            BDQVer[numOfBDs]=core.news[cris.whichHead].verb;
            BDQAct[numOfBDs]=cris.who;
            BDQNew[numOfBDs]=core.news[cris.whichHead].newNVal;
            numOfBDs++;
        }
    }
    else core.news[cris.whichHead].crisisVal=true;
    x=9-cris.crisisLevel;
    t=cris.victim;
    if(x>core.state[t].dontMess) x=core.state[t].dontMess;
    if(loser==0) x=-x;
    core.ChgDMess(t,x);
    nwsWind.reactionLine->setText(GenerateReactionHLine(loser,cris.crisisLevel,false,true));

    nwsWind.question->setDisabled(true);
    nwsWind.backDown->setText("OK");
}

void MainBox::HangTough(int subject){
    int x,y;
    cris.crisisLevel--;
    if(cris.crisisLevel<7) nwsWind.setWindowTitle("Diplomatic crisis");
    if(cris.crisisLevel<5) nwsWind.setWindowTitle("Military crisis");
    x=core.state[cris.victim].treaty[subject];
    y=core.Impt(cris.victim,core.news[cris.whichHead].verb,subject,core.news[cris.whichHead].oldNVal,core.news[cris.whichHead].newNVal);
    core.integrity[subject]+=((core.Should(x)*y)/256);
    if(core.integrity[subject]<1) core.integrity[subject]=1;
    if(core.integrity[subject]>127) core.integrity[subject]=127;
    core.ChgDipAff(core.cmptr,core.human,cris.crisisLevel-9);
    x=0;
    switch(cris.crisisLevel){
    case 2:
        x=16; break;
    case 3:
        x=8; break;
    case 4:
        x=2; break;
    }
    if(core.state[0].overallRelationship[1]>0) x=0;
    else x=(x*(-core.state[0].overallRelationship[1]))/64;
    y=(rand()%32768)/128;
    if(x>abs(y)){ cris.crisisLevel=1; core.ANWFlag=true; nwsWind.close(); }
    core.nastiness=core.nastiness+9-cris.crisisLevel;
    if(core.nastiness>127) core.nastiness=127;


    if(cris.crisisLevel==1){
        core.crisis=true;
        nwsWind.reactionLine->setText("Too late");
        nwsWind.close();
        if(core.ANWFlag||core.crisis) { core.QuitFlag=true; EndGame(); }
    }
    nwsWind.reactionLine->setText(GenerateReactionHLine(subject,cris.crisisLevel,false,false));
}

void MainBox::doCrisis(int WH){
    if(!cris.isBegun){
        cris.resetCrisData();
        cris.isBegun=true;
        cris.whichHead=WH;
        cris.who=core.news[cris.whichHead].actor;
        cris.victim=core.news[cris.whichHead].victim;
        cris.crisisLevel=9;
        cris.backDown=false; core.crisis=false;
        cris.rand1=rand()%32768;
        cris.rand2=rand()%32768;
        cris.aggrFlag=(cris.who==core.cmptr);
        if(cris.aggrFlag){
            if(core.human==0) cris.x=1; else cris.x=-1;
            core.ChgDMess(cris.victim,cris.x);
        }
        nwsWind.setWindowTitle("Backchannel communication");
        nwsWind.newsHeadline->setText("In "+resrc.strg[154+core.news[cris.whichHead].host]+",\n"+core.news[cris.whichHead].headLine);
        nwsWind.reactionLine->setText(GenerateReactionHLine(!cris.who,cris.crisisLevel,false,false));
        if(!OSX_Flag) nwsWind.setWindowFlags(nwsWind.windowFlags()&~Qt::WindowCloseButtonHint);
        else nwsWind.setWindowFlags(nwsWind.windowFlags()|Qt::FramelessWindowHint);
        nwsWind.show();
        nwsWind.next->setDisabled(true);
        nwsWind.previous->setDisabled(true);
        nwsWind.backDown->setDisabled(false);
        nwsWind.question->setDisabled(false);
        nwsWind.backDown->setText("Back Down");
        if(cris.who==core.human) {
            createAdvPanel();
            for(int i=0;i<4;i++){
                cris.x=-core.GImpt(cris.victim,core.news[cris.whichHead].verb,cris.who,core.news[cris.whichHead].oldNVal,core.news[cris.whichHead].newNVal,i);
                cris.x/=8;
                cris.x++;
                if(cris.x<-15)cris.x=-15;
                if(cris.x>16)cris.x=16;
                cris.x+=16;
                nwsWind.advice[i]->setText(resrc.strg[553+cris.x]);
            }
        }
    }
    QTextStream out(stdout);
    out<<cris.victim<<" "<<cris.who<<" "<<core.news[cris.whichHead].verb<<" "<<cris.whichHead<<endl;
    if(cris.aggrFlag&&!core.TwoPFlag){
        //computer considerations
        cris.x=core.GImpt(cris.victim,core.news[cris.whichHead].verb,cris.who,core.news[cris.whichHead].oldNVal,core.news[cris.whichHead].newNVal,0);
        cris.HLoss=core.USAImpt; cris.CGain=core.USSRImpt;
        if(cris.who==core.human) cris.x=-cris.x;
        if(cris.x<4*cris.crisisLevel-36+abs((rand()%32768)/1024)){
            HangTough(core.cmptr);
        }
        else {
            cris.backDown=true;
            cris.isBegun=false;
            core.news[cris.whichHead].crisisVal=true;
            HangLoose(core.cmptr,core.human);
        }
    }

    if(cris.backDown==false&&cris.crisisLevel>1){
        cris.sumLoser=0; cris.sumWinner=0;
        if(cris.crisisLevel<8){
            cris.HLoss=core.GImpt(cris.victim,core.news[cris.whichHead].verb,cris.who,core.news[cris.whichHead].oldNVal,core.news[cris.whichHead].newNVal,0);
            cris.y=core.USAImpt; cris.z=core.USSRImpt;
            cris.x=(abs(cris.y)/cris.crisisLevel)+(abs(cris.z)/cris.crisisLevel)+8-cris.crisisLevel;
            cris.y=0;
            for(int i=2;i<N;i++){
                cris.Usez=cris.x/32;
                cris.y+=(cris.x%32);
                if(cris.y>32) { cris.Usez++; cris.y-=32; }
                cris.Usex=-cris.Usez;
                cris.DAow=core.state[i].overallRelationship[core.cmptr];
                cris.DAol=core.state[i].overallRelationship[core.human];
                if(cris.DAol+cris.Usex>127) cris.Usex=127-cris.DAol;
                if(cris.DAol+cris.Usex<-127) cris.Usex=-127-cris.DAol;
                if(cris.DAow+cris.Usez>127) cris.Usez=127-cris.DAow;
                if(cris.DAow+cris.Usez<-127) cris.Usez=127-cris.DAow;
                cris.sumWinner+=(cris.Usez*core.state[i].prestVal);
                cris.sumLoser+=(cris.Usex*core.state[i].prestVal);
            }
            if(cris.sumLoser>8132352) cris.sumLoser=8132352;
            if(cris.sumLoser<-8132352) cris.sumLoser=-8132352;

        }
        cris.HLoss=-(cris.sumLoser/1024);
        cris.CGain=-(cris.sumWinner/1024);
        nwsWind.leftInfo[0]->setText("<b>Prestige at risk:</b>");
        nwsWind.leftInfoVal[0]->setText(QString::number(cris.HLoss));
        switch(core.level){
            case 1: cris.y=2048; break;
            case 2: cris.y=1024; break;
            case 3: cris.y=512; break;
            case 4: cris.y=512; break;
        }
        cris.x=core.GImpt(cris.victim,core.news[cris.whichHead].verb,cris.who,core.news[cris.whichHead].oldNVal,core.news[cris.whichHead].newNVal,0);
        cris.HLoss=core.USAImpt; cris.CGain=core.USSRImpt;
        cris.x=(cris.HLoss+(cris.rand1/cris.y))/16;
        cris.x=abs(cris.x);
        if(cris.x>7) cris.x=7;
        nwsWind.leftInfo[1]->setText("<b>USA interest:</b>");
        nwsWind.leftInfoVal[1]->setText(resrc.strg[615+cris.x]);
        cris.x=(cris.CGain+(cris.rand2/cris.y))/16;
        cris.x=abs(cris.x);
        if(cris.x>7) cris.x=7;
        nwsWind.leftInfo[2]->setText("<b>USSR interest:</b>");
        nwsWind.leftInfoVal[2]->setText(resrc.strg[615+cris.x]);
    }
    nwsWind.question->setText(resrc.strg[632+cris.crisisLevel]);
    cris.aggrFlag=true;
}

//-----------------
void MainBox::MinorTough(){
    int x;
    cris.crisisLevel--;
    x=0;
    switch(cris.crisisLevel){
        case 2: x=32; break;
        case 3: x=16; break;
        case 4: x=8; break;
        case 5: x=4; break;
        case 6: x=2; break;
        case 7: x=1; break;
        case 8: x=0; break;
    }
    core.ChgDipAff(cris.who,core.human,-x);
    nwsWind.reactionLine->setText(GenerateReactionHLine(cris.who,cris.crisisLevel,true,false));

    if(cris.crisisLevel<2){
        cris.backDown=true;
        cris.isBegun=false;
        nwsWind.reactionLine->setText(GenerateReactionHLine(cris.who,cris.crisisLevel,true,true));
        nwsWind.question->setDisabled(true);
        nwsWind.backDown->setText("OK");
    }
    nwsWind.question->setText(resrc.strg[641+cris.crisisLevel]);
}

void MainBox::MinorCrisis(int WH){
    if(!cris.isBegun){
        cris.resetCrisData();
        cris.isBegun=true;
        cris.whichHead=WH;
        cris.who=core.news[cris.whichHead].actor;
        cris.victim=core.news[cris.whichHead].victim;
        cris.crisisLevel=9;
        cris.backDown=false; core.crisis=false;
        if(core.human==0) cris.x=1; else cris.x=-1;
        core.ChgDMess(cris.victim,cris.x);
        if(!OSX_Flag)nwsWind.setWindowFlags(nwsWind.windowFlags()|Qt::WindowCloseButtonHint);
        else nwsWind.setWindowFlags(nwsWind.windowFlags()|Qt::FramelessWindowHint);
        nwsWind.show();
        nwsWind.next->setDisabled(true);
        nwsWind.previous->setDisabled(true);
        nwsWind.backDown->setDisabled(false);
    }
    cris.x=(abs(core.state[cris.victim].dontMess-core.AveDMess)*core.Influence(core.human,cris.who));
    switch(cris.crisisLevel){
        case 9: cris.y=1; break;
        case 8: cris.y=1; break;
        case 7: cris.y=2; break;
        case 6: cris.y=2; break;
        case 5: cris.y=4; break;
        case 4: cris.y=4; break;
        case 3: cris.y=8; break;
        case 2: cris.y=8; break;
        case 1: cris.y=16; break;
    }
    if(cris.x*cris.y<4*cris.crisisLevel-36+abs((rand()%32768)/(cris.y*256))){
        MinorTough();
    }
    else {
        cris.backDown=true;
        cris.isBegun=false;
        core.news[cris.whichHead].crisisVal=true;
        core.DoPolicy(cris.victim,core.news[cris.whichHead].verb,cris.who,core.news[cris.whichHead].oldNVal,true);
        nwsWind.reactionLine->setText(GenerateReactionHLine(cris.who,cris.crisisLevel,true,true));
        nwsWind.question->setDisabled(true);
        nwsWind.backDown->setText("OK");
    }

}
//----------------------
void MainBox::Tough(){
    int x,y;
    cris.crisisLevel--;
    switch(cris.crisisLevel){
        case 2: x=32; break;
        case 3: x=16; break;
        case 4: x=8; break;
        case 5: x=4; break;
        case 6: x=2; break;
        case 7: x=1; break;
        case 8: x=0; break;
    }
    core.ChgDipAff(cris.who,core.cmptr,-x);
}
void MainBox::CmptrCrisis(int WH){
    cris.resetCrisData();
    cris.whichHead=WH;
    cris.who=core.news[cris.whichHead].actor;
    cris.victim=core.news[cris.whichHead].victim;
    cris.crisisLevel=9;
    if(core.cmptr==0) cris.x=1; else cris.x=-1;
    core.ChgDMess(cris.victim,cris.x);
    do {
        cris.x=(abs(core.state[cris.victim].dontMess-core.AveDMess)*core.Influence(core.cmptr,cris.who))/8;
        switch(cris.crisisLevel){
            case 9: cris.y=1; break;
            case 8: cris.y=1; break;
            case 7: cris.y=2; break;
            case 6: cris.y=2; break;
            case 5: cris.y=4; break;
            case 4: cris.y=4; break;
            case 3: cris.y=8; break;
            case 2: cris.y=8; break;
            case 1: cris.y=16; break;
        }
        if(cris.x*cris.y<4*cris.crisisLevel-36+abs((rand()%32768)/(cris.y*256))) Tough();
        else {
            cris.backDown=true;
            core.news[cris.whichHead].crisisVal=true;
            core.DoPolicy(cris.victim,core.news[cris.whichHead].verb,cris.who,core.news[cris.whichHead].oldNVal,true);
        }
        if(!cris.backDown&&cris.crisisLevel>1){
            //AI superpower consideration
            cris.x=core.GImpt(cris.victim,core.news[cris.whichHead].verb,cris.who,core.news[cris.whichHead].oldNVal,core.news[cris.whichHead].newNVal,0);
            cris.y=core.USAImpt; cris.z=core.USSRImpt;
            if(core.cmptr==0) cris.z=cris.y;
            if(cris.z>4*cris.crisisLevel-36+abs((rand()%32768)/1024)) Tough();
            else { cris.backDown=true; core.news[cris.whichHead].crisisVal=true; }
        }
    } while(!cris.backDown&&cris.crisisLevel>1);
}
//---------------------
QString MainBox::GenerateTextStr(int startingAt, int howManyStrings){
    int skip,count,pos;
    QString string;
    for(int i=0+startingAt;i<howManyStrings+startingAt;i++){
        skip=rand()%4;
        count=0; pos=0;
        while(count<skip&&pos<resrc.strg[i].size()){
            if(resrc.strg[i][pos]=='*') count++;
            pos++;
        }
        while(resrc.strg[i][pos]!='*'&&pos<resrc.strg[i].size()){
            string.append(resrc.strg[i][pos]);
            pos++;
        }
    }
    return string;
}

QString MainBox::GenerateReactionHLine(int who, int crisisLevel, bool isMinor, bool isBDown){
    QString string;
    int startingAt,howManyStrings;
    if(!isMinor){
        if(who==0) startingAt=703;
        else startingAt=704;
        howManyStrings=1;
        string+=GenerateTextStr(startingAt,howManyStrings);
        if(!isBDown){
            if(crisisLevel==9){ startingAt=705; howManyStrings=2; }
            if(crisisLevel==8){ startingAt=707; howManyStrings=2; }
            if(crisisLevel==7){ startingAt=709; howManyStrings=3; }
            if(crisisLevel==6){ startingAt=712; howManyStrings=3; }
            if(crisisLevel==5){ startingAt=715; howManyStrings=4; }
            if(crisisLevel==4){ startingAt=719; howManyStrings=2; }
            if(crisisLevel==3){ startingAt=721; howManyStrings=3; }
            if(crisisLevel==2){ startingAt=724; howManyStrings=3; }
        }
        else {
            if(crisisLevel==9){ startingAt=727; howManyStrings=2; }
            if(crisisLevel==8){ startingAt=729; howManyStrings=3; }
            if(crisisLevel==7){ startingAt=732; howManyStrings=2; }
            if(crisisLevel==6){ startingAt=734; howManyStrings=3; }
            if(crisisLevel==5){ startingAt=737; howManyStrings=2; }
            if(crisisLevel==4){ startingAt=739; howManyStrings=3; }
            if(crisisLevel==3){ startingAt=742; howManyStrings=2; }
            if(crisisLevel==2){ startingAt=744; howManyStrings=3; }
        }
        string+=GenerateTextStr(startingAt,howManyStrings);
    }
    else{
        if(who>1){
            if(!isBDown){
                if(crisisLevel>1) startingAt=854;
                if(crisisLevel>3) startingAt=850;
                if(crisisLevel>5) startingAt=846;
                if(crisisLevel>7) startingAt=842;
            }
            else startingAt=862;
            howManyStrings=4;
            string+=GenerateTextStr(startingAt,howManyStrings);
        }
        else{
            if(who==0) startingAt=866;
            else startingAt=867;
            howManyStrings=1;
            string+=GenerateTextStr(startingAt,howManyStrings);
            startingAt=868;
            howManyStrings=3;
            string+=GenerateTextStr(startingAt,howManyStrings);
        }
    }
    return string;
}

void MainBox::doCHumanLoose(){
    //if crisis against computer
    //if(core.news[listNews[curPage]].actor<2){
    if(cris.who<2){
        if(!cris.backDown){
            cris.backDown=true;
            cris.isBegun=false;
            HangLoose(core.human,core.cmptr);
            if(core.TwoPFlag&&cris.crisisLevel%2) { changeSides(); }
        }
        else {
            nwsWind.setWindowFlags(nwsWind.windowFlags()|Qt::WindowCloseButtonHint);
            nwsWind.next->setDisabled(false);
            nwsWind.previous->setDisabled(false);
            nwsWind.question->setDisabled(false);
            nwsWind.backDown->setText("Back Down");
            nwsWind.backDown->setDisabled(true);
            nwsWind.reactionLine->setText("");
            for(int i=0;i<3;i++){
                nwsWind.leftInfo[i]->setText("");
                nwsWind.leftInfoVal[i]->setText("");
            }
            if(cris.who==core.cmptr) showNewsWindow(curNewsMode);
            else {
                if(curQuest+1<questSize){
                    cris.resetCrisData();
                    curQuest++;
                    listNews[curPage]=QuestQueue[curQuest];
                    doCrisis(listNews[curPage]);
                    nwsWind.show();
                }
                else {
                    questSize=0;
                    curQuest=0;
                    nwsWind.close();
                    continueNextTurn();
                }
            }
        }
    }
    //if crisis against minor country
    else {
        if(!cris.backDown){
            cris.backDown=true;
            cris.isBegun=false;
            nwsWind.reactionLine->setText("Backing down by "+resrc.strg[154+cris.who]);
            nwsWind.reactionLine->setText(GenerateReactionHLine(core.human,cris.crisisLevel,true,true));
            nwsWind.question->setDisabled(true);
            nwsWind.backDown->setText("OK");
        }
        else{
            nwsWind.setWindowFlags(nwsWind.windowFlags()|Qt::WindowCloseButtonHint);
            nwsWind.next->setDisabled(false);
            nwsWind.previous->setDisabled(false);
            nwsWind.question->setDisabled(false);
            nwsWind.backDown->setText("Back Down");
            nwsWind.backDown->setDisabled(true);
            nwsWind.reactionLine->setText("");
            for(int i=0;i<3;i++){
                nwsWind.leftInfo[i]->setText("");
                nwsWind.leftInfoVal[i]->setText("");
            }
            showNewsWindow(curNewsMode);
        }
    }
    core.calcScores();
    drawScores();
}

void MainBox::doCHumanTough(){
    //if crisis against computer
    if(core.news[listNews[curPage]].actor<2){
        if((cris.crisisLevel<9&&cris.isBegun)||(cris.crisisLevel==9&&cris.who==core.human&&cris.isBegun)) HangTough(core.human);
        if(!core.crisis&&!core.ANWFlag) doCrisis(listNews[curPage]);
        if(!core.crisis&&!core.ANWFlag) nwsWind.show();
        if(core.TwoPFlag){ changeSides(); }
    }
    //if crisis against minor country
    else {
        if(cris.crisisLevel<9&&cris.isBegun) MinorTough();
        MinorCrisis(listNews[curPage]);
        nwsWind.show();
    }
}



