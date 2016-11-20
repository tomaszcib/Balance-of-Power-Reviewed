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

#ifndef MAINBOX_H
#define MAINBOX_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QMenu>
#include <QAction>
//#include <QtWidgets>
#include <QtGui>
#include <string>
#include "resources.h"
#include "core.h"
#include "dialogWindows.h"
#include "shapeitem.h"
#include "crisis.h"
using namespace std;

QT_BEGIN_NAMESPACE
class QAction;
class QPoint;
class QToolButton;
class QMenu;
QT_END_NAMESPACE

//! [0]
class MainBox : public QMainWindow{
    Q_OBJECT

public:
    MainBox();
    bool OSX_Flag;

protected:
    bool event(QEvent *event);
    void paintEvent(QPaintEvent *event);
    void initMapPolygons();
    void initLegend();
    void drawLegend(int t, int addParam);
    QString captionCreate(int t, int addParam, int val);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private slots:
    void drawMap(int t, int addParam, bool inOutMode);
    void drawMap0();
    void drawMap1();
    void drawMap2();
    void drawMap3();
    void drawMap4();
    void drawMap5();
    void drawMap6();
    void drawMap7();
    void drawMap8();
    void drawMap9();
    void drawMap10();
    void drawMap11();
    void drawMap12();
    void drawMap13();
    void drawMap14();
    void drawMap15();
    void drawMap16();
    void drawMap17();
    void drawMap18();
    void drawMap19();
    void drawMap20();
    void drawMap21();
    void drawMap22();
    void drawMap23();
    void drawMap24();
    void drawMap25();
    void drawMap26();
    void drawMap27();
    void drawMap28();
    void drawMap29();
    void drawMap30();
    void drawMap31();
    void drawMap32();
    void drawMap33();
    void drawMap34();
    void drawMap35();
    void drawMap36();
    void showCountryCloseUp();
    void showHistory();
    void nextNews();
    void prevNews();
    void showNewsp();
    void showUSAA();
    void showUSAO();
    void showUSSRA();
    void showUSSRO();
    void showMIN();
    void doDestab();
    void doEconAid();
    void doMilAid();
    void doRebAid();
    void doMilIntv();
    void doRebIntv();
    void doPress();
    void doTreaty();
    void enactPolicy();
    void showScores();
    void showNewGame();
    void setNewGame();
    void doSaveGame();
    void doNextTurn();
    void continueNextTurn();
    void changeSides();
    void doCHumanLoose();
    void doCHumanTough();
    void doAbout();

private:
    void createShapeItem(const QPainterPath &path, const QString &toolTip,
                         const QPoint &pos, const QColor &color);
    int itemAt(const QPoint &pos);
    void loadStaticData();
    QPoint initialItemPosition(const QPainterPath &path);

    //menu actions
    void showNewsWindow(int t);
    void showPolcyWindow(int t);
    void createAdvPanel();
    void unloadAdvPanel();
    void createActions();
    void createMenus();
    void correctMenus();
    void correctCMenus();
    void selectCountryEffect();
    void selectSuperPowerEffect();
    void selectNothingEffect();

    void doCrisis(int WH);
    void HangTough(int subject);
    void HangLoose(int loser, int winner);
    void MinorCrisis(int WH);
    void MinorTough();
    void CmptrCrisis(int WH);
    void Tough();
    void ReactNews();
    QString GenerateReactionHLine(int who, int crisisLevel, bool isMinor, bool isBDown);
    QString GenerateTextStr(int startingAt, int howManyStrings);

    void EndGame();
    void drawScores();
    void drawMapStaticStrings();

    QMenu *gameMenu;
    QMenu *mapModeMenus;
    QMenu *countriesMenu;
    QMenu *relationsMenu;
    QMenu *diplMenu;
    QMenu *milAidMenu;
    QMenu *rebAidMenu;
    QMenu *milIntvMenu;
    QMenu *rebIntvMenu;
    QMenu *makePolicyMenu;
    QMenu *briefingMenu;
    QMenu *eventsMenu;
    QMenu *resourcesMenu;
    QMenu *GDPMenu;
    QMenu *GDPSpndMenu[3];
    QMenu *helpMenu;
    QMenu *contMenu[3];
    QActionGroup *mapGroup;
    QAction *mapModeAct[37];
    QAction *doCloseUp;
    QAction *doHistory;
    QAction *doNews[6];
    QAction *doPolicy[8];
    QAction *doScore;
    QAction *newGameAct;
    QAction *saveGameAct;
    QAction *chgSideAct;
    QAction *nextTurnAct;
    QAction *about;

    QAction *contTitle;

    QList<ShapeItem> shapeItems;
    QPoint previousPosition;
    QPainterPath mypath[80];
    int tmpx[92],tmpy[92];
    int delta;
    QPolygon countryShape[92];
    string compass[92];
    QRect legend[3];
    QPainterPath legendPath[3];
    QLabel *legendLabel[3];
    QLabel *legendCaption;
    QLabel *countryHighlight;
    QLabel *flag[2], *sprLabel[2], *score[2], *holdsMouse[2], *yearLabel, *geoLabel[2];
    QPainterPath scoresPath;

    int mapMode, curAddParam, curIOMode, curSelection;

    int curNews, curPage, curNewsMode, newsCount, listNews[MAXNEWS];

    int QuestQueue[MAXNEWS], questSize, curQuest;
    int BDQVictim[MAXNEWS], BDQVer[MAXNEWS], BDQAct[MAXNEWS], BDQNew[MAXNEWS], numOfBDs;

    int curPolicyMode, oldPlcy;

    Resources resrc;
    Crisis cris;
    Core core;
    CloseUp clsUp;
    History histWind;
    ScoreWindow scrWind;
    NewsWindow nwsWind;
    PolicyWindow plcyWind;
    NGameWindow newGameWindow;
    LostGameWindow LGameWindow;
    QMessageBox aboutBox, saveBox;

};

#endif
