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

#include "settingsview.h"
#include "timezonemodel.h"
#include "global.h"
#include "zonechooseview.h"

#include <DLabel>
#include <DListView>
#include <QDebug>
#include <QHBoxLayout>
#include <QMouseEvent>

DWIDGET_USE_NAMESPACE
namespace dwclock {

SettingsView::SettingsView(TimezoneModel *model, QWidget *parent)
    : DDialog(parent)
    , m_clockView(new DListView())
    , m_model(model)
{
    setTitle(tr("Modify City"));
    addSpacing(UI::edit::spacingDesc);
    auto desc = new DLabel();
    DFontSizeManager::instance()->bind(desc, DFontSizeManager::T8);
    desc->setText(tr("Display clocks at different geographical locations"));
    addContent(desc, Qt::AlignHCenter);
    addSpacing(UI::edit::spacingTitle);
    addButton(tr("Cancle"));
    addButton(tr("Save"));

    setFixedSize(UI::clock::settingsDialogSize);
    m_clockView->setDragDropMode(QListView::InternalMove);
    m_clockView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_clockView->setBackgroundType(DStyledItemDelegate::RoundedBackground);
    m_clockView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_clockView->setSpacing(1);
    m_clockView->setItemSize(UI::edit::itemSize);
    m_clockView->setModel(m_model);
    addContent(m_clockView);
    connect(model, &TimezoneModel::modifyLocationClicked, this, &SettingsView::showModifyLocation);
}

TimezoneModel *SettingsView::model() const
{
    return m_model;
}

void SettingsView::closeEvent(QCloseEvent *event)
{
    if (m_chooseView) {
        m_chooseView->close();
    }
    DDialog::closeEvent(event);
}

void SettingsView::showModifyLocation(const QModelIndex &index)
{
    qDebug() << "showModifyLocation(): modify the item:" << index;
    m_chooseView = new ZoneChooseView(this);
    m_chooseView->moveToCenter();
    if (QDialog::Accepted == m_chooseView->exec()) {
        const QString &timezone = m_chooseView->currentZone();
        m_model->updateTimezone(index, timezone);
    }
    m_chooseView->deleteLater();
    m_chooseView = nullptr;
}
}
