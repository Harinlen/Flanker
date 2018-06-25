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
#include "knthememanager.h"
#include "kndpimanager.h"
#include "kntoolbar.h"

#include "knmainwindow.h"

#include <QDebug>

KNMainWindow::KNMainWindow(QWidget *parent) : QMainWindow(parent),
    m_toolBar(new KNToolbar(this))
{
    // Set properties
    setAutoFillBackground(true);
    setMinimumSize(knDpi->size(854, 480));
    setObjectName("MainWindow");

    // Load theme.
    knTheme->registerWidget(this);
}

void KNMainWindow::addToToolBar(QWidget *widget, int stretch)
{
    // Add widget to the toolbar.
    m_toolBar->addWidget(widget, stretch);
}

void KNMainWindow::resizeEvent(QResizeEvent *event)
{
    // Resize the main window.
    QMainWindow::resizeEvent(event);
    // Resize the toolbar.
    m_toolBar->resize(width(), m_toolBar->height());
}
