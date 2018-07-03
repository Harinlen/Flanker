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
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

#include "knlogicglobal.h"

#include "knlogicdocument.h"

#include <QDebug>

KNLogicDocument::KNLogicDocument(QObject *parent) : QAbstractTableModel(parent),
    m_premise(QString()),
    m_sequent(QString())
{
}

int KNLogicDocument::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        return 0;
    }
    return m_lines.size();
}

int KNLogicDocument::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        return 0;
    }
    return LogicDocumentColumnCount;
}

QVariant KNLogicDocument::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }
    // Pick out the structure.
    const KNLogicLine &logicLine = m_lines.at(index.row());
    // Check the index row.
    switch(role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        // We only need these two roles.
        switch(index.column())
        {
        case ColumnAssumption:
            return getAssumption(logicLine, index.row());
        case ColumnLineNumber:
            return QString::number(index.row()+1);
        case ColumnFormula:
            return logicLine.formula;
        case ColumnRule:
            return QString();
        }
    default:
        return QVariant();
    }
}

QString KNLogicDocument::title()
{
    return m_premise + "   " + QChar(162, 34) + "   " + m_sequent;
}

QStringList KNLogicDocument::renderLogicLine(int row)
{
    // Pick out the structure.
    const KNLogicLine &logicLine = m_lines.at(row);
    // Construct list.
    QStringList lineList;
    lineList.append(getAssumption(logicLine, row));
    lineList.append("("+QString::number(row+1)+")");
    lineList.append(logicLine.formula);
    lineList.append(getRule(logicLine));
    // Give back the result.
    return lineList;
}

bool KNLogicDocument::loadFromFile(const QString &filePath)
{
    // Load the file as UTF-8 content.
    QFile documentFile(filePath);
    if(!documentFile.open(QIODevice::ReadOnly))
    {
        // Failed to load the file.
        return false;
    }
    // Set the data.
    loadFromJson(documentFile.readAll());
    // Close file.
    documentFile.close();
    return true;
}

void KNLogicDocument::loadFromJson(const QByteArray &jsonText)
{
    // The document is well defined as a JSON format file.
    QJsonObject documentObject=QJsonDocument::fromJson(jsonText).object();
    // Parse the premise and sequent.
    m_premise=documentObject.value("premise").toString();
    m_sequent=documentObject.value("sequent").toString();
    // Parse the proof list.
    clearLines();
    // Start construction.
    QJsonArray linesData=documentObject.value("proof").toArray();
    // Check the lines size.
    if(linesData.isEmpty())
    {
        // Complete.
        return;
    }
    // Start inserting data.
    for(int i=0; i<linesData.size(); ++i)
    {
        // Construct the line.
        KNLogicLine line;
        QJsonArray lineData=linesData.at(i).toArray();
        // Check the data.
        if(lineData.size()!=LineDataCount)
        {
            //Invalid line data.
            continue;
        }
        // Check the assumption.
        QJsonArray assumption=lineData.at(LineAssumption).toArray();
        if(!assumption.isEmpty())
        {
            // Add the data.
            for(int j=0; j<assumption.size(); ++j)
            {
                // Append the tracing index.
                line.assumptions.append(index(assumption.at(j).toInt()-1,
                                              0));
            }
        }
        // Formula.
        line.formula=lineData.at(LineFormula).toString();
        // Rules.
        line.rule=lineData.at(LineRule).toInt();
        // Check the dependencies.
        QJsonArray dependencies=lineData.at(LineDependencies).toArray();
        if(!dependencies.isEmpty())
        {
            // Add the data.
            for(int j=0; j<dependencies.size(); ++j)
            {
                // Append the tracking index.
                QJsonArray dependency=dependencies.at(j).toArray();
                // Check denpendency size.
                if(dependency.size()!=2)
                {
                    // Error.
                    continue;
                }
                // Parse the logic use line.
                KNLogicUse useRule;
                useRule.index=index(dependency.at(0).toInt()-1, 0);
                QJsonArray notCares=dependency.at(1).toArray();
                for(int k=0; k<notCares.size(); ++k)
                {
                    useRule.notCare.append(index(notCares.at(k).toInt()-1,
                                                 0));
                }
                // Add the use rule.
                line.uses.append(useRule);
            }
        }
        // Insert the data.
        beginInsertRows(QModelIndex(), linesData.size(), linesData.size());
        m_lines.append(line);
        endInsertRows();
    }
}

inline void KNLogicDocument::clearLines()
{
    // Start to reset the entire model.
    beginResetModel();
    // Clear the lines.
    m_lines = QList<KNLogicLine>();
    // Complete.
    endResetModel();
}

inline QString KNLogicDocument::getAssumption(const KNLogicLine &logicLine,
                                              int lineRow) const
{
    // Check line rules.
    if(logicLine.rule==RuleAssumption)
    {
        return QString::number(lineRow+1);
    }
    // Combine the assumption line.
    QString assumptionText;
    for(int i=0; i<logicLine.assumptions.size(); ++i)
    {
        // Add comma.
        if(!assumptionText.isEmpty())
        {
            assumptionText.append(", ");
        }
        // Add current assumption row.
        assumptionText.append(getLineNumber(logicLine.assumptions.at(i)));
    }
    // Give back the assumption text.
    return assumptionText;
}

QString KNLogicDocument::getRule(const KNLogicLine &logicLine) const
{
    QString ruleLines;
    // Construct the rule lines.
    for(int i=0; i<logicLine.uses.size(); ++i)
    {
        const KNLogicUse &useRule=logicLine.uses.at(i);
        // Check rule lines data,
        if(!ruleLines.isEmpty())
        {
            // Add comma.
            ruleLines.append(", ");
        }
        // Append the data.
        ruleLines.append(getLineNumber(useRule.index));
        // Check the not care rows.
        if(useRule.notCare.isEmpty())
        {
            continue;
        }
        // Append not care rules.
        ruleLines.append("[");
        for(int j=0; j<useRule.notCare.size(); ++j)
        {
            // Add comma.
            if(j>0)
            {
                ruleLines.append(", ");
            }
            // Append line number.
            ruleLines.append(getLineNumber(useRule.notCare.at(j)));
        }
        ruleLines.append("]");
    }
    // Append the logic rule at the end.
    if(!ruleLines.isEmpty())
    {
        ruleLines.append("   ");
    }
    return ruleLines + knLogicGlobal->logicRule(logicLine.rule);
}

inline QString KNLogicDocument::getLineNumber(
        const QPersistentModelIndex &targetIndex) const
{
    // Add current assumption row.
    return targetIndex.isValid() ? QString::number(targetIndex.row()+1) :
                                   "?";
}
