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
 * along with this program; if not, write to the Free Software
Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef KNLOGICGLOBAL_H
#define KNLOGICGLOBAL_H

#include <QVector>

#include <QObject>

#define knLogicGlobal (KNLogicGlobal::instance())

namespace LogicGlobal
{
    enum LogicChars
    {
        LogicImplement,
        LogicOr,
        LogicAnd,
        LogicNot,
        LogicTrue,
        LogicFalse,
        LogicCharCount
    };
};

class KNLogicGlobal : public QObject
{
    Q_OBJECT
public:
    static KNLogicGlobal *instance();

    static void initial(QObject *parent = nullptr);

    QChar logicChar(int index) const;

    QString logicRule(int index) const;

signals:

public slots:

private:
    static KNLogicGlobal *m_instance;

    explicit KNLogicGlobal(QObject *parent = 0);
    KNLogicGlobal(const KNLogicGlobal &);
    KNLogicGlobal(KNLogicGlobal &&);

    QVector<QChar> m_logicChars;
};

#endif // KNLOGICGLOBAL_H
