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

void MainBox::createActions(){
    mapModeAct[0]=new QAction(tr("Spheres of Influence"),this);
    mapModeAct[1]=new QAction(tr("Major Events"),this);
    mapModeAct[2]=new QAction(tr("Prestige Value"),this);
    mapModeAct[3]=new QAction(tr("Insurgency"),this);
    mapModeAct[4]=new QAction(tr("Coup d'etat?"),this);
    mapModeAct[5]=new QAction(tr("Finlandization - USA?"),this);
    mapModeAct[6]=new QAction(tr("Finlandization - USSR?"),this);
    mapModeAct[7]=new QAction(tr("Countries at War"),this);
    mapModeAct[8]=new QAction(tr("going out"),this);
    mapModeAct[9]=new QAction(tr("going in"),this);
    mapModeAct[10]=new QAction(tr("going out"),this);
    mapModeAct[11]=new QAction(tr("going in"),this);
    mapModeAct[12]=new QAction(tr("going out"),this);
    mapModeAct[13]=new QAction(tr("going in"),this);
    mapModeAct[14]=new QAction(tr("going out"),this);
    mapModeAct[15]=new QAction(tr("going in"),this);
    mapModeAct[16]=new QAction(tr("going out"),this);
    mapModeAct[17]=new QAction(tr("going in"),this);
    mapModeAct[18]=new QAction(tr("Economic Aid"),this);
    mapModeAct[19]=new QAction(tr("Destabilization"),this);
    mapModeAct[20]=new QAction(tr("Diplomatic Pressure"),this);
    mapModeAct[21]=new QAction(tr("Treaties"),this);
    mapModeAct[22]=new QAction(tr("Trade Policies"),this);
    mapModeAct[23]=new QAction(tr("per nothing"),this);
    mapModeAct[24]=new QAction(tr("per capita"),this);
    mapModeAct[25]=new QAction(tr("per nothing"),this);
    mapModeAct[26]=new QAction(tr("per capita"),this);
    mapModeAct[27]=new QAction(tr("per GDP"),this);
    mapModeAct[28]=new QAction(tr("per nothing"),this);
    mapModeAct[29]=new QAction(tr("per capita"),this);
    mapModeAct[30]=new QAction(tr("per GDP"),this);
    mapModeAct[31]=new QAction(tr("per nothing"),this);
    mapModeAct[32]=new QAction(tr("per capita"),this);
    mapModeAct[33]=new QAction(tr("per GDP"),this);
    mapModeAct[34]=new QAction(tr("Population"),this);
    mapModeAct[35]=new QAction(tr("Military Personnel"),this);
    mapModeAct[36]=new QAction(tr("At War With"),this);

    doEconomy=new QAction(tr("Economy"),this);
    doCloseUp=new QAction(tr("Close-Up"),this);
    doHistory=new QAction(tr("History"),this);
    doNews[0]=new QAction(tr("Newspaper"),this);
    doNews[1]=new QAction(tr("USA Actions"),this);
    doNews[2]=new QAction(tr("USA Other"),this);
    doNews[3]=new QAction(tr("USSR Actions"),this);
    doNews[4]=new QAction(tr("USSR Other"),this);
    doNews[5]=new QAction(tr("Minor Country News"),this);
    doPolicy[0]=new QAction(tr("Destabilization"),this);
    doPolicy[1]=new QAction(tr("Economic Aid"),this);
    doPolicy[2]=new QAction(tr("Military Aid"),this);
    doPolicy[3]=new QAction(tr("Aid to Insurgents"),this);
    doPolicy[4]=new QAction(tr("Intervene for Govt"),this);
    doPolicy[5]=new QAction(tr("Intervene for Rebels"),this);
    doPolicy[6]=new QAction(tr("Diplomatic Pressure"),this);
    doPolicy[7]=new QAction(tr("Treaty"),this);
    doScore=new QAction(tr("Scores"),this);
    newGameAct=new QAction(tr("New Game"),this);
    saveGameAct=new QAction(tr("Save Game"),this);
    chgSideAct=new QAction(tr("Change Sides"),this);
    nextTurnAct=new QAction(tr("Next Turn"),this);
    about=new QAction(tr("About..."),this);

    connect(mapModeAct[0],SIGNAL(triggered()),this,SLOT(drawMap0()));
    connect(mapModeAct[1],SIGNAL(triggered()),this,SLOT(drawMap1()));
    connect(mapModeAct[2],SIGNAL(triggered()),this,SLOT(drawMap2()));
    connect(mapModeAct[3],SIGNAL(triggered()),this,SLOT(drawMap3()));
    connect(mapModeAct[4],SIGNAL(triggered()),this,SLOT(drawMap4()));
    connect(mapModeAct[5],SIGNAL(triggered()),this,SLOT(drawMap5()));
    connect(mapModeAct[6],SIGNAL(triggered()),this,SLOT(drawMap6()));
    connect(mapModeAct[7],SIGNAL(triggered()),this,SLOT(drawMap7()));
    connect(mapModeAct[8],SIGNAL(triggered()),this,SLOT(drawMap8()));
    connect(mapModeAct[9],SIGNAL(triggered()),this,SLOT(drawMap9()));
    connect(mapModeAct[10],SIGNAL(triggered()),this,SLOT(drawMap10()));
    connect(mapModeAct[11],SIGNAL(triggered()),this,SLOT(drawMap11()));
    connect(mapModeAct[12],SIGNAL(triggered()),this,SLOT(drawMap12()));
    connect(mapModeAct[13],SIGNAL(triggered()),this,SLOT(drawMap13()));
    connect(mapModeAct[14],SIGNAL(triggered()),this,SLOT(drawMap14()));
    connect(mapModeAct[15],SIGNAL(triggered()),this,SLOT(drawMap15()));
    connect(mapModeAct[16],SIGNAL(triggered()),this,SLOT(drawMap16()));
    connect(mapModeAct[17],SIGNAL(triggered()),this,SLOT(drawMap17()));
    connect(mapModeAct[18],SIGNAL(triggered()),this,SLOT(drawMap18()));
    connect(mapModeAct[19],SIGNAL(triggered()),this,SLOT(drawMap19()));
    connect(mapModeAct[20],SIGNAL(triggered()),this,SLOT(drawMap20()));
    connect(mapModeAct[21],SIGNAL(triggered()),this,SLOT(drawMap21()));
    connect(mapModeAct[22],SIGNAL(triggered()),this,SLOT(drawMap22()));
    connect(mapModeAct[23],SIGNAL(triggered()),this,SLOT(drawMap23()));
    connect(mapModeAct[24],SIGNAL(triggered()),this,SLOT(drawMap24()));
    connect(mapModeAct[25],SIGNAL(triggered()),this,SLOT(drawMap25()));
    connect(mapModeAct[26],SIGNAL(triggered()),this,SLOT(drawMap26()));
    connect(mapModeAct[27],SIGNAL(triggered()),this,SLOT(drawMap27()));
    connect(mapModeAct[28],SIGNAL(triggered()),this,SLOT(drawMap28()));
    connect(mapModeAct[29],SIGNAL(triggered()),this,SLOT(drawMap29()));
    connect(mapModeAct[30],SIGNAL(triggered()),this,SLOT(drawMap30()));
    connect(mapModeAct[31],SIGNAL(triggered()),this,SLOT(drawMap31()));
    connect(mapModeAct[32],SIGNAL(triggered()),this,SLOT(drawMap32()));
    connect(mapModeAct[33],SIGNAL(triggered()),this,SLOT(drawMap33()));
    connect(mapModeAct[34],SIGNAL(triggered()),this,SLOT(drawMap34()));
    connect(mapModeAct[35],SIGNAL(triggered()),this,SLOT(drawMap35()));
    connect(mapModeAct[36],SIGNAL(triggered()),this,SLOT(drawMap36()));

    connect(doCloseUp,SIGNAL(triggered()),this,SLOT(showCountryCloseUp()));
    connect(doEconomy,SIGNAL(triggered()),this,SLOT(showEconomy()));
    connect(doHistory,SIGNAL(triggered()),this,SLOT(showHistory()));
    connect(doNews[0],SIGNAL(triggered()),this,SLOT(showNewsp()));
    connect(doNews[1],SIGNAL(triggered()),this,SLOT(showUSAA()));
    connect(doNews[2],SIGNAL(triggered()),this,SLOT(showUSAO()));
    connect(doNews[3],SIGNAL(triggered()),this,SLOT(showUSSRA()));
    connect(doNews[4],SIGNAL(triggered()),this,SLOT(showUSSRO()));
    connect(doNews[5],SIGNAL(triggered()),this,SLOT(showMIN()));
    connect(doPolicy[0],SIGNAL(triggered()),this,SLOT(doDestab()));
    connect(doPolicy[1],SIGNAL(triggered()),this,SLOT(doEconAid()));
    connect(doPolicy[2],SIGNAL(triggered()),this,SLOT(doMilAid()));
    connect(doPolicy[3],SIGNAL(triggered()),this,SLOT(doRebAid()));
    connect(doPolicy[4],SIGNAL(triggered()),this,SLOT(doMilIntv()));
    connect(doPolicy[5],SIGNAL(triggered()),this,SLOT(doRebIntv()));
    connect(doPolicy[6],SIGNAL(triggered()),this,SLOT(doPress()));
    connect(doPolicy[7],SIGNAL(triggered()),this,SLOT(doTreaty()));

    connect(doScore,SIGNAL(triggered()),this,SLOT(showScores()));
    connect(newGameAct,SIGNAL(triggered()),this,SLOT(showNewGame()));
    connect(saveGameAct,SIGNAL(triggered()),this,SLOT(doSaveGame()));
    connect(chgSideAct,SIGNAL(triggered()),this,SLOT(changeSides()));
    connect(nextTurnAct,SIGNAL(triggered()),this,SLOT(doNextTurn()));

    connect(about,SIGNAL(triggered()),this,SLOT(doAbout()));

    mapGroup=new QActionGroup(this);
    for(int i=0;i<37;i++) {
        mapModeAct[i]->setCheckable(true);
        mapGroup->addAction(mapModeAct[i]);
    }

    contTitle=new QAction(this);

}

