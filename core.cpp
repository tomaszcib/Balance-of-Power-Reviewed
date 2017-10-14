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

#include "core.h"

int Core::IntvConv(int x){
    if(x==0) return 0;
    else if(x==1) return 1;
    else if(x==2) return 5;
    else if(x==3) return 20;
    else if(x==4) return 100;
    else if(x==5) return 500;
}
int Core::MAidConv(int x){
    if(x==0) return 0;
    else if(x==1) return 1;
    else if(x==2) return 5;
    else if(x==3) return 20;
    else if(x==4) return 50;
    else if(x==5) return 100;
}
int Core::EconConv(int x){
    if(x==0) return 0;
    else if(x==1) return 100;
    else if(x==2) return 200;
    else if(x==3) return 500;
    else if(x==4) return 1000;
    else if(x==5) return 2000;
}
int Core::EconAMax(int x){
    if(x<=-60) return 0;
    else if(x>-60&&x<=-40) return 1;
    else if(x>-40&&x<=-20) return 2;
    else if(x>-20&&x<=0) return 3;
    else if(x>0&&x<=20) return 4;
    else return 5;
}
int Core::IntvGMax(int x, int DAij){
    if(level>=3){
        if(x==3) return 2;
        else if(x==4) return 4;
        else if(x==5) return 5;
        else return 0;
    }
    else{
        int q;
        if(DAij>0) q=1;
        if(DAij>20) q=2;
        if(DAij>40) q=3;
        if(DAij>60) q=4;
        if(DAij>80) q=5;
        return q;
    }
}
int Core::TreatMax(int x){
    //x - integrity+diplAff-pugnacity
    int tmax=0;
    if(x<=-60) tmax=0;
    else if(x>-60&&x<=0) tmax=1;
    else if(x>0&&x<=40) tmax=2;
    else if(x>40&&x<=60) tmax=3;
    else if(x>60&&x<=100) tmax=4;
    else tmax=5;
    if(level<3) tmax=5;
    return tmax;
}

int Core::MaxPolcy(int x){
    int sumIntv, sumMilt, men, spnd;
    sumIntv=state[x].totalIntv;
    sumMilt=state[x].govtAidBalance;
    men=state[x].troopSize;
    spnd=state[x].gdpSpending[2];
    MaxCIntv=5; MaxCAid=5;
    for(int i=4;i>=0;i--)
      if(MAidConv(i+1)*20>((spnd/18)+sumMilt)) MaxCAid=i;
    for(int i=4;i>=0;i--)
      if(IntvConv(i+1)>((men/4)-sumIntv)) MaxCIntv=i;

}

int Core::MilMax(int x){
    if(x<=-40) return 0;
    else if(x>-40&&x<=-20) return 1;
    else if(x>-20&&x<=0) return 2;
    else if(x>0&&x<=20) return 3;
    else if(x>20&&x<=40) return 4;
    else return 5;
}

int Core::Should(int x){
    if(x==0) return 0;
    else if(x==1) return 16;
    else if(x==2) return 32;
    else if(x==3) return 64;
    else if(x==4) return 96;
    else if(x==5) return 128;
}
int Core::RebIMax(int SuprPwr, int MinrPwr){
    int y=2; int x;
    if(state[MinrPwr].neighbour[SuprPwr]) y=5;
    else {
        for(int i=2;i<N;i++){
            if(state[MinrPwr].neighbour[i]){
                x=state[i].milIntv[SuprPwr];
                if(x<5) x++;
                if(x>y) y=x;
            }
        }
    }
    return y;
}
int Core::RebAMax(int SuprPwr, int MinrPwr){
    int max=1, x;
    if(state[MinrPwr].neighbour[SuprPwr]) max=5;
    else {
        for(int i=2;i<N;i++){
            if(state[MinrPwr].neighbour[i]){
                x=state[i].milIntv[SuprPwr];
                if(x<5) x++;
                if(x>max) max=x;
            }
        }
    }
    return max;
}
void Core::ChgDipAff(int i, int j, int delta){
    int x;
    x=state[i].overallRelationship[j]+delta;
    if(x>127) x=127;
    else if(x<-127) x=-127;
    state[i].overallRelationship[j]=x;
    state[j].overallRelationship[i]=x;
}

void Core::ChgDMess(int who, int howMuch){
  state[who].dontMess+=howMuch;
  sumDontMess+=howMuch;
  if(sumDontMess<1) sumDontMess=1;
  AveDMess=sumDontMess/N;
}

int Core::Influence(int SuperPower, int Minor){
    int x;
    x=state[Minor].treaty[SuperPower]+state[Minor].econAid[SuperPower]+state[Minor].milAid[SuperPower]+2*state[Minor].milIntv[SuperPower]-2*state[Minor].destabilization[SuperPower]-2*state[Minor].rebAid[SuperPower]-4*state[Minor].rebIntv[SuperPower];
    if(x<0) x=0;
    return x;
}

void Core::DoPolicy(int victim, int ver, int actor, int New, bool cri){
    int oldVal;
    if(ver==0){
        oldVal=state[victim].destabilization[actor];
        state[victim].destabilization[actor]=New;
    }
    else if(ver==1){
        oldVal=state[victim].econAid[actor];
        state[victim].econAid[actor]=New;
    }
    else if(ver==2){
        oldVal=state[victim].milAid[actor];
        state[victim].milAid[actor]=New;
        state[victim].govtAidBalance=state[victim].govtAidBalance-MAidConv(oldVal)+MAidConv(New);
        state[actor].govtAidBalance=state[actor].govtAidBalance+(MAidConv(oldVal)-MAidConv(New))*20;
    }
    else if(ver==3){
        oldVal=state[victim].rebAid[actor];
        state[victim].rebAid[actor]=New;
        state[actor].govtAidBalance=state[actor].govtAidBalance+(MAidConv(oldVal)-MAidConv(New))*20;
    }
    else if(ver==4){
        oldVal=state[victim].milIntv[actor];
        state[victim].milIntv[actor]=New;
        state[actor].totalIntv=state[actor].totalIntv-IntvConv(oldVal)+IntvConv(New);
    }
    else if(ver==5){
        oldVal=state[victim].rebIntv[actor];
        state[victim].rebIntv[actor]=New;
        state[actor].totalIntv=state[actor].totalIntv-IntvConv(oldVal)+IntvConv(New);
    }
    else if(ver==6){
        oldVal=state[victim].pressure[actor];
        state[victim].pressure[actor]=New;
    }
    else if(ver==7){
        oldVal=state[victim].treaty[actor];
        state[victim].treaty[actor]=New;
    }
    else if(ver==8){
        oldVal=state[victim].tradePolicy[actor];
        state[victim].tradePolicy[actor]=New;
        cri=false;
    }
    if(oldVal!=New||victim==human)
      InsrtNews(actor,ver,victim,oldVal,New,victim,cri);
}

int Core::Hurt(int ver, int victim, int old, int New){
  int x;
  if(ver==0) x=16*(New-old);
  else if(ver==1){
    x=-((1024*(EconConv(New)-EconConv(old)))/state[victim].gdp)/(state[victim].govPopul+1);
    if(x==0) x=old-New;
  }
  else if(ver==2){
    x=((old-New)*state[victim].milPress)/4;
    if(x==0) x=old-New;
  }
  else if(ver==3) x=12*(New-old);
  else if(ver==4) {
    x=((old-New)*state[victim].milPress)/2;
    if(x==0) x=old-New;
  }
  else if(ver==5) x=25*(New-old);
  else if(ver==6) x=8*New;
  else if(ver==7) {
    x=((old-New)*state[victim].milPress)/4;
    if(x==0) x=old-New;
  }
  if(x>127) x=127;
  else if(x<-127) x=-127;
  return x;
}

int Core::GImpt(int victim, int ver, int actor, int old, int New, int bias) {
  long long int MLV=134144000;
  int x,y,z,t,v;
  long long int Lx,Ly,Lz;
  for(int i=0;i<2;i++){
    x=state[victim].overallRelationship[i]/4;
    if(x==0) x=1;
    y=(Should(state[victim].treaty[i])/4)+1;
    z=(state[victim].dontMess*1280)/sumDontMess;
    if(z>32) z=32;
    if(z<1) z=1;
    if(i==1) z=33-z;
    t=adventur[i]/2;
    if(t>32) t=32;
    if(t<1) t=1;
    v=Hurt(ver,victim,old,New);
    if(actor==(1-i)&&(ver==2||ver==4||ver==7)&&state[victim].overallRelationship[i]>0) v=-v;
    switch(bias){
      case 0:
        break;
      case 1:
        x=x*sqrt(abs(x)); y=sqrt(y);
        break;
      case 2:
        y=y*sqrt(y);
        z=sqrt(z);
        break;
      case 3:
        z=z*sqrt(z); t=sqrt(t);
        break;
      case 4:
        t=t*sqrt(t);
        if(x>0) x=sqrt(x);
        else x=-sqrt(abs(x));
        break;
    }
    Lx=((z*x*y*t*v)/64)*(state[victim].prestVal);
    if(i==0) Ly=Lx; else Lz=Lx;
    if(Lx>MLV) Lx=MLV;
    if(Lx<-MLV) Lx=-MLV;
    Lx/=4096;
    if(i==0) USAImpt=Lx; else USSRImpt=Lx;
  }
  Lx=Ly+Lz;
  if(Lx>MLV) Lx=MLV;
  if(Lx<-MLV) Lx=-MLV;
  return Lx/4096;
}

int Core::Impt(int toWhom, int ver, int victim, int old, int New){
  int impt=(Hurt(ver,victim,old,New)*state[victim].overallRelationship[toWhom])/128;
  return impt;
}

