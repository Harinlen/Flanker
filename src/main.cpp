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

#include "core/knpluginmanager.h"
#include "knmainwindow.h"

int main(int argc, char *argv[])
{
    // Initial the global settings.
    QApplication app(argc, argv);
    // Initial the plugin manager.
    KNPluginManager pluginManager;
    // Initial the main window instance.
    KNMainWindow mainWindow;
    pluginManager.setMainWindow(&mainWindow);
    // Load all the plugins.
    pluginManager.loadPlugins();
    // Start the application.
    pluginManager.start();
    // Initial the main window.
    return app.exec();
}
