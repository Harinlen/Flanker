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
#ifndef KNMAINMENUBUTTON_H
#define KNMAINMENUBUTTON_H

#include <QAbstractButton>

/*!
 * \brief The KNMainMenuButton class provides the main menu button for the main
 * window.
 * It uses the different role for coloring the button:
 *  - Base: Default state color.
 *  - Window: Hover state color.
 *  - Button: Pressed state color.
 */
class KNMainMenuButton : public QAbstractButton
{
    Q_OBJECT
public:
    /*!
     * \brief Construct a KNMainMenuButton widget.
     * \param parent The parent widget.
     */
    explicit KNMainMenuButton(QWidget *parent = nullptr);

signals:

public slots:

protected:
    /*!
     * \brief Reimplemented from QAbstractButton::enterEvent().
     */
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from QAbstractButton::leaveEvent().
     */
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from QAbstractButton::paintEvent().
     */
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    bool m_entered;
};

#endif // KNMAINMENUBUTTON_H