void Core::InsrtNews(int actor, int ver, int victim, int old, int New, int hos, bool cri){
  int lowI, lowest, import, loclOld;
  QString hline;
  bool loclCri;
  if(victim==actor){
    switch(ver){
      case 0:
    import=5;
    break;
      case 1:
    import=14;
    break;
      case 2:
    import=10;
    break;
      case 3:
    import=2;
    break;
      case 4:
    import=2;
    break;
      case 5:
    import=2;
    break;
      case 6:
    import=2;
    break;
      case 7:
    import=0;
    break;
    }
  }
  else{
    switch(ver){
       case 0:
    import=4;
    break;
      case 1:
    import=3;
    break;
      case 2:
    import=5;
    break;
      case 3:
    import=5;
    break;
      case 4:
    import=10;
    break;
      case 5:
    import=10;
    break;
      case 6:
    if(New>old)import=2; else import=12;
    break;
      case 7:
    import=5;
    break;
      case 8:
    import=2;
    break;
    }
  }
  hline=generateNewsHeadline(victim,ver,actor,old,New,hos);
  import=import*(1+abs(New-old));
  if(old>New) import--;
  if(actor<200) import=sqrt(((sqrt(state[victim].prestVal*state[actor].prestVal))+1)*import);
  if(import<1) import=1;
  CullFlag=false;
  loclOld=old;
  loclCri=cri;
  int j, i=0;
  while(i<NewsQCtr&&!CullFlag){
    if(news[i].victim==victim&&news[i].verb==ver&&news[i].actor==actor){
      loclOld=news[i].oldNVal;
      loclCri=(New<=loclOld);
      j=i;
      while(j<NewsQCtr){
            news[j].victim=news[j+1].victim;
            news[j].verb=news[j+1].verb;
            news[j].actor=news[j+1].actor;
            news[j].oldNVal=news[j+1].oldNVal;
            news[j].newNVal=news[j+1].newNVal;
            news[j].host=news[j+1].host;
            news[j].crisisVal=news[j+1].crisisVal;
            news[j].worth=news[j+1].worth;
            news[j].headLine=news[j+1].headLine;
            j++;
      }
      NewsQCtr--;
      CullFlag=true;
      if(i<LastNews) LastNews--;
    }
    i++;
  }
  if(!CullFlag||(loclOld!=New)){
    lowI=NewsQCtr;
    NewsQCtr++;
    if(NewsQCtr>=MAXNEWS-1) NewsQCtr=MAXNEWS-1;
     lowest=import;
    while(lowI>1&&news[lowI].worth<lowest) lowI--;
     if(lowI>0&&news[lowI].worth<lowest) lowI=0;
     if(lowI<MAXNEWS-1){
       if(lowI<(MAXNEWS-2)&&((lowI+1)<=(NewsQCtr-2))){
            for(int i=NewsQCtr-2;i>=lowI+1;i--){
                news[i+1].victim=news[i].victim;
                news[i+1].verb=news[i].verb;
                news[i+1].actor=news[i].actor;
                news[i+1].oldNVal=news[i].oldNVal;
                news[i+1].newNVal=news[i].newNVal;
                news[i+1].host=news[i].host;
                news[i+1].crisisVal=news[i].crisisVal;
                news[i+1].worth=news[i].worth;
                news[i+1].headLine=news[i].headLine;
            }
       }
       news[lowI+1].victim=victim;
       news[lowI+1].verb=ver;
       news[lowI+1].actor=actor;
       news[lowI+1].oldNVal=loclOld;
       news[lowI+1].newNVal=New;
       news[lowI+1].host=hos;
       news[lowI+1].crisisVal=loclCri;
       news[lowI+1].worth=import;
       news[lowI+1].headLine=hline;
       if(lowI<LastNews) LastNews++;
     }
  }
}


// GAME AI FUNCTIONS
// ---------------------------------------------------------
void Core::MinorRej(int j, int i){
        QTextStream out(stdout);
  int x, val, treatz, milAidz, intvGovtz;
  x=state[i].overallRelationship[j]+2*pugnacty[j];
  val=TreatMax(x+integrity[j]);
  treatz=state[i].treaty[j];
  if(val<treatz){
    if(year>1982) InsrtNews(i,7,j,treatz,val,i,true);
    treatz=val;
  }
  intvGovtz=state[i].milIntv[j];
  val=IntvGMax(treatz,x);
  if(val<intvGovtz){
    state[j].totalIntv=state[j].totalIntv-IntvConv(intvGovtz)+IntvConv(val);
    if(year>1982) InsrtNews(i,4,j,intvGovtz,val,i,true);
    state[i].milIntv[j]=val;
  }
  val=EconAMax(x);
  if(state[i].econAid[j]>val){
    if(year>1982) InsrtNews(i,1,j,state[i].econAid[j],val,i,true);
    state[i].econAid[j]=val;
  }
  milAidz=state[i].milAid[j];
  val=MilMax(x);
  if(val<milAidz){
    state[i].govtAidBalance=state[i].govtAidBalance-MAidConv(milAidz)+MAidConv(val);
    state[j].govtAidBalance=state[j].govtAidBalance+(MAidConv(milAidz)-MAidConv(val))*20;
    if(year>1982) InsrtNews(i,2,j,milAidz,val,i,true);
    state[i].milAid[j]=val;
  }
  state[i].treaty[j]=treatz;
}

void Core::PrePlanMove(){
  long long int temp;
  int x;
  year++;
  for(int i=0;i<N;i++){
        state[i].OGovStrength=state[i].govStrength;
        state[i].ORebStrength=state[i].rebStrength;
        state[i].OGovPopul=state[i].govPopul;
        for(int j=0;j<2;j++){
            state[i].revlGain[j]=0;
            state[i].coupGain[j]=0;
            state[i].finlGain[j]=0;
            state[i].OFinProb[j]=state[i].finlandization[j];
            state[i].OEcon[j]=state[i].econAid[j];
            state[i].ODest[j]=state[i].destabilization[j];
            state[i].OTreat[j]=state[i].treaty[j];
            state[i].OPress[j]=state[i].pressure[j];
        }
        for(int j=0;j<N;j++){
            state[i].OMilAid[j]=state[i].milAid[j];
            state[i].ORebAid[j]=state[i].rebAid[j];
            state[i].OMilIntv[j]=state[i].milIntv[j];
            state[i].ORebIntv[j]=state[i].rebIntv[j];
        }
        if(state[i].govStrength==0) state[i].govStrength=1;
        if(state[i].rebStrength>state[i].govStrength) state[i].rebStrength=state[i].govStrength;
        temp=state[i].rebStrength;
        x=(6400*temp)/state[i].govStrength;
        if(x<1) x=1;
        if(x>6400) x=6400;
        temp=x;
        state[i].sqrStrength=sqrt(temp);
        //check for USA-USSR battles
        if((state[i].milIntv[0]>0&&state[i].rebIntv[1]>0)||(state[i].milIntv[1]>0&&state[i].rebIntv[0]>0)){
            //USA fights with USSR
            state[1].overallRelationship[0]=-127;
            state[0].overallRelationship[1]=-127;
            nastiness=127;
            pugnacty[0]=127; pugnacty[1]=127;
        }
        //check for minor country battles
        if(level==4){
            for(int j=2;j<N;j++){
                if(state[j].milIntv[i]>0){
                    for(int k=0;k<N;k++){
                        if(state[j].rebIntv[k]>0){
                            ChgDipAff(k,i,-nastiness/8);
                            ChgDipAff(i,k,-nastiness/8);
                        }
                    }
                }
            if(state[j].rebIntv[i]>0){
            for(int k=0;k<N;k++){
                if(state[j].milIntv[k]>0){
                    ChgDipAff(k,i,-nastiness/8);
                    ChgDipAff(i,k,-nastiness/8);
                }
            }
          }
       }
    }
  }
}

int Core::Arf1(int who, int superPower){
    int temp1;
    temp1=IntvConv(state[who].milIntv[superPower]);
    return (temp1*state[superPower].milPower)/state[superPower].troopSize;
}
int Core::Arf2(int who, int superPower){
    int temp1;
    temp1=IntvConv(state[who].rebIntv[superPower]);
    return (temp1*state[superPower].milPower)/state[superPower].troopSize;
}
void Core::Revolution(int i){
    createNewLeader(i);
    int x,y,z;
    z=state[i].rebIdeol;
    state[i].rebWinFlag=true;
    int d=state[i].govIdeol;
    state[i].govIdeol=state[i].rebIdeol;
    state[i].rebIdeol=d;
    if(state[i].rebIntv[USA]+state[i].rebIntv[USSR]>0){
        if(state[i].rebIntv[USA]>state[i].rebIntv[USSR])
            state[i].govIdeol=(state[i].govIdeol+state[USA].govIdeol)/2;
        else state[i].govIdeol=(state[i].govIdeol+state[USSR].govIdeol)/2;
    }
    state[i].govPopul=10+(128-abs(state[i].govIdeol))/8;
    state[i].govStrength=state[i].rebStrength;
    state[i].rebStrength=1; state[i].rebPower=1;
    state[i].strengthRatio=state[i].govStrength/state[i].rebStrength;
    InsrtNews(i,1,i,4+(z>=0),0+(z>=0),i,true);
    state[i].govtAidBalance=0;
    for(int j=0;j<N;j++){
        //revolutionary adjustments
        if(j!=i){
            if(j<2){
                x=128-Should(state[i].treaty[j]);
                integrity[j]=integrity[j]*x/128;
                x=state[i].rebIdeol-state[j].govIdeol;
                y=state[i].govIdeol-state[j].govIdeol;
                x=(abs(x)-abs(y))/2;
                x=x+8*(state[i].rebAid[j]+2*state[i].rebIntv[j]-state[i].milAid[j]-2*state[i].milIntv[j]);
                x=x-8*(state[i].rebAid[1-j]+2*state[i].rebIntv[1-j]-state[i].milAid[1-j]-2*state[i].milIntv[1-j]);
                if(x>127) x=127;
                else if(x<-127) x=-127;
                state[i].revlGain[j]=((x-state[i].overallRelationship[j])*state[i].prestVal)/1024;
                state[i].treaty[j]=0;
                state[i].econAid[j]=0;
            }
            else x=8*(state[i].rebAid[j]+2*state[i].rebIntv[j]-state[i].milAid[j]-2*state[i].milIntv[j]);
            if(x>127) x=127;
            else if(x<-127) x=-127;
            state[i].overallRelationship[j]=x;
            state[j].overallRelationship[i]=x;
            x=state[i].milAid[j];
            state[i].milAid[j]=state[i].rebAid[j];
            state[i].rebAid[j]=x;
            x=state[i].milIntv[j];
            state[i].milIntv[j]=state[i].rebIntv[j];
            state[i].rebIntv[j]=x;
            if(j<2)
                for(int k=0;k<5;k++)
                    if(IntvGMax(k,state[i].overallRelationship[j])<state[i].milIntv[j]) state[i].treaty[j]=k+1;
        }
    }
}

