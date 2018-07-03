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
#include <QBoxLayout>

#include "knthememanager.h"
#include "kndpimanager.h"
#include "kntoolbar.h"

#include "knmainwindow.h"

#include <QDebug>

KNMainWindow::KNMainWindow(QWidget *parent) : QMainWindow(parent),
    m_mainLayout(new QBoxLayout(QBoxLayout::TopToBottom)),
    m_toolBar(new KNToolbar(this))
{
    // Set properties
    setContentsMargins(0, 0, 0, 0);
    setAutoFillBackground(true);
    setMinimumSize(knDpi->size(854, 480));
    setObjectName("MainWindow");

    // Construct the container.
    QWidget *container=new QWidget(this);
    container->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(container);
    // Set the layout.
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    container->setLayout(m_mainLayout);
    // Add widget.
    m_mainLayout->addWidget(m_toolBar);

    // Load theme.
    knTheme->registerWidget(this);
}

void KNMainWindow::addToToolBar(QWidget *widget, int stretch)
{
    // Add widget to the toolbar.
    m_toolBar->addWidget(widget, stretch);
}

void KNMainWindow::addToCentral(QWidget *widget, int stretch)
{
    // Add to main layout.
    m_mainLayout->addWidget(widget, stretch);
}

void KNMainWindow::resizeEvent(QResizeEvent *event)
{
    // Resize the main window.
    QMainWindow::resizeEvent(event);
    // Resize the toolbar.
    m_toolBar->resize(width(), m_toolBar->height());
}
