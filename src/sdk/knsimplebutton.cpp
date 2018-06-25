/*
 * Copyright (C) Kreogist Dev Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#include <QPainter>

#include "knsimplebutton.h"

KNSimpleButton::KNSimpleButton(QWidget *parent) : QAbstractButton(parent),
    m_entered(false)
{
}

void KNSimpleButton::enterEvent(QEvent *event)
{
    // Handle the original event.
    QAbstractButton::enterEvent(event);
    // Repaint the button.
    m_entered = true;
    update();
}

void KNSimpleButton::leaveEvent(QEvent *event)
{
    // Handle the original event.
    QAbstractButton::enterEvent(event);
    // Repaint the button.
    m_entered = false;
    update();
}

void KNSimpleButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::SmoothPixmapTransform);

    // When entered.
    if(isDown())
    {
        // Draw the pressed background.
        painter.fillRect(rect(), QColor(0x00, 0x00, 0x00, 0x67));
    }
    else
    {
        // Check mouse entered state.
        if(m_entered)
        {
            // Draw the hover background
            painter.fillRect(rect(), QColor(0x00, 0x00, 0x00, 0x40));
        }
    }

    QPixmap iconPixmap = icon().pixmap(size());
    painter.drawPixmap((width() - iconPixmap.width())>>1,
                       (height() - iconPixmap.height())>>1,
                       iconPixmap);
}