void Core::doFinlandize(int i){
    int selfPower[2], projPower[2];
    int y=state[i].milPower-state[i].rebPower;
    int x, temp;
    if(level>=3){
        for(int j=0;j<2;j++){
            x=RebIMax(j,i);
            projPower[j]=(IntvConv(x)*state[j].milPower)/state[j].troopSize;
            x=state[i].treaty[1-j];
            x=(Should(x)*state[1-j].milPower)/128;
            selfPower[j]=y+(x*state[1-j].integrity)/128;
            if(selfPower[j]<1) selfPower[j]=1;
            temp=((adventur[j]-state[i].overallRelationship[j])*projPower[j]*(state[i].pressure[j]+4))/selfPower[j];
            if(temp<0) temp=0;
            if(temp>2048) temp=2048;
            state[i].finlandization[j]=temp/8;

        }
        x=state[i].finlandization[cmptr];
        y=state[i].finlandization[human];
        short int who, notWho;
        if(x>127||y>127) {//then finlandize
            if(x>y){ who=cmptr; notWho=human; }
            else { who=human; notWho=cmptr; }
            state[i].finlFlag=true;
            state[i].govIdeol=state[i].govIdeol+(state[who].govIdeol-state[i].govIdeol)/4;
            if(state[i].govIdeol*state[i].rebIdeol>0){
                state[i].rebIdeol=-state[i].govIdeol;
            }
            state[i].finlGain[who]=(32*state[i].prestVal)/1024;
            state[i].finlGain[notWho]=(-32*state[i].prestVal)/1024;
            ChgDipAff(i,who,32);
            ChgDipAff(i,notWho,-32);
            InsrtNews(i,0,who,0,0,i,true);
            for(int j=0;j<2;j++){
                //recalc
                temp=((adventur[j]-state[i].overallRelationship[j])*projPower[j]*(state[i].pressure[j]+4))/selfPower[j];
                if(temp<0) temp=0; else if (temp>2048) temp=2048;
                state[i].finlandization[j]=temp/16;
            }
        }
    }
}

void Core::countryAI(int i){
    long int temp; int x;
    state[i].finlFlag=0; state[i].coupFlag=0; state[i].rebWinFlag=0;
    x=state[i].troopSize;
    temp=(state[i].gdpSpending[2]+state[i].govtAidBalance)/2;
    if(i==1) temp/=10;
    if(temp<1) temp=1;
    int y=Arf1(i,USA)+Arf1(i,USSR);
    state[i].milPower=((4*temp*x)/(temp+x))+y;
    x=(6400*state[i].rebStrength)/state[i].govStrength;
    if(x<1) x=1;
    else if(x>6400) x=6400;
    temp=x;
    state[i].sqrStrength=sqrt(temp);
    if(i>1&&level==4){
        for(int j=2;j<N;j++){
            //trigger minor country war when bad relationship
            if(state[i].overallRelationship[j]<=-127){
                state[i].milPower-=(state[j].milPower/4);
                state[i].gdp-=(state[j].milPower/4);
                if(state[i].gdp<1) state[i].gdp=1;
                //if the country army is destroyed, it surrender
                if(state[i].milPower<1){
            //cout<<"W";
                    createNewLeader(i);
                    for(int k=0;k<N;k++){
                        //surrendered now views the world as the victorious side
                        if(state[j].overallRelationship[k]<=-127)
                            state[i].overallRelationship[k]=-120;
                        else state[i].overallRelationship[k]=state[j].overallRelationship[k];
                    }
                    state[i].govIdeol=state[j].govIdeol;
                    state[i].rebIdeol=-state[j].govIdeol;
                    InsrtNews(i,6,j,2,1,i,true);
                    state[i].overallRelationship[j]=0;
                    state[j].overallRelationship[i]=0;
            if(i>j){
              CullFlag=false;
              int k=1;
              while(k<=NewsQCtr&&!CullFlag){
                if(news[k].victim==j&&news[k].verb==6&&news[k].actor==i&&news[k].newNVal==1&&news[k].oldNVal==1){
                    for(int d=k;d<NewsQCtr-1;d++){
                        news[d].victim=news[d+1].victim;
                        news[d].verb=news[d+1].verb;
                        news[d].actor=news[d+1].actor;
                        news[d].oldNVal=news[d+1].oldNVal;
                        news[d].newNVal=news[d+1].newNVal;
                        news[d].host=news[d+1].host;
                        news[d].crisisVal=news[d+1].crisisVal;
                        news[d].worth=news[d+1].worth;
                    }
                    NewsQCtr--;
                    CullFlag=true;
                    if(k<LastNews) LastNews--;
                }
                k++;
              }
            }
         }
         else { InsrtNews(i,6,j,1,1,i,true); state[i].overallRelationship[j]=-127;}
        }
      }
    }
    x=(((256-state[i].maturity)*(state[i].population/100)/256)*state[i].sqrStrength/80/*sqrtX*/);
    temp=0;
    for(int j=0;j<N;j++) temp+=(2*MAidConv(state[i].rebAid[j]));
    if(temp<(x/8)+1) temp=(x/8)+1;
    //do rebel wars
    y=Arf2(i,USA)+Arf2(i,USSR);
    state[i].rebPower=((4*temp*x)/(temp+x))+y;
    if(i<2) state[i].rebPower=1;
    state[i].milPower-=(state[i].rebPower/4);
    if(state[i].milPower<1) state[i].milPower=1;
    state[i].rebPower-=(state[i].milPower/4);
    if(state[i].rebPower<1) state[i].rebPower=1;
    state[i].govStrength=state[i].milPower;
    state[i].rebStrength=state[i].rebPower;
    state[i].strengthRatio=state[i].govStrength/state[i].rebStrength;
    if(state[i].rebStrength==1&&state[i].govStrength<8192)
        state[i].strengthRatio*=4;
    //when rebel are victorious, revolution happen
    if(state[i].strengthRatio<1) Revolution(i);

    //economy
    int press[3];
    press[0]=(20-state[i].govPopul)*10;
    if(press[0]<1) press[0]=1;
    press[1]=(80-state[i].gdpFrac[1])*2;
    if(press[1]<1) press[1]=1;
    press[2]=state[i].sqrStrength+state[i].finlandization[USA]+state[i].finlandization[USSR];
    if(press[2]<1) press[2]=1;
    state[i].milPress=press[2];
    int sum=press[0]+press[1]+press[2];
    int pot=0;
    if(state[i].gdpFrac[0]>16) {
        state[i].gdpFrac[0]-=8; pot=8; }
    if(state[i].gdpFrac[1]>16) {
        state[i].gdpFrac[1]-=8; pot+=8; }
    if(state[i].gdpFrac[2]>16) {
        state[i].gdpFrac[2]-=8; pot+=8; }
    state[i].gdpFrac[1]+=((press[1]*pot)/sum);
    state[i].gdpFrac[2]+=((press[2]*pot)/sum);
    state[i].gdpFrac[0]=255-state[i].gdpFrac[2]-state[i].gdpFrac[1];
    long int oldSpend0=(state[i].gdpSpending[0]*255)/state[i].population;
    x=EconConv(state[i].econAid[USA])+EconConv(state[i].econAid[USSR]);
    long int pseudGdp=state[i].gdp+x;
    temp=pseudGdp*2*(state[i].gdpFrac[1]-30);
    //GDP growth calculation
    state[i].gdpGrowth=(double)(state[i].gdp+(temp/1000))/state[i].gdp;
    state[i].gdpGrowth--; state[i].gdpGrowth*=100;
    state[i].gdp+=(temp/1000);
    pseudGdp=state[i].gdp+x;
    //population growth
    x=30-(oldSpend0/40); if(x<1) x=1;
    temp=state[i].population*x;
    if(temp<1000) temp=1000;
    state[i].popGrowth=(double)(state[i].population+(temp/1000))/state[i].population;
    state[i].population+=(temp/1000);
    state[i].gdpSpending[0]=(state[i].gdpFrac[0]*pseudGdp/256);
    state[i].gdpSpending[1]=(state[i].gdpFrac[1]*pseudGdp/256);
    if(state[i].gdpSpending[1]<1) {state[i].gdpSpending[1]=1;}
    state[i].gdpSpending[2]=(pseudGdp-state[i].gdpSpending[0]-state[i].gdpSpending[1])/*10*/;
    if(state[i].gdpSpending[2]<1) state[i].gdpSpending[2]=1;
    //fix negative resource bug
    if(i<2){
        x=(state[i].gdpSpending[2]/18)+govtAidBalance[i];
        while(x<0){
            state[i].gdpFrac[0]--;
            state[i].gdpFrac[2]++;
            state[i].gdpSpending[0]=(state[i].gdpFrac[0]*pseudGdp)/256;
            state[i].gdpSpending[2]=(pseudGdp-state[i].gdpSpending[1]-state[i].gdpSpending[0]);
            x=(state[i].gdpSpending[2]/18)+govtAidBalance[i];
        }
    }
    //calculate govt popularity balance
    temp=(state[i].gdpFrac[0]*pseudGdp)/state[i].population;
    long int delta=((temp-oldSpend0)*100)/(oldSpend0+1);
    temp=delta+(abs(state[i].govIdeol)/64)-3;
    state[i].govPopul+=temp;
    if(state[i].govPopul>20) state[i].govPopul=20;
    if(state[i].govPopul<0) state[i].govPopul=0;
    if(i<2) state[i].govPopul=20;
    if(state[i].govPopul<=state[i].destabilization[USA]+state[i].destabilization[USSR]&&level>1){
       //if low popularity, coup d'etat happens
       state[i].coupFlag=true;
       createNewLeader(i);
       x=state[i].govIdeol;
       state[i].govIdeol=state[i].rebIdeol;
       state[i].rebIdeol=x;
       state[i].govPopul=10+(128-abs(state[i].govIdeol))/8;
       if(state[i].govPopul>20) state[i].govPopul=20;
       if(state[i].govPopul<0) state[i].govPopul=0;
       state[i].govStrength-=(state[i].govStrength/8);
       InsrtNews(i,2,i,0,(state[i].maturity/64)+1,i,true);
       for(int j=0;j<2;j++){
            //do things related to superpowers
            x=Should(state[i].treaty[j])-(state[i].maturity/2);
            if(x>128) x=128;
            else if(x<0) x=0;
            integrity[j]=(integrity[j]*(128-x))/128;
            x=state[i].rebIdeol-state[j].govIdeol;
            y=state[i].govIdeol-state[j].govIdeol;
            x=(abs(x)-abs(y))/2;
            state[i].coupGain[j]=(x*state[i].prestVal)/1024;
            ChgDipAff(i,j,x);
            MinorRej(j,i);
       }
    }

    //foreign policy
    x=(6400*state[i].rebStrength)/state[i].govStrength;
    if(x<1) x=1;
    else if(x>6400) x=6400;
    temp=x;
    state[i].sqrStrength=sqrt(temp);
    if(i>1) doFinlandize(i);
    for(int j=0;j<2;j++) { state[i].pressure[j]=0; state[i].destabilization[j]=0;}
    for(int j=0;j<N;j++) {
        x=RebAMax(j,i);
        y=RebIMax(j,i);
        if(state[i].rebAid[j]>x) state[i].rebAid[j]=x;
        if(state[i].rebIntv[j]>y) state[i].rebIntv[j]=y;
        if(j<2) MinorRej(j,i);
    }
}

