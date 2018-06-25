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
#ifndef KNMAINWINDOW_H
#define KNMAINWINDOW_H

#include <QMainWindow>

class KNToolbar;
/*!
 * \brief The KNMainWindow class provides the main window for the application.
 * This class should rebuild for each application.
 */
class KNMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit KNMainWindow(QWidget *parent = nullptr);

    /*!
     * \brief Add a widget to tool bar row.
     * \param widget The widget pointer.
     * \param stretch The stretch hint.
     */
    void addToToolBar(QWidget *widget, int stretch = 0);

signals:

public slots:

protected:
    /*!
     * \brief Reimplemented from QMainWindow::resizeEvent().
     */
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    KNToolbar *m_toolBar;
};

#endif // KNMAINWINDOW_H
