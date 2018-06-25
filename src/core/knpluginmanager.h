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
#ifndef KNPLUGINMANAGER_H
#define KNPLUGINMANAGER_H

#include <QObject>

class KNLogicManagerBase;
class KNMainWindow;
/*!
 * \brief The KNPluginManager class provides the central manager for the entire
 * application. It manages the class construction and destory.
 */
class KNPluginManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Construct a KNPluginManager object.
     * \param parent The parent object.
     */
    explicit KNPluginManager(QObject *parent = nullptr);


signals:

public slots:
    /*!
     * \brief Set the main window to the plugin manager.
     * \param mainWindow The main window pointer.
     */
    void setMainWindow(KNMainWindow *mainWindow);

    /*!
     * \brief Load all the plugin modules.
     */
    void loadPlugins();

    /*!
     * \brief Start to execute the program.
     */
    void start();

private:
    inline void loadLogicManager(KNLogicManagerBase *logicManager);
    KNMainWindow *m_mainWindow;
};

#endif // KNPLUGINMANAGER_H
