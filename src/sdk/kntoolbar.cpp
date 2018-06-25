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
#include <QToolBar>
#include <QTabBar>

#include "knmainmenubutton.h"
#include "kntabbar.h"
#include "kntabbutton.h"
#include "knthememanager.h"
#include "kndpimanager.h"

#include "kntoolbar.h"

KNToolbar::KNToolbar(QWidget *parent) : QWidget(parent),
    m_mainMenu(new KNMainMenuButton(this)),
    m_toolbar(new QToolBar(this)),
    m_mainLayout(new QBoxLayout(QBoxLayout::LeftToRight, this))
{
    setObjectName("ToolBar");
    // Set properties.
    setAutoFillBackground(true);
    setContentsMargins(0, 0, 0, 0);
    setFixedHeight(knDpi->height(25));
    // Configure the button.
    m_mainMenu->setObjectName("MainMenuButton");
    m_mainMenu->setFixedSize(knDpi->size(59, 25));
    m_mainMenu->setText("File");
    knTheme->registerWidget(m_mainMenu);

    // Initial the layout.
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    setLayout(m_mainLayout);
    // Add widgets.
    m_mainLayout->addWidget(m_mainMenu);
    m_mainLayout->addWidget(m_toolbar);
    // Apply theme.
    knTheme->registerWidget(this);
}

void KNToolbar::addWidget(QWidget *widget, int stretch)
{
    // Add widget to layout.
    m_mainLayout->addWidget(widget, stretch);
}
