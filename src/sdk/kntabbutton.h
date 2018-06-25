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
#ifndef KNTABBUTTON_H
#define KNTABBUTTON_H

#include <QStaticText>

#include <QAbstractButton>

#define TabWidth    105
#define TabHeight   25

class QGraphicsColorizeEffect;
class KNSimpleButton;
/*!
 * \brief The KNTabButton class provides a button for the tab.
 */
class KNTabButton : public QAbstractButton
{
    Q_OBJECT
public:
    /*!
     * \brief Construct a KNTabButton button.
     * \param parent The parent widget.
     */
    explicit KNTabButton(QWidget *parent = nullptr);

    void setText(const QString &text);

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

    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:
    void updatePalette();

private:
    inline void updateStaticText(const QString &text);
    QStaticText m_buttonText;
    KNSimpleButton *m_closeButton;
    QGraphicsColorizeEffect *m_closeEffect;
    bool m_entered;
};

#endif // KNTABBUTTON_H