void MainBox::correctMenus(){
    //disable some mapmodes which are useless on lower levels
    for(int i=4;i<8;i++) mapModeAct[i]->setDisabled(false);
    if(core.level==1) for(int i=4;i<8;i++) mapModeAct[i]->setDisabled(true);
    if(core.level==2) for(int i=5;i<8;i++) mapModeAct[i]->setDisabled(true);
    if(core.level==3) mapModeAct[7]->setDisabled(true);
    if(core.TwoPFlag) { nextTurnAct->setDisabled(true); chgSideAct->setDisabled(false); }
    else { nextTurnAct->setDisabled(false); chgSideAct->setDisabled(true); }
}

void MainBox::createMenus(){

    gameMenu=menuBar()->addMenu("Game");
    gameMenu->addAction(newGameAct);
    gameMenu->addAction(saveGameAct);
    gameMenu->addSeparator();
    gameMenu->addAction(nextTurnAct);
    gameMenu->addAction(chgSideAct);
    gameMenu->addAction(doScore);

    mapModeMenus=menuBar()->addMenu("View");
    countriesMenu=mapModeMenus->addMenu(tr("Countries"));
    for(int i=0;i<8;i++) countriesMenu->addAction(mapModeAct[i]);
    relationsMenu=mapModeMenus->addMenu(tr("Relations"));
    diplMenu=relationsMenu->addMenu(tr("Diplomatic Relationships"));
    diplMenu->addAction(mapModeAct[8]);
    diplMenu->addAction(mapModeAct[9]);
    milAidMenu=relationsMenu->addMenu(tr("Military Aid"));
    milAidMenu->addAction(mapModeAct[10]);
    milAidMenu->addAction(mapModeAct[11]);
    rebAidMenu=relationsMenu->addMenu(tr("Aid to Insurgents"));
    rebAidMenu->addAction(mapModeAct[12]);
    rebAidMenu->addAction(mapModeAct[13]);
    milIntvMenu=relationsMenu->addMenu(tr("Intervene for Govt"));
    milIntvMenu->addAction(mapModeAct[14]);
    milIntvMenu->addAction(mapModeAct[15]);
    rebIntvMenu=relationsMenu->addMenu(tr("Intervene for Rebels"));
    rebIntvMenu->addAction(mapModeAct[16]);
    rebIntvMenu->addAction(mapModeAct[17]);
    relationsMenu->addAction(mapModeAct[36]);
    for(int i=18;i<22;i++) relationsMenu->addAction(mapModeAct[i]);
    resourcesMenu=mapModeMenus->addMenu(tr("Resources"));
    GDPMenu=resourcesMenu->addMenu(tr("GDP"));
    GDPMenu->addAction(mapModeAct[23]);
    GDPMenu->addAction(mapModeAct[24]);
    GDPSpndMenu[0]=resourcesMenu->addMenu(tr("Consumer Spending"));
    GDPSpndMenu[1]=resourcesMenu->addMenu(tr("Investment Spending"));
    GDPSpndMenu[2]=resourcesMenu->addMenu(tr("Military Spending"));

    for(int i=0,j=25;i<3;i++,j+=3){
        GDPSpndMenu[i]->addAction(mapModeAct[j]);
        GDPSpndMenu[i]->addAction(mapModeAct[j+1]);
        GDPSpndMenu[i]->addAction(mapModeAct[j+2]);
    }
    resourcesMenu->addAction(mapModeAct[34]);
    resourcesMenu->addAction(mapModeAct[35]);

    makePolicyMenu=menuBar()->addMenu("Make Policies");
    for(int i=0;i<8;i++) makePolicyMenu->addAction(doPolicy[i]);

    eventsMenu=menuBar()->addMenu("Events");
    for(int i=0;i<6;i++) eventsMenu->addAction(doNews[i]);

    briefingMenu=menuBar()->addMenu("Selection");
    briefingMenu->addAction(doCloseUp);
    briefingMenu->addAction(doEconomy);
    briefingMenu->addAction(doHistory);

    helpMenu=menuBar()->addMenu("Help");
    helpMenu->addAction(about);


    //and now - contextual menus
    for(int i=0;i<3;i++){
        contMenu[i]=new QMenu(this);
        contMenu[i]->addAction(contTitle);
        contMenu[i]->addSeparator();
        if(i==0){
            //USA Menu
            contMenu[i]->addAction(doCloseUp);
            contMenu[i]->addAction(doEconomy);
            contMenu[i]->addAction(doNews[1]);
            contMenu[i]->addAction(doNews[2]);
        }
        else if(i==1){
            //USSR Menu
            contMenu[i]->addAction(doCloseUp);
            contMenu[i]->addAction(doEconomy);
            contMenu[i]->addAction(doNews[3]);
            contMenu[i]->addAction(doNews[4]);
        }
        else {
            contMenu[i]->addAction(doCloseUp);
            contMenu[i]->addAction(doEconomy);
            contMenu[i]->addAction(doHistory);
            contMenu[i]->addAction(doNews[0]);
            contMenu[i]->addSeparator();
            for(int j=0;j<8;j++){
                contMenu[i]->addAction(doPolicy[j]);
            }
        }
    }
}

