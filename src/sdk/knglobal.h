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
#ifndef KNGLOBAL_H
#define KNGLOBAL_H

#include <QObject>

/*!
 * \def knGlobal
 * A global pointer referring to the unique global object.
 */
#define knGlobal (KNGlobal::instance())

class KNConfigure;
/*!
* \brief The KNGlobal class is a global instance which contains several public
 * function. \n
 * You should only construct this class once. If you construct the KNGlobal more
 * than once, the other instance will become no use.\n
 * This global instance will also initial several singleton instance, and take
 * those managers' control.
 *  * KNThemeManager - A Json based color theme file manager.
 */
class KNGlobal : public QObject
{
    Q_OBJECT
public:
    enum DefaultPath
    {
        KreogistDir,
        UserDataDir,
        ResourceDir,
        DefaultDirCount
    };

    ~KNGlobal();

    /*!
     * \brief Get the singleton instance of class KNGlobal.
     * \return The global instance of KNGlobal.
     */
    static KNGlobal *instance();

    /*!
     * \brief Initial the global class.
     * \param parent The parent object of the global class.
     */
    static void initial(QObject *parent = 0);

    /*!
     * \brief Get the user configure class.
     * \return The user KNConfigure class.
     */
    KNConfigure *userConfigure();

signals:

public slots:

private:
    explicit KNGlobal(QObject *parent = nullptr);
    //Disable the copy of the instance.
    KNGlobal(const KNGlobal &);
    KNGlobal(KNGlobal &&);
    static KNGlobal *m_instance;

    inline void initialDefaultDirPath();
    inline void initialInfrastrcture();

    QString m_dirPath[DefaultDirCount];
    KNConfigure *m_globalConfigure;
};

#endif // KNGLOBAL_H
