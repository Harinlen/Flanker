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
#ifndef KNTOOLBAR_H
#define KNTOOLBAR_H

#include <QWidget>

class QBoxLayout;
class QToolBar;
class KNMainMenuButton;
/*!
 * \brief The KNToolbar class provides a general toolbar with a menu button at
 * the left most position. The button should be used for the menu. The toolbar
 * allows user to add customer actions.
 */
class KNToolbar : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Construct a KNToolbar widget.
     * \param parent The parent widget.
     */
    explicit KNToolbar(QWidget *parent = nullptr);

    /*!
     * \brief Add a widget to the toolbar row.
     * \param widget The widget pointer.
     * \param stretch The stretch hint parameter.
     */
    void addWidget(QWidget *widget, int stretch = 0);

signals:

public slots:

private:
    KNMainMenuButton *m_mainMenu;
    QToolBar *m_toolbar;
    QBoxLayout *m_mainLayout;
};

#endif // KNTOOLBAR_H
