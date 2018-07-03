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
#include <QApplication>
#include <QStyleFactory>

#include "knmainwindow.h"
#include "knlogicmanagerbase.h"
#include "knglobal.h"

// Plugins.
#include "../plugins/knlogicmanager/knlogicmanager.h"

#include "knpluginmanager.h"

KNPluginManager::KNPluginManager(QObject *parent) : QObject(parent),
    m_mainWindow(nullptr)
{
    //Set fusion style to application.
    QApplication::setStyle(QStyleFactory::create("fusion"));
    //Initial the global.
    KNGlobal::initial(this);
}

void KNPluginManager::start()
{
    // Check the main window pointer state.
    if(m_mainWindow)
    {
        // Show the main window.
        m_mainWindow->show();
    }
}

void KNPluginManager::loadLogicManager(KNLogicManagerBase *logicManager)
{
    // Add the logic mananger tab bar.
    m_mainWindow->addToToolBar(logicManager->tabBar(), 1);
    // Add the logic manager status bar.
    m_mainWindow->addToToolBar(logicManager->statusBar());
    // Set the central widget.
    m_mainWindow->addToCentral(logicManager->centralWidget(), 1);
}

void KNPluginManager::setMainWindow(KNMainWindow *mainWindow)
{
    m_mainWindow = mainWindow;
}

void KNPluginManager::loadPlugins()
{
    // Check main window.
    if(!m_mainWindow)
    {
        return;
    }
    // Load the logic manager parts to main window.
    loadLogicManager(new KNLogicManager(m_mainWindow));
}
