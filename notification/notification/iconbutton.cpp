/*
 * Copyright (C) 2022 UnionTech Technology Co., Ltd.
 *
 * Author:     yeshanshan <yeshanshan@uniontech.com>
 *
 * Maintainer: yeshanshan <yeshanshan@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "iconbutton.h"

#include "style.h"

DGUI_USE_NAMESPACE

CicleIconButton::CicleIconButton(QWidget *parent)
    : DIconButton(parent)
{
    setEnabledCircle(true);
    updateBackground(UI::Panel::buttonBackground);
}

void CicleIconButton::updateBackground(const QColor &color)
{
    auto pt = palette();
    pt.setBrush(QPalette::Button, color);
    setPalette(pt);
}
