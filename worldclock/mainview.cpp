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

#include "mainview.h"

#include "clockpanel.h"
#include "settingsview.h"
#include "timezonemodel.h"

namespace dwclock {
ViewManager::ViewManager(QObject *parent)
    : QObject (parent)
    , m_model(new TimezoneModel())
{
}

ViewManager::~ViewManager()
{
    m_model->deleteLater();
    m_model = nullptr;
}

ClockPanel *ViewManager::clockPanel() const
{
    if (!m_clockPanel) {
        m_clockPanel = new ClockPanel();
        m_clockPanel->view()->setModel(m_model);
    }
    return m_clockPanel;
}

SettingsView *ViewManager::settingsView() const
{
    if (!m_settingsView) {
        TimezoneModel *m = new TimezoneModel();
        m->appendItems(m_model->timezones());
        m_settingsView = new SettingsView(m, m_clockPanel);
        m->setParent(m_settingsView);
    }
    return m_settingsView;
}

TimezoneModel *ViewManager::model() const
{
    return m_model;
}

void ViewManager::updateModel(const QStringList &timezones)
{
    m_model->updateModel(timezones);
}
}