void Core::CompuAI(){
  int sum, MaxCEcon,x, y, HFinProb, DAij, obligation, need, Max, oldVal, newVal, projPower;
  MaxPolcy(cmptr);
  sum=0;
  for(int i=2;i<N;i++) sum+=(state[i].econAid[cmptr]);
  MaxCEcon=5;
  y=(state[cmptr].gdp/88)-2*sum;
  for(int i=5;i>=1;i--) if(EconConv(i)>y) MaxCEcon=i-1;
  for(int j=2;j<N;j++){
    HFinProb=state[j].finlandization[human];
    DAij=state[j].overallRelationship[cmptr];
    obligation=DAij+Should(state[j].treaty[cmptr])-state[j].overallRelationship[human];
    if(obligation<0) obligation=(obligation*nastiness)/32;
    if(obligation>128) obligation=128;
    if(obligation==0) obligation=1;
    for (int k=0;k<=7;k++){
      switch(k){
    case 1:
      need=(22-state[j].govPopul)/3;
      if(need<0) need=0;
      Max=EconAMax(DAij);
      if(Max>MaxCEcon) Max=MaxCEcon;
      oldVal=state[j].econAid[cmptr];
      if(level==1) need=0;
      break;
    case 2:
      oldVal=state[j].milAid[cmptr];
      need=(state[j].sqrStrength+HFinProb)/8;
      Max=MilMax(DAij);
      if(Max>MaxCAid) Max=MaxCAid;
      break;
    case 3:
      need=-10;
      oldVal=state[j].rebAid[cmptr];
      Max=RebAMax(cmptr,j);
      if(Max>MaxCAid) Max=MaxCAid;
      x=state[j].strengthRatio;
      y=0;
      if(x<128) y=1;
      if(x<64) y=2;
      if(x<32) y=3;
      if(x<8) y=4;
      if(x<2) y=5;
      if(y<Max) Max=y;
      break;
    case 4:
      oldVal=state[j].milIntv[cmptr];
      Max=IntvGMax(state[j].treaty[cmptr],state[j].overallRelationship[cmptr]);
      need=(state[j].sqrStrength+HFinProb)/8;
      sum=0;
      for(int i=2;i<N;i++){
        if(i!=j&&state[i].neighbour[j]&&!state[i].neighbour[cmptr]&&state[i].overallRelationship[cmptr]<0)
          sum+=(128-state[i].overallRelationship[cmptr]);
      }
      need+=(sum/64);
      if(Max>MaxCIntv) Max=MaxCIntv;
      break;
    case 5:
      oldVal=state[j].rebIntv[cmptr];
      newVal=0;
      Max=5;
      if(DAij<((nastiness/2)-64)){
        Max=RebIMax(cmptr,j);
        projPower=(IntvConv(Max)*state[cmptr].milPower)/state[cmptr].troopSize;
        if(Max>MaxCIntv) Max=MaxCIntv;
        if(projPower>state[j].milPower){
          newVal=Max;
          x=GImpt(j,k,cmptr,oldVal,newVal,0);
          if(x>(rand()%32768)/1024) newVal=oldVal;
        }
      }
      break;
    case 6:
      x=(144-state[j].finlandization[cmptr])/16;
      if(x>5) x=0; if(x<0) x=0;
      need=x;
      Max=5;
      oldVal=0;
      if(level<3) need=0;
      break;
    case 7:
      oldVal=state[j].treaty[cmptr];
      x=1+(HFinProb/16)-(state[j].sqrStrength/24)-((20-state[j].govPopul)/8);
      if(x<0) x=0;
      if(level<3) x=0;
      need=oldVal+x;
      Max=TreatMax(integrity[cmptr]+DAij-pugnacty[cmptr]);
      if(Max<oldVal) Max=oldVal;
      break;
    case 0:
      oldVal=state[j].destabilization[cmptr];
      if(level==4) need=(state[j].govPopul-20)/4;
      else need=(state[j].govPopul-20)/2;  //balancing the game
      if(need>0/*||state[j].govPopul>10*/) need=0;
      Max=5;
      if(level==1) need=0;
      break;
    }
      if(k!=5){
        if(k!=7&&k!=6&&k!=4) need=(need*obligation)/128;
        if(need>Max) need=Max;
        if(need<0) need=0;
        newVal=need;
        if(newVal>oldVal)
        while(GImpt(j,k,cmptr,oldVal,newVal,0)>(abs(rand()%32768)/512)&&newVal>oldVal) newVal--;
      }
      if(newVal<oldVal&&k==7) newVal=oldVal;
      if(newVal!=oldVal){
        DoPolicy(j,k,cmptr,newVal,(newVal<oldVal));
        MaxPolcy(cmptr);
      }
    }
  }
}

