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
#ifndef KNLOGICMANAGER_H
#define KNLOGICMANAGER_H

#include "knlogicmanagerbase.h"

class KNTabBar;
class KNLogicManager : public KNLogicManagerBase
{
    Q_OBJECT
public:
    explicit KNLogicManager(QWidget *parent = nullptr);

    QWidget *tabBar() const Q_DECL_OVERRIDE;

    QWidget *statusBar() const Q_DECL_OVERRIDE;

    QWidget *centralWidget() const Q_DECL_OVERRIDE;

signals:

public slots:

private:
    KNTabBar *m_tabBar;

};

#endif // KNLOGICMANAGER_H
