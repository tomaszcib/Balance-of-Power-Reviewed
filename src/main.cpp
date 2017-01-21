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

#include <QtWidgets>
//#include <QtGui>

#include "mainbox.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(bopsource);

    QApplication app(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    MainBox mainBox;
    QFont font;
    /*Uncomment one of these lines. Set the OSX_Flag true while compiling
     * this project on Apple OS X. The program may look uglier and will not
     * work properly without this flag.
     * For Windows and GNU/Linux systems, set OSX_Flag to false.
     */
    //-----------
    //MainBox.OSX_Flag=true;
    mainBox.OSX_Flag=false;
    //-----------
    if(mainBox.OSX_Flag) {
        font.setPixelSize(9);
        app.setFont(font);
    }


    mainBox.show();
    return app.exec();
}
