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
#include "shapeitem.h"

QPainterPath ShapeItem::path() const{
    return myPath;
}

QPoint ShapeItem::position() const{
    return myPosition;
}

QColor ShapeItem::color() const{
    return myColor;
}

QString ShapeItem::toolTip() const{
    return myToolTip;
}

void ShapeItem::setPath(const QPainterPath &path){
    myPath = path;
}

void ShapeItem::setToolTip(const QString &toolTip){
    myToolTip = toolTip;
}

void ShapeItem::setPosition(const QPoint &position){
    myPosition = position;
}

void ShapeItem::setColor(const QColor &color){
    myColor = color;
}