void Core::MinorAI(){
    int influe, weight, who, weapons, newWeapons, maxStuff, troops, newTroops;
    int weightArr[N], IDArr[N], temp;
    long long int longSum;
    for(int i=2;i<N;i++){
        influe=Influence(0,i)-Influence(1,i);
        for(int j=2;j<N;j++) {
            if(i!=j&&state[i].minorSph[j]&&state[i].overallRelationship[j]!=127){
                if(state[i].milAid[j]>0) DoPolicy(j,2,i,0,1);
                if(state[i].rebAid[j]>0) DoPolicy(j,3,i,0,1);
                if(state[i].milIntv[j]>0) DoPolicy(j,4,i,0,1);
                if(state[i].rebIntv[j]>0) DoPolicy(j,5,i,0,1);
            }
        }
        int sRat=state[i].strengthRatio;
        for(int j=2;j<N;j++) if(state[i].overallRelationship[j]==-127) sRat=0;
        int resrcFrac=0;
        if(sRat>640&&sRat<=1280) resrcFrac=10;
        else if(sRat>1280&&sRat<=2560) resrcFrac=20;
        else if(sRat>2560&&sRat<=5120) resrcFrac=30;
        else if(sRat>5120) resrcFrac=40;
        if(sRat>0){
            //explore foreign policy options
            resrcFrac+=((adventur[0]+adventur[1]+nastiness)/8);
            for(int j=0;j<N;j++) { weightArr[j]=0; IDArr[j]=0; }
            for(int j=2;j<N;j++){
                if(j!=i&&state[i].minorSph[j]){
                    longSum=0;
                    for(int k=0;k<N;k++) longSum-=(state[j].overallRelationship[k]*state[k].overallRelationship[i]);
                    weight=abs((state[i].overallRelationship[j]*longSum)/16383);
                    int x=state[j].dontMess-AveDMess;
                    weight+=(x*influe);
                    if(weight<0) weight=0;
                    int k=0;
                    while(weight<weightArr[k]) k++;
                    for(int kk=N-2;kk>=k;kk--){
                        weightArr[kk+1]=weightArr[kk];
                        IDArr[kk+1]=IDArr[kk];
                    }
                    weightArr[k]=weight;
                    IDArr[k]=j;
                }
            }
            longSum=0;
            for(int j=0;j<N;j++) longSum+=weightArr[j];
            for(int j=0;j<N-2;j++){
                if(weightArr[j]>0){
                    who=IDArr[j];
                    weapons=((weightArr[j]-1)*resrcFrac*state[i].gdpSpending[2])/(longSum*100);
                    weapons/=10;
                    newWeapons=0;
                    if(weapons>1&&weapons<=5) newWeapons=1;
                    else if(weapons>5&&weapons<=20) newWeapons=2;
                    else if(weapons>20&&weapons<=50) newWeapons=3;
                    else if(weapons>50&&weapons<=100) newWeapons=4;
                    else if(weapons>100) newWeapons=5;
                    maxStuff=0;
                    if(state[who].strengthRatio<256) maxStuff=1;
                    if(state[who].strengthRatio<128) maxStuff=2;
                    if(state[who].strengthRatio<64) maxStuff=3;
                    if(state[who].strengthRatio<16) maxStuff=4;
                    if(state[who].strengthRatio<4) maxStuff=5;
                    troops=((weightArr[j]-1)*resrcFrac*state[i].troopSize)/(longSum*100);
                    newTroops=0;
                    if(troops>1) newTroops=1;
                    if(troops>5) newTroops=2;
                    if(troops>20) newTroops=3;
                    if(troops>50) newTroops=4;
                    if(troops>100) newTroops=5;
                    if(state[i].overallRelationship[who]>0){
                        temp=MilMax(state[i].overallRelationship[who]);
                        if(temp>maxStuff) temp=maxStuff;
                        if(newWeapons>temp) newWeapons=temp;
                        DoPolicy(who,2,i,newWeapons,(newWeapons<state[who].milAid[i]));
                        temp=IntvGMax(5,state[who].overallRelationship[i]);
                        if(temp>maxStuff) temp=maxStuff;
                        if(newTroops>temp) newTroops=temp;
                        DoPolicy(who,4,i,newTroops,(newTroops<state[who].milIntv[i]));
                    }
                    else {
                        temp=RebAMax(i,who);
                        if(temp>maxStuff) temp=maxStuff;
                        if(newWeapons>temp) newWeapons=temp;
                        DoPolicy(who,3,i,newWeapons,(newWeapons<state[who].rebAid[i]));
                        temp=RebIMax(i,who);
                        if(temp>maxStuff) temp=maxStuff;
                        if(newTroops>temp) newTroops=temp;
                        DoPolicy(who,5,i,newTroops,(newTroops<state[who].rebIntv[i]));
                    }
                }
            }
        }
    }
}

int Core::loadData(){
    long int x;
    int tmp[3];
    ifstream readCountry, readRelations, readBorders;
    readCountry.open("countryData1.dat");
    readRelations.open("minorRelations1.dat");
    readBorders.open("borders1.dat");
    for(int i=0;i<N;i++){
      readCountry>>state[i].name>>state[i].nameLanguageGroup>>state[i].leaderTitle;
      readCountry>>state[i].population>>state[i].gdp>>state[i].gdpSpending[2]>>state[i].govIdeol;
      readCountry>>state[i].rebIdeol>>state[i].govStrength>>state[i].rebStrength>>state[i].gdpFrac[1];
      readCountry>>state[i].troopSize>>state[i].dontMess>>state[i].maturity;
      for(int j=0;j<2;j++) {
        readCountry>>state[i].milAid[j]>>state[i].rebAid[j]>>state[i].milIntv[j];
        readCountry>>state[i].rebIntv[j]>>state[i].treaty[j]>>state[i].econAid[j];
        readCountry>>state[i].tradePolicy[j]>>state[i].overallRelationship[j];
        state[j].overallRelationship[i]=state[i].overallRelationship[j];
      }
      state[i].gdpSpending[2]/=5;
      state[i].draftFraction=(state[i].troopSize*255)/state[i].population;
      state[i].gdpFrac[2]=((255*state[i].gdpSpending[2])/*/10*/)/state[i].gdp;
      state[i].gdpFrac[0]=255-state[i].gdpFrac[1]-state[i].gdpFrac[2];
      state[i].govPopul=10+(128-abs(state[i].govIdeol))/8;
      x=(state[i].gdpFrac[0])*state[i].gdp;
      state[i].gdpSpending[0]=(state[i].gdpFrac[0]*state[i].gdp)/256;
      state[i].gdpSpending[1]=(state[i].gdpFrac[1]*state[i].gdp)/256;
      sumDontMess+=state[i].dontMess;
      state[i].finlFlag=0; state[i].coupFlag=0;
      state[i].finlandization[0]=0; state[i].finlandization[1]=0;
      state[i].totalIntv=0;
      if(i>1){
              for(int j=2;j<N;j++){
                  state[i].overallRelationship[j]=((state[i].overallRelationship[USA]*state[j].overallRelationship[USA])/256)+((state[i].overallRelationship[USSR]*state[j].overallRelationship[USSR])/256);
                  state[j].overallRelationship[i]=state[i].overallRelationship[j];
          }
      }
    }
    readRelations>>x;
      for(int j=0;j<x;j++){
        readRelations>>tmp[0]>>tmp[1];
        readRelations>>state[tmp[1]].rebIntv[tmp[0]]
                    >>state[tmp[1]].rebAid[tmp[0]]
                   >>state[tmp[1]].milIntv[tmp[0]]
                  >>state[tmp[1]].milAid[tmp[0]]
                 >>state[tmp[1]].overallRelationship[tmp[0]];
        if(level < 4){
            state[tmp[1]].rebIntv[tmp[0]] = 0;
            state[tmp[1]].rebAid[tmp[0]] = 0;
            state[tmp[1]].milIntv[tmp[0]] = 0;
            state[tmp[1]].milAid[tmp[0]] = 0;
        }
      }
      readBorders>>x;
      for(int j=0;j<x/2;j++){
        readBorders>>tmp[0]>>tmp[1];
        state[tmp[0]].neighbour[tmp[1]]=true;
        state[tmp[1]].neighbour[tmp[0]]=true;
        state[tmp[0]].minorSph[tmp[1]]=true;
        state[tmp[1]].minorSph[tmp[0]]=true;
      }
      readBorders>>x;
      for(int j=0;j<x/2;j++){
        readBorders>>tmp[0]>>tmp[1];
        state[tmp[0]].minorSph[tmp[1]]=true;
      }
    readCountry.close();
    readRelations.close();
    readBorders.close();
    return 0;
  }

int Core::RandAdjust(int val, int Max, int min, int bias){
    int delta=bias>>level;
    if(rand()%2) delta*=-1;
    int x=val+(rand()%32768)/delta;
    if(x>Max) x=Max;
    if(x<min) x=min;
    return x;
}

int Core::gameInit(){
  resrc.setStrings();
  loadLeaders();
  int x,y;
  nastiness=8*level+(rand()%32768)/2048;
  for(int i=0;i<2;i++) pugnacty[i]=32+(4*level)+(rand()%32768)/4096;
  pugnacty[cmptr]+=4*level;
  for(int i=0;i<2;i++){
      initScore[i]=0;
    integrity[i]=128;
    adventur[i]=pugnacty[i]+nastiness-pugnacty[1-i]-state[i].gdpFrac[2]+32;
    if(adventur[i]<16) adventur[i]=16;
  }
  for(int i=0;i<N;i++){
    //randomizing
      state[i].govIdeol=RandAdjust(state[i].govIdeol,127,-127,8192);
      state[i].govStrength=RandAdjust(state[i].govStrength,32768,1,4096);
      state[i].maturity=RandAdjust(state[i].maturity,255,0,8192);
      state[i].govPopul=RandAdjust(state[i].govPopul,20,0,16384);
    //end randomizing
    for(int j=0;j<2;j++){
      state[i].OEcon[j]=state[i].econAid[j];
      state[i].ODest[j]=state[i].destabilization[j];
      state[i].OTreat[j]=state[i].treaty[j];
      state[i].OPress[j]=state[i].pressure[j];
    }
    for(int j=0;j<N;j++){
      x=state[i].milAid[j];
      state[i].govtAidBalance+=MAidConv(x);
      if(j<2)state[j].govtAidBalance-=MAidConv(x)*15;  //kludge to balance the powers, it should be x20 normally
      else state[j].govtAidBalance-=MAidConv(x);       //and to fix bug with units
      x=state[i].rebAid[j];
      if(j<2) state[j].govtAidBalance-=MAidConv(x)*15;  //and here, too
      else state[j].govtAidBalance-=MAidConv(x);
      x=state[i].milIntv[j];
      y=state[i].rebIntv[j];
      state[j].totalIntv+=(IntvConv(x)+IntvConv(y));

      state[i].OMilAid[j]=state[i].milAid[j];
      state[i].ORebAid[j]=state[i].rebAid[j];
      state[i].OMilIntv[j]=state[i].milIntv[j];
      state[i].ORebIntv[j]=state[i].rebIntv[j];
    }
    x=state[i].troopSize;
    int temp=(state[i].gdpSpending[2]+state[i].govtAidBalance)/50;    //div2
    state[i].prestVal=(16*temp*x)/(temp+x);
    AveDMess=sumDontMess/N;
  }
}

