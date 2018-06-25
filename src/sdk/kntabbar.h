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
#ifndef KNTABBAR_H
#define KNTABBAR_H

#include <QScrollArea>

class QBoxLayout;
class QButtonGroup;
class KNTabButton;
/*!
 * \brief The KNTabBar class provides the tab bars like it in firefox.
 */
class KNTabBar : public QScrollArea
{
    Q_OBJECT
public:
    explicit KNTabBar(QWidget *parent = nullptr);

    void addTab(KNTabButton *tabButton);

signals:

public slots:

private:
    QWidget *m_tabContainer;
    QBoxLayout *m_tabLayout;
    QButtonGroup *m_tabGroup;
};

#endif // KNTABBAR_H
