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
#include <QGraphicsColorizeEffect>

#include "knthememanager.h"
#include "kndpimanager.h"
#include "knsimplebutton.h"

#include "kntabbutton.h"

#define LabelHeight 11
#define SideMargin  5
#define TotalMargin 30

KNTabButton::KNTabButton(QWidget *parent) : QAbstractButton(parent),
    m_buttonText(QStaticText()),
    m_closeButton(new KNSimpleButton(this)),
    m_closeEffect(new QGraphicsColorizeEffect(this)),
    m_entered(false)
{
    setObjectName("TabButton");
    // Set properties.
    setCheckable(true);
    setFixedSize(knDpi->size(TabWidth, TabHeight));
    // Configure the button text.
    m_buttonText.setTextFormat(Qt::PlainText);
    // Update the font size.
    QFont labelFont=font();
    labelFont.setPixelSize(knDpi->height(LabelHeight));
    setFont(labelFont);
    // Configure the close button.
    m_closeButton->setIcon(QIcon(":/public/close.png"));
    m_closeButton->setFixedSize(knDpi->size(18, 18));
    // Configure the close effect.
    // Link to the theme manager.
    connect(knTheme, &KNThemeManager::themeChange,
            this, &KNTabButton::updatePalette);
    updatePalette();
}

void KNTabButton::setText(const QString &text)
{
    // Update the static text.
    updateStaticText(text);
    // Set the original text.
    QAbstractButton::setText(text);
}

void KNTabButton::enterEvent(QEvent *event)
{
    // Handle the original event.
    QAbstractButton::enterEvent(event);
    // Repaint the button.
    m_entered = true;
    update();
}

void KNTabButton::leaveEvent(QEvent *event)
{
    // Handle the original event.
    QAbstractButton::enterEvent(event);
    // Repaint the button.
    m_entered = false;
    update();
}

void KNTabButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    // Draw the other content
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::TextAntialiasing |
                           QPainter::SmoothPixmapTransform);
    QRect backRect = QRect(0, 0, width()-1, height());
    // Check the state.
    if(isChecked())
    {
        // Fill the rect.
        painter.fillRect(backRect, palette().button());
        // Update the pen.
        const QColor &textColor=palette().color(QPalette::ButtonText);
        m_closeEffect->setColor(textColor);
        m_closeButton->setGraphicsEffect(m_closeEffect);
        painter.setPen(textColor);
    }
    else
    {
        // Check whether mouse is entered.
        if(m_entered)
        {
            // Fill the background as base color.
            painter.fillRect(backRect, palette().base());
        }
        // Update the pen.
        const QColor &textColor=palette().color(QPalette::WindowText);
        m_closeEffect->setColor(textColor);
        m_closeButton->setGraphicsEffect(m_closeEffect);
        painter.setPen(textColor);
    }
    // Draw the text.
    painter.drawStaticText(SideMargin, (height()-LabelHeight)>>1, m_buttonText);
}

void KNTabButton::resizeEvent(QResizeEvent *event)
{
    m_buttonText.setTextWidth(width() - TotalMargin);
    // Update the static text.
    updateStaticText(text());
    // Resize the button.
    QAbstractButton::resizeEvent(event);
    // Move the close button.
    m_closeButton->move(width() - m_closeButton->width() - SideMargin,
                        ((height() - m_closeButton->height()) >> 1) + 1);
}

void KNTabButton::updatePalette()
{
    // Update the palette.
    setPalette(knTheme->getPalette(objectName()));
}

void KNTabButton::updateStaticText(const QString &text)
{
    // Update the static button text.
    m_buttonText.setText(fontMetrics().elidedText(text,
                                                  Qt::ElideRight,
                                                  width() - TotalMargin));
    if(m_buttonText.text() == text)
    {
        // Clear the tooltip.
        setToolTip("");
    }
    else
    {
        // Update the tooltip.
        setToolTip(text);
    }
}