void Core::loadLeaders(){
    preDefinedLeaders[0]="Reagan";
    preDefinedLeaders[1]="Andropov";
    preDefinedLeaders[2]="Portillo";
    preDefinedLeaders[3]="Cordova";
    preDefinedLeaders[4]="Ortega";
    preDefinedLeaders[5]="Royo";
    preDefinedLeaders[6]="Castro";
    preDefinedLeaders[7]="Galtieri";
    preDefinedLeaders[8]="Ayala";
    preDefinedLeaders[9]="Terry";
    preDefinedLeaders[10]="Campins";
    preDefinedLeaders[11]="Figueiredo";
    preDefinedLeaders[12]="Pinochet";
    preDefinedLeaders[13]="Trudeau";
    preDefinedLeaders[14]="Karamanlis";
    preDefinedLeaders[15]="Falldin";
    preDefinedLeaders[16]="Thatcher";
    preDefinedLeaders[17]="Mitterand";
    preDefinedLeaders[18]="Calvo-Sotelo";
    preDefinedLeaders[19]="Schmidt";
    preDefinedLeaders[20]="Ceausescu";
    preDefinedLeaders[21]="Spadolini";
    preDefinedLeaders[22]="Honecker";
    preDefinedLeaders[23]="Jaruzelski";
    preDefinedLeaders[24]="Husak";
    preDefinedLeaders[25]="Ribicic";
    preDefinedLeaders[26]="Botha";
    preDefinedLeaders[27]="Mubarak";
    preDefinedLeaders[28]="Burgiba";
    preDefinedLeaders[29]="Hassan";
    preDefinedLeaders[30]="Bendjedid";
    preDefinedLeaders[31]="Gaddafi";
    preDefinedLeaders[32]="Traore";
    preDefinedLeaders[33]="Shagari";
    preDefinedLeaders[34]="Nimeiry";
    preDefinedLeaders[35]="Haile-Mariam";
    preDefinedLeaders[36]="Moi";
    preDefinedLeaders[37]="Sese Seko";
    preDefinedLeaders[38]="Nyerere";
    preDefinedLeaders[39]="Machel";
    preDefinedLeaders[40]="Kaunda";
    preDefinedLeaders[41]="dos Santos";
    preDefinedLeaders[42]="Suzuki";
    preDefinedLeaders[43]="Kim";
    preDefinedLeaders[44]="Chun";
    preDefinedLeaders[45]="Fraser";
    preDefinedLeaders[46]="Deng";
    preDefinedLeaders[47]="Le Duan";
    preDefinedLeaders[48]="Evren";
    preDefinedLeaders[49]="Al-Asad";
    preDefinedLeaders[50]="Begin";
    preDefinedLeaders[51]="Chiang";
    preDefinedLeaders[52]="Hussein";
    preDefinedLeaders[53]="Khalid";
    preDefinedLeaders[54]="Khomeini";
    preDefinedLeaders[55]="Karmal";
    preDefinedLeaders[56]="Zia-ul-Haq";
    preDefinedLeaders[57]="Gandhi";
    preDefinedLeaders[58]="U San Yu";
    preDefinedLeaders[59]="Rama";
    preDefinedLeaders[60]="Soeharto";
    preDefinedLeaders[61]="Marcos";
    preDefinedLeaders[62]="Montt";
    preDefinedLeaders[63]="Duarte";
    preDefinedLeaders[64]="Carazo";
    preDefinedLeaders[65]="Haidalla";
    preDefinedLeaders[66]="Toure";
    preDefinedLeaders[67]="Boigny";
    preDefinedLeaders[68]="Zerbo";
    preDefinedLeaders[69]="Rawlings";
    preDefinedLeaders[70]="Kountche";
    preDefinedLeaders[71]="Oueddei";
    preDefinedLeaders[72]="Ahidjo";
    preDefinedLeaders[73]="Kolingba";
    preDefinedLeaders[74]="Sassou-Nguesso";
    preDefinedLeaders[75]="Banana";
    preDefinedLeaders[76]="Masire";
    preDefinedLeaders[77]="Hussein";
    preDefinedLeaders[78]="Sarkis";
    preDefinedLeaders[79]="Torrelio";
    for(int i=0;i<N;i++) { state[i].leaderName=preDefinedLeaders[i]; state[i].oldLeaderName=preDefinedLeaders[i]; }

    name[0]="Aboah*Abu'd*Aduba*Aggrey*Agrinya*Agyare*Agyei*Amankona*Amissah*Arjwana*Asante*Azebry*Baharia*Barry*Bayu*Boakye*Bolaji*Buys*Chiroto*Chiweshe*Dangarembga*Deresse*Dorkenoo*Dube*Dwamena*Ejiofor*Freddy*Gyasi*Hatendi*Ikande*Iwuchukwu*Jalloh*Jamoko*Joof*Kalende*Kazah*Kombayi*Konkwo*Kyagumbo*Kyekyeku*Levas*Lumumba*Luter*Mahalah*Majange*Malindi*Mamer*Mangle*Manyasha*Maree*Mathema*Mawere*Mbangwa*Melgiste*Mengiste*Messi*Mombeshora*Moyo*Mudzuri*Mushohwe*Mutema*Muzorewa*Mwaruwari*Mweushi*Nengomasha*Ntsimango*Oderasak*Odige*Odoemene*Ogyampah*Okafor*Okeke*Okwabi*Popoola*Sakyi*Sarpei*Sesay*Siaw*Sika*Siriboe*Sow*Takyi*Tweneboa*Theron";
    name[1]="Abdullah*Abujamal*Ahmad*Ajam*Adib*Ahad*Al-Ahdal*Akif*Badat*Bakir*Bahri*Bashir*Boustani*Boutros*Hawi*Hatem*Hassan*Al-Hasami*Al-Hosam*Hussein*Iqbal*Ismat*Issawi*Jabir*Al-Jabri*Jameel*Kaddouri*Kadir*Karawi*Karim*Kashif*Kassab*Kazmi*Khalid*Khalef*Nasar*Naseer*Nasiri*Nasri*Nawar*Nawaz*Nazif*Omar*Al-Omari*Qarni*Qaderi*Qasim*Rafiq*Al-Razi*Ramzi*Sa'id*Sadir*Saatchi*Sabri*Sajjad*Samiya*Shawki*Shukri*As-Suwaidi*Tantawi*Tariq*Al-Tusi*Wahed*Wahid*Yasin*Yasser*Zaid";
    name[2]="Ashin*Binnya*Daw*Duwa*Khun*Ko*Ma*Mahn*Mai*Mi*Min*Nai*Gyi*Sawbwa*Saya*Sao*Thakin";
    name[3]="Li*Zhang*Liu*Chen*Yang*Huang*Zhao*Wu*Zhou*Xu*Xi*Hu*Sun*Ma*Zhu*Guo";
    name[4]="Novak*Novotny*Svoboda*Dvorak*Cerny*Prochazka*Jelinek*Hajek*Zeman*Fiala*Kral*Benes*Kucera";
    name[5]="Betteridge*Black*Cable*Chell*Clarke*Clausen*Fidler*Gregory*Harris*Henderson*Johnson*White*Jones*Lawrence*Moore*Patel*Palmer*Smith*Terry*Turner*Vance*Philips*Watson*Walker*Williams*Willis*Webb";
    name[6]="Martin*Bernard*Dubois*Durand*Leroy*Laurent*Lefebvre*Roux*Fournier*Girard*Mercier*Dupont*Lambert*Martinez*Chevalier*Masson*Denis*Boyer*Leclerc*Fabre";
    name[7]="Muller*Fischer*Weber*Wagner*Becker*Schulz*Hoffmann*Schafer*Bauer*Wolf*Schroeder*Zimmermann*Braun*Kruger*Lange*Werner*Jager*Stein*Schreiber*Kuhn*Ziegler";
    name[8]="Colonomos*Demetriou*Floros*Ioannidis*Katsaros*Kokinos*Tsipras*Metaxas*Michelakakis*Pachis*Papadopoulos*Stavros*Spiros";
    name[9]="Kumar*Lal*Sharma*Shan*Jai*Aggarwal*Chande*Rai*Anand*Bhad*Khan*Kapoor*Arun*Madan*Srini*Prasad*Subramani*Sethi*Vijaya*Malik*Mittal*Kishore*Chaudhary";
    name[10]="Rossi*Ferrari*Esposito*Bianchi*Ricci*Marino*Greco*Bruno*Gallo*Conti*Mancini*Costa*Rizzo*Moretti*Lombardi";
    name[11]="Adi*Bethari*Buana*Bulan*Cahaya*Darma*Guntur*Indah*Intan*Kusuma*Nirmala*Purnama*Raharjo*Sukarno*Surya*Wahyu*Wibawa";
    name[12]="Sato*Suzuki*Takahashi*Tanaka*Watanabe*Yamamoto*Nakamura*Kobayashi*Yoshida*Sasaki*Saito*Matsumoto*Shimizu*Ishikawa*Fujita*Okada*Hasegawa";
    name[13]="Cohen*Levy*Mizrahi*Peretz*Biton*Dahan*Avraham*Friedman*Agbaria*Malka*Jabarin*Katz*Saadon*Masalha*Salem";
    name[14]="Kim*Yi*Ri*Pak*Jeong*Gang*Jang*Sin*Han*Seo*Jeon*Bae*Baek*Heo*Sim*Ju*Seong*Cha*Jin*Min";
    name[15]="Ahadi*Akbari*Asadi*Ebrahimi*Fanaei*Ghasemi*Hamadani*Majidi*Mokri*Norouzi*Pahlavi*Pejman*Qazwini*Salehi";
    name[16]="Jakierek*Nowak*Kowalski*Wisniewski*Kowalczyk*Kaminski*Lewandowski*Zielinski*Szymanski*Dabrowski*Jankowski*Mazur*Wojciechowski*Kaczmarek*Wieczorek";
    name[17]="Santos*Sousa*Oliveira*Pereira*Lima*Ferreira*Almeida*Costa*Martins*Araujo*Ribeiro*Rocha*Dias*Teixeira*Azevedo*Montes*Morais";
    name[18]="Popescu*Dumitru*Stoica*Gheorghe*Matei*Ciobanu*Iliescu*Dobre*Barbu*Stefan*Florea*Vasile*Ghita*Georgescu";
    name[19]="Garcia*Fernandez*Gonzales*Rodriguez*Lopez*Diaz*Martinez*Sanchez*Perez*Gomez*Ruiz*Hernandez*Jimenez*Alvarez*Moreno*Alonso*Romero*Navarro*Torres*Dominigueq*Gil*Vazquez*Serrano*Ramos*Sanz*Suarez*Ortega*Rubio*Molina*Delgado*Ramirez*Moralez*Ortiz*Marin*Iglesias*Munoz*Villa*Galleti";
    name[20]="Johansson*Andersson*Karlsson*Nilsson*Eriksson*Olsson*Persson*Gustafsson*Jonsson*Hanson*Jonsson*Carlsson*Lindberg";
    name[21]="Ploy*May*Nan*Aom*Kanokwan*Natcha*Sudarat*Sarawut*Nattapong*Gan*New*Sirichai*Teerapat*Werawat*Anurat*Kittinan*Peerapat*Nutcha*Kwan";
    name[22]="Yilmaz*Kaya*Demir*Sahin*Celik*Yildiz*Ozturk*Aydin*Ozdemir*Arslan*Dogan*Kilic*Aslan*Cetin*Kara*Koc*Kurt*Ozkan*Simisek";
    name[23]="Nguyen*Tran*Le*Pham*Phan*Vu*Dang*Bui*Do*Ho*Ngo*Duong*Ly";
    name[24]="Petrovic*Jovanovic*Popovic*Lukic*Zivkovic*Vukovic*Maric*Durovic*Stvanovic*Jelic*Bozovic*Maric";
}

