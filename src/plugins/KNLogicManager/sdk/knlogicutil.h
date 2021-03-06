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
#ifndef KNLOGICUTIL_H
#define KNLOGICUTIL_H

#include <QPersistentModelIndex>

namespace LogicUtil {
    enum KNLogicRules
    {
        RuleUnknown,
        RuleAssumption,
        RuleAndE,
        RuleAndI,
        RuleOrE,
        RuleOrI,
        RuleToE,
        RuleToI,
        RuleRedAdAbs,
        RuleDoubleNegE,
        RuleDoubleNegI,
        RuleNegE,
        RuleNegI,
        LogicRulesCount
    };

    struct KNLogicUse
    {
        QPersistentModelIndex index;
        QList<QPersistentModelIndex> notCare;
    };

    struct KNLogicLine
    {
        QList<QPersistentModelIndex> assumptions;
        QString formula;
        int rule;
        QList<KNLogicUse> uses;
    };
}

class KNLogicUtil
{
public:
    KNLogicUtil();
};

#endif // KNLOGICUTIL_H
