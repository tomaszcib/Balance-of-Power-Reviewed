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

#ifndef CORE_H
#define CORE_H
#include <QString>
#include <QTextStream>
#include <QDir>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <fstream>
#include "resources.h"
#define N 80
#define MAXNEWS 129
#define USA 0
#define USSR 1
using namespace std;
class QString;
struct nws{
  int type, host, victim, verb, actor, newNVal, oldNVal, worth;
  bool crisisVal;
  QString headLine;
};

struct country {
    string name, adj;
    string capital;

    QString leaderName, oldLeaderName;
    short int leaderTitle;
    short int nameLanguageGroup;

    short int continent;
    bool neighbour[N], minorSph[N];

    //relations to superpower
    int milAid[N], rebAid[N], milIntv[N], rebIntv[N],
    econAid[2];
    short int destabilization[2],pressure[2],treaty[2],finlandization[2], revlGain[2],
    tradePolicy[2], overallRelationship[N];
    int gdp, population, govIdeol, rebIdeol, govStrength, rebStrength,
    govStability, govPopul, troopSize, dontMess, deaths, milPower, rebPower, strengthRatio, sqrStrength, milPress;
    //int finlProb[2];
    int maturity, integrity, prestVal;
    long int gdpSpending[3], gdpFrac[3];
    float draftFraction, conscrFraction;
    double gdpGrowth, popGrowth;
    bool finlFlag, coupFlag, rebWinFlag;
    int govtAidBalance, totalIntv;
    int OMilAid[N], ORebAid[N], OMilIntv[N], ORebIntv[N], ODest[2], OPress[2], OTreat[2], OEcon[2], OTrade[2], OFinProb[2], OGovStrength, ORebStrength, OGovPopul;
    int revGain[2], coupGain[2], finlGain[2];


};

class Core {
public:
    int year;
    long int sumDontMess;
    int level, nastiness, AveDMess;
    int adventur[2], integrity[2], pugnacty[2], govtAidBalance[2];
    short int cmptr, human;
    int MaxCIntv, MaxCAid, USAImpt, USSRImpt;
    int NewsQCtr, LastNews;
    bool CullFlag, TwoPFlag, crisis, ANWFlag, WinFlag;
    country state[80];
    nws news[512];
    int history[9][N][23];
    int historyScore[9][2];
    int score[2];
    int OScore[2];
    int initScore[2];

    QString preDefinedLeaders[N];
    QString name[25];

    void loadLeaders();
    void createNewLeader(int i);
    int loadData();
    int gameInit();
    int RandAdjust(int val, int Max, int min, int bias);
    void CompuAI();
    void MinorAI();
    void countryAI(int i);
    void InsrtNews(int actor, int ver, int victim, int old, int New, int hos, bool cri);

    int IntvConv(int x);
    int MAidConv(int x);
    int EconConv(int x);
    int EconAMax(int x);
    int IntvGMax(int x,int DAij);
    int TreatMax(int x);
    int MaxPolcy(int x);
    int MilMax(int x);
    int Should (int x);
    int RebIMax(int SuprPwr, int MinrPwr);
    int RebAMax(int SuprPwr, int MinrPwr);
    void ChgDipAff(int i, int j, int delta);
    void ChgDMess(int who, int howMuch);
    int Influence(int SuperPower, int Minor);
    void DoPolicy(int victim, int ver, int actor, int New, bool cri);
    int Hurt(int ver, int victim, int old, int New);
    int GImpt(int victim, int ver, int actor, int old, int New, int bias);
    int Impt(int toWhom, int ver, int actor, int old, int New);

    void MinorRej(int j, int i);
    void PrePlanMove();
    int Arf1(int who, int superPower);
    int Arf2(int who, int superPower);
    void Revolution(int i);
    void doFinlandize(int i);

    void SaveHistory();
    void calcScores();

    void MainMove();

    int saveGame();
    int loadGame();

    void clearAllData();

    bool QuitFlag;

    Resources resrc;

private:
    QString generateNewsHeadline(int victim,int ver,int actor,int oldVal,int newVal,int host);

};

#endif // CORE_H
