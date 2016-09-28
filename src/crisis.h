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

#ifndef CRISIS_H
#define CRISIS_H

class Crisis {
public:
    long long int sumLoser, sumWinner;
    int whichHead,crisisLevel,base,savHuman,HLoss,CGain,t,x,y,z,H,DAow,DAol,Usex,Usez,rand1,rand2,victim,who,temp;
    bool backDown,aggrFlag,isBegun;
    void resetCrisData();
};

#endif // CRISIS_H
