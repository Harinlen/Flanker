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
#include <QButtonGroup>
#include <QBoxLayout>
#include <QWidget>

#include "kndpimanager.h"
#include "kntabbutton.h"

#include "kntabbar.h"

#include <QDebug>

KNTabBar::KNTabBar(QWidget *parent) : QScrollArea(parent),
    m_tabContainer(new QWidget(this)),
    m_tabLayout(new QBoxLayout(QBoxLayout::LeftToRight, m_tabContainer)),
    m_tabGroup(new QButtonGroup(this))
{
    // Set properties.
    setContentsMargins(0, 0, 0, 0);
    setFrameStyle(QFrame::NoFrame);
    // Configure the container.
    m_tabContainer->setContentsMargins(0, 0, 0, 0);
    // Configure the layout.
    m_tabLayout->setContentsMargins(0, 0, 0, 0);
    m_tabLayout->setSpacing(0);
    m_tabContainer->setLayout(m_tabLayout);
    // Configure the tab group.
    setWidget(m_tabContainer);
}

void KNTabBar::addTab(KNTabButton *tabButton)
{
    // Add button to the button group.
    m_tabGroup->addButton(tabButton);
    // Add the button to container.
    m_tabLayout->addWidget(tabButton);
    // Check the tab counts.
    int tabCounts = m_tabGroup->buttons().size();
    // Update container size.
    m_tabContainer->setFixedSize(
                knDpi->width(TabWidth) * tabCounts,
                knDpi->height(TabHeight));
    if(tabCounts==1)
    {
        // Select the tab button.
        tabButton->setChecked(true);
    }
}