void Core::createNewLeader(int i){
    QTextStream out(stdout);
    int x=state[i].nameLanguageGroup;
    int j,count=0,pos; QString temp;
    for(j=0;j<name[x].size();j++) if(name[x][j]=='*') count++;
    j=0, pos=0;
    out<<count<<" ";
    count=rand()%count;
    while(j<count){
        if(name[x][pos]=='*') j++;
        pos++;
    }
    while(name[x][pos]!='*'&&pos<name[x].size()){
        temp.append(name[x][pos]);
        pos++;
    }
    state[i].oldLeaderName=state[i].leaderName;
    state[i].leaderName=temp;
}

void Core::calcScores(){
    long int sum[2];
    sum[0]=0; sum[1]=0;
    for(int i=2;i<N;i++){
        sum[0]=sum[0]+(state[i].overallRelationship[0]*state[i].prestVal);
        sum[1]=sum[1]+(state[i].overallRelationship[1]*state[i].prestVal);
    }
    score[0]=sum[0]/1024;
    score[1]=sum[1]/1024;
}

void Core::SaveHistory(){
    int x=year-1982;
    for(int i=0;i<N;i++){
        history[x][i][0]=state[i].sqrStrength;
        history[x][i][1]=state[i].milAid[0];
        history[x][i][2]=state[i].milAid[1];
        history[x][i][3]=state[i].rebAid[0];
        history[x][i][4]=state[i].rebAid[1];
        history[x][i][5]=state[i].milIntv[0];
        history[x][i][6]=state[i].milIntv[1];
        history[x][i][7]=state[i].rebIntv[0];
        history[x][i][8]=state[i].rebIntv[1];
        history[x][i][9]=state[i].overallRelationship[0];
        history[x][i][10]=state[i].overallRelationship[1];
        history[x][i][11]=state[i].milPress;
        history[x][i][12]=state[i].govPopul;
        history[x][i][13]=state[i].econAid[0];
        history[x][i][14]=state[i].econAid[1];
        history[x][i][15]=state[i].destabilization[0];
        history[x][i][16]=state[i].destabilization[1];
        history[x][i][17]=state[i].finlandization[0];
        history[x][i][18]=state[i].finlandization[1];
        history[x][i][19]=state[i].treaty[0];
        history[x][i][20]=state[i].treaty[1];
        history[x][i][21]=state[i].pressure[0];
        history[x][i][22]=state[i].pressure[1];

        history[x][i][23]=state[i].gdp;
        history[x][i][24]=state[i].gdpSpending[0];
        history[x][i][25]=state[i].gdpSpending[1];
        history[x][i][26]=state[i].gdpSpending[2];
        history[x][i][27]=state[i].gdpFrac[0];
        history[x][i][28]=state[i].gdpFrac[1];
        history[x][i][29]=state[i].gdpFrac[2];
        history[x][i][30]=state[i].population;
    }
}

QString Core::generateNewsHeadline(int victim,int ver,int actor,int oldVal,int newVal,int host){
    QString string;
    int startingAt,howManyStrings,skip,count,pos;

    if(actor==host){
        if(ver==1&&victim==actor) { startingAt=0; howManyStrings=3; }
        else if(ver==0&&victim<2) { startingAt=3; howManyStrings=4; }
        else if(ver==2&&victim==actor) { startingAt=13; howManyStrings=3; }
        else if(ver==6&&oldVal==2) { startingAt=7; howManyStrings=3; }
        else if(ver==6&&oldVal==1) { startingAt=10; howManyStrings=3; }
        else if(ver==1&&victim<2){ startingAt=26; howManyStrings=3; }
        else if(ver==2&&victim<2){ startingAt=36; howManyStrings=4; }
        else if(ver==4&&victim<2){ startingAt=55; howManyStrings=3; }
        else if(ver==7&&victim<2){ startingAt=77; howManyStrings=4; }
    }
    else {
        if(newVal>oldVal){
            if(ver==0) { startingAt=16; howManyStrings=3; }
            if(ver==1) { startingAt=19; howManyStrings=3; }
            if(ver==2) { startingAt=29; howManyStrings=4; }
            if(ver==3) { startingAt=40; howManyStrings=4; }
            if(ver==4) { startingAt=48; howManyStrings=4; }
            if(ver==5) { startingAt=58; howManyStrings=4; }
            if(ver==6) { startingAt=66; howManyStrings=3; }
            if(ver==7) { startingAt=69; howManyStrings=4; }
        }
        else {
            if(ver==0) { startingAt=81; howManyStrings=3; }
            if(ver==1) { startingAt=22; howManyStrings=4; }
            if(ver==2) { startingAt=33; howManyStrings=3; }
            if(ver==3) { startingAt=44; howManyStrings=4; }
            if(ver==4) { startingAt=52; howManyStrings=3; }
            if(ver==5) { startingAt=62; howManyStrings=4; }
            if(ver==6) { startingAt=84; howManyStrings=2; }
            if(ver==7) { startingAt=73; howManyStrings=4; }
        }
    }

    for(int i=0+startingAt;i<howManyStrings+startingAt;i++){
        if(resrc.evnt[i][0]=='0') skip=rand()%4;
        else if(resrc.evnt[i][0]=='1') skip=newVal;
        else if(resrc.evnt[i][0]=='4') skip=oldVal;
        count=0; pos=2;
        while(count<skip&&pos<resrc.evnt[i].size()){
            if(resrc.evnt[i][pos]=='*') count++;
            pos++;
        }
        while(resrc.evnt[i][pos]!='*'&&pos<resrc.evnt[i].size()){
            if(resrc.evnt[i][pos]=='_') string.append(resrc.strg[154+victim]);
            else if(resrc.evnt[i][pos]=='=') string.append(resrc.strg[234+victim]);
            else if(resrc.evnt[i][pos]=='&') string.append(resrc.strg[540+state[victim].leaderTitle]);
            else if(resrc.evnt[i][pos]=='{') string.append(state[victim].leaderName);
            else if(resrc.evnt[i][pos]=='[') string.append(state[victim].oldLeaderName);
            else if(resrc.evnt[i][pos]=='%') {
                if(actor==host&&ver==1) string.append(resrc.rebels[newVal][victim]);
                else string.append(resrc.rebels[state[host].rebIdeol>=0][victim]);
            }
            else if(resrc.evnt[i][pos]=='@') string.append(resrc.strg[314+victim]);

            else if(resrc.evnt[i][pos]=='>') string.append(resrc.strg[234+actor]);
            else if(resrc.evnt[i][pos]=='+') string.append(resrc.strg[540+state[actor].leaderTitle]);
            else if(resrc.evnt[i][pos]=='}') string.append(state[actor].leaderName);
            else if(resrc.evnt[i][pos]==']') string.append(state[actor].oldLeaderName);
            else if(resrc.evnt[i][pos]=='#') string.append(resrc.rebels[state[actor].rebIdeol>=0][actor]);
            else if(resrc.evnt[i][pos]=='^') string.append(resrc.strg[314+actor]);
            else if(resrc.evnt[i][pos]=='!') string.append(resrc.strg[154+actor]);
            else string.append(resrc.evnt[i][pos]);
            pos++;
        }
    }
    return string;
}


