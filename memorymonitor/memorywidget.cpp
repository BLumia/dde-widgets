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

#include "memorywidget.h"
#include "common/utils.h"

#include <DApplication>
#include <DApplicationHelper>

#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>
#include <QBrush>
#include <QPaintEvent>
#include <QFontMetrics>

DWIDGET_USE_NAMESPACE

using namespace Utils;

MemoryWidget::MemoryWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *dAppHelper = DApplicationHelper::instance();
    connect(dAppHelper, &DApplicationHelper::themeTypeChanged, this, &MemoryWidget::changeTheme);
    changeTheme(dAppHelper->themeType());

    changeFont(DApplication::font());
    connect(dynamic_cast<QGuiApplication *>(DApplication::instance()), &DApplication::fontChanged,
            this, &MemoryWidget::changeFont);
}
MemoryWidget::~MemoryWidget() {}

void MemoryWidget::updateMemoryInfo(const QString &memPercent,
                                    const QString &swapPercent)
{
    m_memPercent = memPercent;
    m_swapPercent = swapPercent;
}

void MemoryWidget::changeTheme(DApplicationHelper::ColorType themeType)
{
    switch (themeType) {
    case DApplicationHelper::LightType:
        memoryBackgroundColor = "#000000";
        swapBackgroundColor = "#000000";

        break;
    case DApplicationHelper::DarkType:
        memoryBackgroundColor = "#FFFFFF";
        swapBackgroundColor = "#FFFFFF";

        break;
    default:
        break;
    }

    // init colors
    auto palette = DApplicationHelper::instance()->applicationPalette();
#ifndef THEME_FALLBACK_COLOR
    numberColor = palette.color(DPalette::TextTitle);
#else
    numberColor = palette.color(DPalette::Text);
#endif

    summaryColor = palette.color(DPalette::TextTips);
}

void MemoryWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter;
    painter.begin(this);

    //裁剪绘制区域
    QPainterPath path;
    path.addRoundedRect(rect(), 8, 8);
    painter.setClipPath(path);
    //背景
    QRect contentRect(rect());
    painter.fillRect(contentRect, QBrush(QColor(255, 255, 255,100)));

    int sectionSize = 6;

    QString memoryContent = QString("%1 (%2%)")
                          .arg(tr("Memory"))//Memory
                          .arg(m_memPercent);

    QString swapContent;
    if (m_swapPercent.isEmpty()) {
        // After the memory and swap space text, add a space before the brackets
        swapContent = QString("%1 (%2)")
                    .arg(tr("SW Memory"))//Swap
                    .arg(tr("Unabled"));
    } else {
        swapContent = QString("%1 (%2%)")
                              .arg(tr("SW Memory"))//Memory
                              .arg(m_swapPercent);
    }

    QFontMetrics fmMemTxt(m_memTxtFont);
    const int ContentTextWidth = qMax(fmMemTxt.size(Qt::TextSingleLine, memoryContent).width(),
                                      fmMemTxt.size(Qt::TextSingleLine, swapContent).width());

    int leftMargin = (contentRect.width() - ContentTextWidth) / 2;
    int topMargin = 15;
    int margin = 8;
    //内存txt
    QRect memTxtRect(contentRect.left() + leftMargin, contentRect.top() + topMargin,
                      fmMemTxt.size(Qt::TextSingleLine, memoryContent).width(),
                      fmMemTxt.height());
    QRectF memIndicatorRect(memTxtRect.x() - margin, memTxtRect.y() + qCeil((memTxtRect.height() - sectionSize) / 2.),
                            sectionSize, sectionSize);


    QPainterPath section;
    section.addEllipse(memIndicatorRect);
    painter.fillPath(section, memoryColor);

    painter.setFont(m_memTxtFont);
    painter.setPen(QPen(summaryColor));
    painter.drawText(memTxtRect, Qt::AlignLeft | Qt::AlignVCenter, memoryContent);

    QRect swapTxtRect(memTxtRect.left(), memTxtRect.bottom() + margin,//+ topsize
                      fmMemTxt.size(Qt::TextSingleLine, swapContent).width(),
                      fmMemTxt.height());
    QRectF swapIndicatorRect(swapTxtRect.x() - margin, swapTxtRect.y() + qCeil((swapTxtRect.height() - sectionSize) / 2.),
                             sectionSize, sectionSize);


    QPainterPath section2;
    section2.addEllipse(swapIndicatorRect);
    painter.fillPath(section2, swapColor);

    painter.setFont(m_memTxtFont);
    painter.setPen(QPen(summaryColor));
    painter.drawText(swapTxtRect, Qt::AlignLeft | Qt::AlignVCenter, swapContent);

    const int outsideRingRadius = (contentRect.bottom() - swapTxtRect.bottom() - topMargin) / 2;
    const int insideRingRadius = outsideRingRadius - ringWidth - 1;
    const auto &ringCenter = QPoint(contentRect.center().x(), swapIndicatorRect.bottom() + margin + outsideRingRadius);
    // Draw memory ring.
    drawLoadingRing(painter, ringCenter.x(), ringCenter.y(),
                    outsideRingRadius, ringWidth, 270, 270, memoryForegroundColor,
                    memoryForegroundOpacity, memoryBackgroundColor, memoryBackgroundOpacity,
                    m_memPercent.toDouble()/100);

    // Draw swap ring.
    drawLoadingRing(painter, ringCenter.x(), ringCenter.y(),
                    insideRingRadius, ringWidth, 270, 270, swapForegroundColor,
                    swapForegroundOpacity, swapBackgroundColor, swapBackgroundOpacity, m_swapPercent.toDouble()/100);

    // Draw percent text.
    painter.setFont(m_memPercentFont);
    painter.setPen(QPen(numberColor));
    painter.drawText(QRect(ringCenter.x() - insideRingRadius,
                           ringCenter.y() - insideRingRadius, insideRingRadius * 2,
                           insideRingRadius * 2),
                     Qt::AlignHCenter | Qt::AlignVCenter,
                     QString("%1%").arg(QString::number(m_memPercent.toDouble(), 'f', 1)));
}

void MemoryWidget::changeFont(const QFont &font)
{
    m_memTxtFont = font;
    m_memTxtFont.setFamily("SourceHanSansSC");
    m_memTxtFont.setWeight(QFont::ExtraLight);
    m_memTxtFont.setPointSizeF(m_memTxtFont.pointSizeF()-2 );
}
