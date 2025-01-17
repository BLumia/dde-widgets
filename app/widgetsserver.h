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

#pragma once

#include "global.h"
#include <QObject>
#include <QEvent>

WIDGETS_FRAME_BEGIN_NAMESPACE
class WidgetManager;
class MainView;
WIDGETS_FRAME_END_NAMESPACE
class WidgetsServer : public QObject {
    Q_OBJECT
public:
    explicit WidgetsServer(QObject *parent = nullptr);
    virtual ~WidgetsServer() override;

    bool registerService();

    void start();

public Q_SLOTS:
    void Toggle();
    void Show();
    void Hide();
    void SyncWidgets();

private:
    WIDGETS_FRAME_NAMESPACE::WidgetManager *m_manager;
    WIDGETS_FRAME_NAMESPACE::MainView *m_mainView = nullptr;
};
