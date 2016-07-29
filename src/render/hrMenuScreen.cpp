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
#include "precompiled.hpp"

#include "hrMenuScreen.hpp"

void hrMenuScreen::setViewport(int width, int height)
{
    size.setRect(0, 0, width, height);
}

void hrMenuScreen::collect()
{
    clearItems();
    loadScreen.rect.moveCenter(size.center());
    addItem(loadScreen);
}

void hrMenuScreen::onMouseEvent(const QPointF &pos)
{
    Q_UNUSED(pos);
}

void hrMenuScreen::onMouseLeave()
{
}

void hrMenuScreen::showLoadScreen()
{
    hrCache &cache = hrCache::getInstance();
    loadScreen = cache.loadItem("loadbar.pcx");
    emit sceneChanged();
}
