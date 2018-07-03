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
#ifndef KNLOGICDOCUMENT_H
#define KNLOGICDOCUMENT_H

#include "knlogicutil.h"

#include <QAbstractTableModel>

using namespace LogicUtil;

class KNLogicDocument : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum LogicDocumentColumn
    {
        ColumnAssumption,
        ColumnLineNumber,
        ColumnFormula,
        ColumnRule,
        LogicDocumentColumnCount
    };

    enum LineDataIndex
    {
        LineAssumption,
        LineFormula,
        LineRule,
        LineDependencies,
        LineDataCount
    };

    explicit KNLogicDocument(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const
    Q_DECL_OVERRIDE;

    int columnCount(const QModelIndex &parent = QModelIndex()) const
    Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    Q_DECL_OVERRIDE;

    QString title();
    QStringList renderLogicLine(int row);

signals:

public slots:
    bool loadFromFile(const QString &filePath);
    void loadFromJson(const QByteArray &jsonText);

private:

    inline void clearLines();
    inline QString getAssumption(const KNLogicLine &renderLogicLine,
                                 int lineRow) const;
    inline QString getRule(const KNLogicLine &logicLine) const;
    inline QString getLineNumber(const QPersistentModelIndex &targetIndex) const;
    QList<KNLogicLine> m_lines;
    QString m_premise, m_sequent;
};

#endif // KNLOGICDOCUMENT_H