void MainBox::createToolbars(){

    //and also put icons into actions
    actionToolBar=addToolBar("Main Toolbar");
    mapModeToolBar=new QToolBar("Map Mode Toolbar");
    gameToolBar=new QToolBar("Gameplay Toolbar");
    addToolBar(Qt::BottomToolBarArea,mapModeToolBar);
    addToolBar(Qt::BottomToolBarArea,gameToolBar);
    QIcon iconSet;
    QPixmap iconSetPix;
    QPixmap tempPix; //for trimming
    iconSetPix.load(":/images/icons2.png","PNG");
    for(int i=0;i<8;i++){
        //add action icons
        tempPix=iconSetPix.copy(i*64+i+1,1,64,64);
        iconSet.addPixmap(tempPix,QIcon::Normal,QIcon::On);
        doPolicy[i]->setIcon(iconSet);
        actionToolBar->addAction(doPolicy[i]);

        //add basic mapmodes to mapmode bar
        tempPix=iconSetPix.copy(i*64+i+1,131,64,64);
        iconSet.addPixmap(tempPix,QIcon::Normal,QIcon::On);
        mapModeAct[i]->setIcon(iconSet);
        mapModeToolBar->addAction(mapModeAct[i]);
    }
    mapModeToolBar->addSeparator();
    actionToolBar->addSeparator();

    //add close-up
    tempPix=iconSetPix.copy(1,196,64,64);
    iconSet.addPixmap(tempPix,QIcon::Normal,QIcon::On);
    doCloseUp->setIcon(iconSet);
    actionToolBar->addAction(doCloseUp);
    //add history
    tempPix=iconSetPix.copy(66,196,64,64);
    iconSet.addPixmap(tempPix,QIcon::Normal,QIcon::On);
    doHistory->setIcon(iconSet);
    actionToolBar->addAction(doHistory);
    //add newspaper
    tempPix=iconSetPix.copy(131,196,64,64);
    iconSet.addPixmap(tempPix,QIcon::Normal,QIcon::On);
    doNews[0]->setIcon(iconSet);
    actionToolBar->addAction(doNews[0]);
    actionToolBar->addSeparator();

    for(int i=0;i<5;i++){
        //add next mapmodes to mapmode bar
        tempPix=iconSetPix.copy(i*64+i+1,66,64,64);
        iconSet.addPixmap(tempPix,QIcon::Normal,QIcon::On);
        mapModeAct[2*i+8]->setIcon(iconSet);
        mapModeToolBar->addAction(mapModeAct[2*i+8]);

        //add news items to first bar
        tempPix=iconSetPix.copy(i*64+i+196,196,64,64);
        iconSet.addPixmap(tempPix,QIcon::Normal,QIcon::On);
        doNews[i+1]->setIcon(iconSet);
        actionToolBar->addAction(doNews[i+1]);
    }
    for(int i=6;i<10;i++){
        //add next mapmodes to mapmode bar
        tempPix=iconSetPix.copy(i*64+i+1,66,64,64);
        iconSet.addPixmap(tempPix,QIcon::Normal,QIcon::On);
        mapModeAct[i+12]->setIcon(iconSet);
        mapModeToolBar->addAction(mapModeAct[i+12]);
    }
    //add 'at war with' mapmode to mapmode bar
    tempPix=iconSetPix.copy(326,66,64,64);
    iconSet.addPixmap(tempPix,QIcon::Normal,QIcon::On);
    mapModeAct[36]->setIcon(iconSet);
    mapModeToolBar->addAction(mapModeAct[36]);
    mapModeToolBar->addSeparator();
    mapModeToolBar->addSeparator();
    mapModeToolBar->addSeparator();

    //add 'switch sides' and 'next turn' to gameToolBar
    tempPix=iconSetPix.copy(392,262,64,64);
    iconSet.addPixmap(tempPix,QIcon::Normal,QIcon::On);
    chgSideAct->setIcon(tempPix);
    tempPix=iconSetPix.copy(456,262,64,64);
    iconSet.addPixmap(tempPix,QIcon::Normal,QIcon::On);
    nextTurnAct->setIcon(iconSet);
    gameToolBar->addSeparator();
    gameToolBar->addSeparator();
    gameToolBar->addSeparator();
    gameToolBar->addAction(chgSideAct);
    gameToolBar->addAction(nextTurnAct);
    gameToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    actionToolBar->setIconSize(QSize(32,32));
    mapModeToolBar->setIconSize(QSize(32,32));
    gameToolBar->setIconSize(QSize(18,18));
    actionToolBar->setMovable(false);
    mapModeToolBar->setMovable(false);
    gameToolBar->setMovable(false);
    mapModeToolBar->setAllowedAreas(Qt::NoToolBarArea);
    actionToolBar->setAllowedAreas(Qt::TopToolBarArea);
    mapModeToolBar->setAllowedAreas(Qt::BottomToolBarArea);
    gameToolBar->setAllowedAreas(Qt::BottomToolBarArea);
    actionToolBar->setContextMenuPolicy(Qt::NoContextMenu);
    mapModeToolBar->setContextMenuPolicy(Qt::NoContextMenu);
}

void MainBox::doSaveGame(){
    core.saveGame();
    saveBox.exec();
}
