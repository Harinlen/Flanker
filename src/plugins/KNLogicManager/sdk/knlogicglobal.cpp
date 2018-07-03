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
#include "knlogicutil.h"

#include "knlogicglobal.h"

using namespace LogicUtil;
using namespace LogicGlobal;

KNLogicGlobal *KNLogicGlobal::m_instance = nullptr;

KNLogicGlobal *KNLogicGlobal::instance()
{
    return m_instance;
}

void KNLogicGlobal::initial(QObject *parent)
{
    if(m_instance)
    {
        return;
    }
    // Initial the parent instance.
    m_instance=new KNLogicGlobal(parent);
}

QChar KNLogicGlobal::logicChar(int index) const
{
    return index<LogicCharCount ? m_logicChars.at(index) : QChar();
}

QString KNLogicGlobal::logicRule(int index) const
{
    switch(index)
    {
    case RuleAssumption:
        return "A";
    case RuleAndE:
        return QString(m_logicChars.at(LogicAnd)) + "E";
    case RuleAndI:
        return QString(m_logicChars.at(LogicAnd)) + "I";
    case RuleOrE:
        return QString(m_logicChars.at(LogicOr)) + "E";
    case RuleOrI:
        return QString(m_logicChars.at(LogicOr)) + "I";
    case RuleToE:
        return QString(m_logicChars.at(LogicImplement)) + "E";
    case RuleToI:
        return QString(m_logicChars.at(LogicImplement)) + "I";
    case RuleRedAdAbs:
        return "RAA";
    case RuleDoubleNegE:
        return QString(m_logicChars.at(LogicNot)) +
                m_logicChars.at(LogicNot) + "E";
    case RuleDoubleNegI:
        return QString(m_logicChars.at(LogicNot)) +
                m_logicChars.at(LogicNot) + "I";
    case RuleNegE:
        return QString(m_logicChars.at(LogicNot)) + "E";
    case RuleNegI:
        return QString(m_logicChars.at(LogicNot)) + "I";
    default:
        return QString();
    }
}

KNLogicGlobal::KNLogicGlobal(QObject *parent) : QObject(parent),
    m_logicChars(QVector<QChar>(LogicCharCount))
{
    // Initial logic chars.
    m_logicChars.replace(LogicImplement, QChar(146, 33));
    m_logicChars.replace(LogicOr, QChar(40, 34));
    m_logicChars.replace(LogicAnd, QChar(39, 34));
    m_logicChars.replace(LogicNot, QChar(172, 0));
    m_logicChars.replace(LogicTrue, QChar(164, 34));
    m_logicChars.replace(LogicFalse, QChar(165, 34));
}
