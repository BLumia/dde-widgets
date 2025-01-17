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
#include "widgetmanager.h"
#include "widgetsserver.h"
#include "displaymodepanel.h"
#include "accessible/accessible.h"

#include <DWidgetUtil>
#include <DApplication>
#include <DLog>
#include <DGuiApplicationHelper>
DGUI_USE_NAMESPACE

WIDGETS_USE_NAMESPACE
DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    // no inactive color for the application, and it need to be set before DApplication constructor.
    DGuiApplicationHelper::setAttribute(DGuiApplicationHelper::UseInactiveColorGroup, false);
    DApplication a(argc, argv);
    a.setApplicationVersion("1.0.0");
    a.setOrganizationName("deepin");
    a.setApplicationName("dde-widgets");

    // avoid to being quit when dialog is closed with it's parent invisible.
    a.setQuitOnLastWindowClosed(false);
    // enable accessible
    QAccessible::installFactory(accessibleFactory);

    // TODO it's temporay in dbug.
//    Dtk::Core::DLogManager::registerConsoleAppender();
//    Dtk::Core::DLogManager::registerFileAppender();
    qInfo() << "Log path is:" << Dtk::Core::DLogManager::getlogFilePath();

    a.loadTranslator();

    WidgetsServer server;
    if (server.registerService()) {
        qInfo(dwLog()) << "start dde-widgets successfully.";
    } else {
        qInfo(dwLog()) << "start dde-widgets failed.";
        return 1;
    }
    server.start();

    return a.exec();
}