void Core::MainMove(){
    NewsQCtr=0;
    for(int i=0;i<N;i++) countryAI(i);
    if(!TwoPFlag) CompuAI();
    if(level==4) MinorAI();
    nastiness-=4;
    if(nastiness<0) nastiness=0;
    for(int i=0;i<2;i++){
        pugnacty[i]-=4;
        adventur[i]=pugnacty[i]+nastiness-pugnacty[1-i]-state[i].gdpFrac[2]+32;
        if(adventur[i]<1) adventur[i]=1;
        integrity[i]+=5;
        if(integrity[i]>127) integrity[i]=127;
    }
    calcScores();
    if(year==1982){
        initScore[0]=score[0];
        initScore[1]=score[1];
        for(int i=0;i<N;i++){
            state[i].OGovStrength=state[i].govStrength;
            state[i].ORebStrength=state[i].rebStrength;
            state[i].OGovPopul=state[i].govPopul;
            state[i].OFinProb[0]=state[i].OFinProb[0];
            state[i].OFinProb[1]=state[i].OFinProb[1];
        }
    }
    for(int i=0;i<2;i++) {
        OScore[i]=score[i];
        historyScore[year-1982][i]=score[i]-initScore[i];
    }
    SaveHistory();
}

int Core::saveGame(){
    ofstream save;
    QByteArray buffer;
    char *bufSav;
    int size;

    save.open("SaveGame.dat",std::ofstream::out|std::ofstream::trunc);

    save<<TwoPFlag<<" "<<level<<" "<<human<<" "<<cmptr<<" "<<year<<" "<<sumDontMess<<" "<<nastiness
       <<" "<<AveDMess<<" "<<MaxCIntv<<" "<<MaxCAid<<" "<<USAImpt<<" "<<USSRImpt<<" "
      <<CullFlag<<" "<<crisis<<" "<<ANWFlag<<" "<<NewsQCtr<<" ";
    for(int i=0;i<129;i++){
        save<<news[i].type<<" "<<news[i].host<<" "<<news[i].victim<<" "<<news[i].verb<<
              " "<<news[i].actor<<" "<<news[i].newNVal<<" "<<news[i].oldNVal<<" "<<news[i].worth
           <<" "<<news[i].crisisVal<<" ";
    }
    for(int i=0;i<2;i++){
        save<<adventur[i]<<" "<<integrity[i]<<" "<<pugnacty[i]<<" "<<govtAidBalance[i]<<" "<<
              score[i]<<" "<<OScore[i]<<" "<<initScore[i]<<" ";
    }
    for(int i=0;i<N;i++){
        save<<state[i].leaderTitle<<" "<<state[i].nameLanguageGroup<<" "<<state[i].gdp<<" "
           <<state[i].population<<" "<<state[i].govIdeol<<" "<<state[i].rebIdeol<<" "<<state[i].govStrength<<" "
          <<state[i].rebStrength<<" "<<state[i].govStability<<" "<<state[i].govPopul<<" "<<state[i].troopSize<<" "
         <<state[i].dontMess<<" "<<state[i].deaths<<" "<<state[i].milPower<<" "<<state[i].rebPower<<" "<<state[i].strengthRatio<<" "
        <<state[i].sqrStrength<<" "<<state[i].milPress<<" "<<state[i].maturity<<" "<<state[i].prestVal<<" "
        <<state[i].draftFraction<<" "<<state[i].finlFlag<<" "<<state[i].coupFlag<<" "<<state[i].rebWinFlag<<" "<<state[i].govtAidBalance<<" "
        <<state[i].totalIntv<<" "<<state[i].OGovStrength<<" "<<state[i].ORebStrength<<" "<<state[i].OGovPopul<<" ";
        for(int j=0;j<2;j++){
            save<<state[i].econAid[j]<<" "<<state[i].destabilization[j]<<" "<<state[i].pressure[j]<<" "<<state[i].treaty[j]<<" "<<state[i].finlandization[j]<<" "
               <<" "<<state[i].ODest[j]<<" "<<state[i].OPress[j]<<" "<<state[i].OTreat[j]<<" "<<state[i].OFinProb[j]<<" "
              <<state[i].revlGain[j]<<" "<<state[i].coupGain[j]<<" "<<state[i].finlGain[j]<<" ";
        }
        for(int j=0;j<N;j++){
            save<<state[i].overallRelationship[j]<<" "<<state[i].milAid[j]<<" "<<state[i].rebAid[j]<<" "<<state[i].milIntv[j]<<" "<<state[i].rebIntv[j]<<" "
               <<state[i].OMilAid[j]<<" "<<state[i].ORebAid[j]<<" "<<state[i].OMilIntv[j]<<" "<<state[i].ORebIntv[j]<<" "<<state[i].neighbour[j]<<" "<<state[i].minorSph[j]<<" ";
        }
        for(int j=0;j<3;j++){
            save<<state[i].gdpSpending[j]<<" "<<state[i].gdpFrac[j]<<" ";
        }
    }
    for(int i=0;i<8;i++){
        for(int j=0;j<80;j++){
            for(int k=0;k<31;k++)
                save<<history[i][j][k]<<" ";
        }
    }
    for(int i=0;i<8;i++)
        for(int j=0;j<2;j++)
            save<<historyScore[i][j]<<" ";

    for(int i=0;i<N;i++){
        buffer=state[i].leaderName.toLatin1();
        bufSav=buffer.data();
        size=buffer.size();
        for(int j=0;j<size;j++) if(bufSav[j]==' ') bufSav[j]='_';
        save<<bufSav<<endl;
        buffer=state[i].oldLeaderName.toLatin1();
        bufSav=buffer.data();
        size=buffer.size();
        for(int j=0;j<size;j++) if(bufSav[j]==' ') bufSav[j]='_';
        save<<bufSav<<endl;
    }
    save.close();
    return 0;
}

int Core::loadGame(){

    clearAllData();
    level=4;
    loadData();

    ifstream load;

    load.open("SaveGame.dat");
    QTextStream out(stdout);

    load>>TwoPFlag>>level>>human>>cmptr>>year>>sumDontMess>>nastiness
       >>AveDMess>>MaxCIntv>>MaxCAid>>USAImpt>>USSRImpt
      >>CullFlag>>crisis>>ANWFlag>>NewsQCtr;
    for(int i=0;i<129;i++){
        load>>news[i].type>>news[i].host>>news[i].victim>>news[i].verb>>
                news[i].actor>>news[i].newNVal>>news[i].oldNVal>>news[i].worth
           >>news[i].crisisVal;
    }
    for(int i=0;i<2;i++){
        load>>adventur[i]>>integrity[i]>>pugnacty[i]>>govtAidBalance[i]>>
              score[i]>>OScore[i]>>initScore[i];
    }
    for(int i=0;i<N;i++){
        load>>state[i].leaderTitle>>state[i].nameLanguageGroup>>state[i].gdp
           >>state[i].population>>state[i].govIdeol>>state[i].rebIdeol>>state[i].govStrength
          >>state[i].rebStrength>>state[i].govStability>>state[i].govPopul>>state[i].troopSize
         >>state[i].dontMess>>state[i].deaths>>state[i].milPower>>state[i].rebPower>>state[i].strengthRatio
        >>state[i].sqrStrength>>state[i].milPress>>state[i].maturity>>state[i].prestVal
        >>state[i].draftFraction>>state[i].finlFlag>>state[i].coupFlag>>state[i].rebWinFlag>>state[i].govtAidBalance
        >>state[i].totalIntv>>state[i].OGovStrength>>state[i].ORebStrength>>state[i].OGovPopul;
        for(int j=0;j<2;j++){
            load>>state[i].econAid[j]>>state[i].destabilization[j]>>state[i].pressure[j]>>state[i].treaty[j]>>state[i].finlandization[j]
               >>state[i].ODest[j]>>state[i].OPress[j]>>state[i].OTreat[j]>>state[i].OFinProb[j]
              >>state[i].revlGain[j]>>state[i].coupGain[j]>>state[i].finlGain[j];
        }
        for(int j=0;j<N;j++){
            load>>state[i].overallRelationship[j]>>state[i].milAid[j]>>state[i].rebAid[j]>>state[i].milIntv[j]>>state[i].rebIntv[j]
               >>state[i].OMilAid[j]>>state[i].ORebAid[j]>>state[i].OMilIntv[j]>>state[i].ORebIntv[j]>>state[i].neighbour[j]>>state[i].minorSph[j];
        }
        for(int j=0;j<3;j++){
            load>>state[i].gdpSpending[j]>>state[i].gdpFrac[j];
        }
    }
    for(int i=0;i<8;i++){
        for(int j=0;j<80;j++){
            for(int k=0;k<31;k++)
                load>>history[i][j][k];
        }
    }
    for(int i=0;i<8;i++)
        for(int j=0;j<2;j++)
            load>>historyScore[i][j];
    string temp;
    for(int i=0;i<N;i++){
        getline(load, temp);
        state[i].leaderName=QString::fromStdString(temp);
        getline(load, temp);
        state[i].oldLeaderName=QString::fromStdString(temp);
    }
    for(int i=0;i<129;i++)
        news[i].headLine=generateNewsHeadline(news[i].victim,news[i].verb,news[i].actor,news[i].oldNVal,news[i].newNVal,news[i].host);
    load.close();
    return 0;
}

void Core::clearAllData(){
    sumDontMess=0;
    AveDMess=0;
    NewsQCtr=0;
    for(int i=0;i<MAXNEWS;i++){
        news[i].actor=0;
        news[i].verb=0;
        news[i].victim=0;
        news[i].crisisVal=0;
        news[i].headLine="";
        news[i].newNVal=0;
        news[i].oldNVal=0;
        news[i].worth=0;
        news[i].host=0;
    }
    for(int i=0;i<N;i++){
        state[i].totalIntv=0;
        state[i].govtAidBalance=0;
    }
    for(int i=0;i<9;i++){
       for(int j=0;j<N;j++)
           for(int k=0;k<31;k++)
               history[i][j][k]=0;
       historyScore[i][0] = 0;
       historyScore[i][1] = 0;
    }
    ANWFlag=0, crisis=0, QuitFlag=0, WinFlag=0;
}
