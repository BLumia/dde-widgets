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
#include <widgetsinterface.h>

WIDGETS_FRAME_BEGIN_NAMESPACE
class WidgetManager;
WIDGETS_FRAME_END_NAMESPACE

struct PluginInfo {
    WIDGETS_NAMESPACE::IWidgetPlugin *plugin = nullptr;
    WIDGETS_FRAME_NAMESPACE::PluginId id;
    QString fileName;
    QString version;
};
WIDGETS_BEGIN_NAMESPACE

class WidgetPluginSpec {
public:
    explicit WidgetPluginSpec(const PluginInfo &info);
    ~WidgetPluginSpec();

    WIDGETS_FRAME_NAMESPACE::PluginId id() const;
    QString title() const;
    QString description() const;
    QString aboutDescription() const;
    IWidgetPlugin::Type type() const;
    QString version() const;
    QIcon logo() const;
    QStringList contributors() const;

    QVector<IWidget::Type> supportTypes() const;
    void removeSupportType(const IWidget::Type type);

    WIDGETS_FRAME_NAMESPACE::Instance *createWidget(const IWidget::Type &type);
    WIDGETS_FRAME_NAMESPACE::Instance *createWidget(const IWidget::Type &type, const WIDGETS_FRAME_NAMESPACE::InstanceId &key);
private:

    WIDGETS_FRAME_NAMESPACE::Instance *createWidgetForWidgetStore(const IWidget::Type &type);

    WIDGETS_FRAME_NAMESPACE::Instance *createWidgetImpl(const IWidget::Type &type, const WIDGETS_FRAME_NAMESPACE::InstanceId &key);
    void setDataStore(WIDGETS_FRAME_NAMESPACE::DataStore *store);

    IWidgetPlugin *m_plugin = nullptr;
    WIDGETS_FRAME_NAMESPACE::PluginId m_pluginId;
    WIDGETS_FRAME_NAMESPACE::DataStore *m_dataStore = nullptr;
    QString m_fileName;
    QString m_version;
    QVector<IWidget::Type> m_supportTypes;

    friend class WIDGETS_FRAME_NAMESPACE::WidgetManager;
};

WIDGETS_END_NAMESPACE
