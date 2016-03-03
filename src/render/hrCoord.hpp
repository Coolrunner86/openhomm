// openhomm - open source clone of Heroes of Might and Magic III
// Copyright (C) 2009-2010 openhomm developers team (see AUTHORS)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#pragma once

class QPoint;
class QRect;
class QSize;

namespace coord
{
    const int dim = 32;
    inline int toPix(int x)
    {
        return x * dim;
    }
    inline int toCell(int x)
    {
        return x / dim;
    }
    inline QPoint toPix(const QPoint &p)
    {
        return QPoint(toPix(p.x()), toPix(p.y()));
    }
    inline QPoint toCell(const QPoint &p)
    {
        return QPoint(toCell(p.x()), toCell(p.y()));
    }
    inline QSize toCell(const QSize &s)
    {
        return QSize(toCell(s.width()), toCell(s.height()));
    }
    inline QRect toPix(const QRect &r)
    {
        return QRect(toPix(r.x()), toPix(r.y()), toPix(r.width()), toPix(r.height()));
    }
    inline QRect toCell(const QRect &r)
    {
        return QRect(toCell(r.x()), toCell(r.y()), toCell(r.width()), toCell(r.height()));
    }
}
