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

#include "knmainmenubutton.h"

KNMainMenuButton::KNMainMenuButton(QWidget *parent) : QAbstractButton(parent),
    m_entered(false)
{

}

void KNMainMenuButton::enterEvent(QEvent *event)
{
    // Handle the original event.
    QAbstractButton::enterEvent(event);
    // Repaint the button.
    m_entered = true;
    update();
}

void KNMainMenuButton::leaveEvent(QEvent *event)
{
    // Handle the original event.
    QAbstractButton::enterEvent(event);
    // Repaint the button.
    m_entered = false;
    update();
}

void KNMainMenuButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    // Initial the painter.
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::SmoothPixmapTransform);
    // Check entered.
    if(m_entered)
    {
        // Check the whether the mouse is pressed down.
        if(isDown())
        {
            // Paint the pressed color.
            painter.fillRect(rect(), palette().button());
        }
        else
        {
            // Paint the hover color.
            painter.fillRect(rect(), palette().window());
        }
    }
    else
    {
        // Just paint the base color.
        painter.fillRect(rect(), palette().base());
    }
}
