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
#include <QScrollBar>
#include <QPainter>

#include "knlogicdocument.h"
#include "knthememanager.h"

#include "knlogicdocumentview.h"

#include <QDebug>

// All the parameters are set to be 100%.
#define DocumentWidth           800
#define DocumentColumnSpacing   11
#define DocumentAssumptionWidth 31
#define DocumentLineNumWidth    32
#define DocumentFormulaWidth    98
#define DocumentEmptyWidth      43
#define DocumentRuleWidth       78
#define DocumentTitleSpacing    40
#define DocumentFontHeight      16
#define DocumentLineMargin      3

KNLogicDocumentView::KNLogicDocumentView(QWidget *parent) :
    QAbstractItemView(parent),
    m_columnWidth(QVector<int>(ViewColumnCount)),
    m_scaledColumnWidth(QVector<int>(ViewColumnCount)),
    m_columnStart(QVector<int>(StartPosCount)),
    m_standardMetrics(QFontMetrics(QFont())),
    m_scaleFactor(1.0),
    m_document(nullptr),
    m_titleSpacing(0),
    m_titleHeight(0),
    m_paperWidth(0),
    m_centralSpacing(0),
    m_paperSpacing(0),
    m_lineMargin(0),
    m_lineHeight(0)
{
    setObjectName("DocumentView");
    // Set properties.
    setFrameStyle(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // Set the 100% time font data.
    QFont standardFont;
    standardFont.setFamily("Georgia");
    standardFont.setPixelSize(DocumentFontHeight);
    setFont(standardFont);
    m_standardMetrics=QFontMetrics(standardFont);
    // Reset the default column width.
    m_columnWidth.replace(0, DocumentAssumptionWidth);
    m_columnWidth.replace(1, DocumentLineNumWidth);
    m_columnWidth.replace(2, DocumentFormulaWidth);
    m_columnWidth.replace(3, DocumentEmptyWidth);
    m_columnWidth.replace(4, DocumentRuleWidth);
    // Reset all column width.
    scaleSizeParameters();
    // Register the view.
    knTheme->registerWidget(this);
}

QModelIndex KNLogicDocumentView::indexAt(const QPoint &point) const
{
    // Check model existance.
    if(!m_document)
    {
        // Always invalid index.
        return QModelIndex();
    }
    // Recast the point to the paper position.
    int x=point.x()+horizontalScrollBar()->value()
            -m_paperSpacing-m_centralSpacing;
    if(x<0 || x>m_columnStart.at(StartPosEnd))
    {
        // X out of range.
        return QModelIndex();
    }
    int y=point.y()+verticalScrollBar()->value()-m_titleHeight;
    if(y<0)
    {
        // Y out of range.
        return QModelIndex();
    }
    // Calculate the position.
    int row = y / m_lineHeight;
    // Check the column.
    for(int column=0; column<StartPosEnd; ++column)
    {
        if(x < m_scaledColumnWidth.at(column+1))
        {
            // Find the column.
            return m_document->index(row, column);
        }
    }
    // All the other are invalid, shounldn't go here.
    return QModelIndex();
}

void KNLogicDocumentView::scrollTo(const QModelIndex &index,
                                   QAbstractItemView::ScrollHint hint)
{
    //! FIXME
    ;
}

QRect KNLogicDocumentView::visualRect(const QModelIndex &index) const
{
    if(!m_document || !index.isValid() || index.column()==ViewColumnSpacing)
    {
        // Invalid index, invalid rect.
        return QRect();
    }
    // Calculate the index position.
    int columnIndex = (index.column() > ViewColumnSpacing) ?
                            (index.column()-1) :
                            index.column();
    // Calculate the position.
    int contentX=m_columnStart.at(columnIndex)+m_paperSpacing+m_centralSpacing-
            horizontalScrollBar()->value();
    return QRect(contentX,
                 index.row() * m_lineHeight + m_titleHeight
                 - verticalScrollBar()->value(),
                 m_columnWidth.at(columnIndex),
                 m_lineHeight);
}

void KNLogicDocumentView::setModel(QAbstractItemModel *model)
{
    // Check the original document setting.
    if(m_document)
    {
        // Remove the original configuration.
        ;
    }
    // Save the model as the document.
    m_document=static_cast<KNLogicDocument *>(model);
    // Set the model.
    QAbstractItemView::setModel(m_document);
}

void KNLogicDocumentView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    // Initial the painter.
    QPainter painter(viewport());
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::TextAntialiasing |
                           QPainter::SmoothPixmapTransform);
    // Fill the paper.
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRect(m_paperSpacing, 0, m_paperWidth, height());
    // Check the model pointer.
    if(!m_document)
    {
        // No model, ignore rendering.
        return;
    }
    // Draw the other content.
    int paperLeft = m_paperSpacing - horizontalScrollBar()->value(),
            paperTop = -verticalScrollBar()->value();
    // Rendering the title.
    painter.setPen(Qt::black);
    QFont italicFont=font();
    italicFont.setItalic(true);
    if(verticalScrollBar()->value() < m_titleHeight)
    {
        // Render the title.
        painter.drawText(paperLeft, paperTop, m_paperWidth, m_titleHeight,
                         Qt::AlignCenter,
                         m_document->title());
    }
    // Rendering the model data.
    paperTop += m_titleHeight;
    int currentRow = 0, currentY = paperTop;
    if(paperTop<0)
    {
        // Calculate the row.
        currentRow = -(paperTop / m_lineHeight);
    }
    // Calculate the column start position.
    QVector<int> columnStart(StartPosCount);
    for(int i=0; i<StartPosCount; ++i)
    {
        // Update the column start.
        columnStart.replace(i, m_columnStart.at(i)+paperLeft+m_centralSpacing);
    }
    // Rendering lines.
    while(currentRow<m_document->rowCount())
    {
        // Get the row data.
        QStringList logicLineData=m_document->renderLogicLine(currentRow);
        // Rendering line.
        // Assumption.
        painter.drawText(columnStart.at(StartPosAssumption),
                         currentY,
                         m_scaledColumnWidth.at(ViewColumnAssumption),
                         m_lineHeight,
                         Qt::AlignVCenter | Qt::AlignRight,
                         logicLineData.at(KNLogicDocument::ColumnAssumption));
        // Line Number.
        painter.drawText(columnStart.at(StartPosLineNumber),
                         currentY,
                         m_scaledColumnWidth.at(ViewColumnLineNumber),
                         m_lineHeight,
                         Qt::AlignVCenter,
                         logicLineData.at(KNLogicDocument::ColumnLineNumber));
        // Formula.
        painter.setFont(italicFont);
        painter.drawText(columnStart.at(StartPosFormula),
                         currentY,
                         m_scaledColumnWidth.at(ViewColumnFormula),
                         m_lineHeight,
                         Qt::AlignVCenter,
                         logicLineData.at(KNLogicDocument::ColumnFormula));
        painter.setFont(font());
        // Dependencies.
        painter.drawText(columnStart.at(StartPosRules),
                         currentY,
                         m_scaledColumnWidth.at(ViewColumnRules),
                         m_lineHeight,
                         Qt::AlignVCenter,
                         logicLineData.at(KNLogicDocument::ColumnRule));

        painter.drawRect(visualRect(m_document->index(currentRow, 4)));

        // Move to next row.
        currentY += m_lineHeight;
        // Increase row.
        ++currentRow;
    }
}

void KNLogicDocumentView::resizeEvent(QResizeEvent *event)
{
    QAbstractItemView::resizeEvent(event);
    // Update the scale parameters.
    updateScrollBar();
}

QModelIndex KNLogicDocumentView::moveCursor(
        QAbstractItemView::CursorAction cursorAction,
        Qt::KeyboardModifiers modifiers)
{
    //! FIXME
    return QModelIndex();
}

int KNLogicDocumentView::horizontalOffset() const
{
    return horizontalScrollBar()->value();
}

int KNLogicDocumentView::verticalOffset() const
{
    return verticalScrollBar()->value();
}

bool KNLogicDocumentView::isIndexHidden(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return false;
}

void KNLogicDocumentView::setSelection(
        const QRect &rect,
        QItemSelectionModel::SelectionFlags command)
{
    //!FIXME
    ;
}

QRegion KNLogicDocumentView::visualRegionForSelection(
        const QItemSelection &selection) const
{
    //!FIXME
    return QRegion();
}

void KNLogicDocumentView::updateGeometries()
{
    //!FIXME
    ;
}

inline void KNLogicDocumentView::scaleColumnSizeParameters()
{
    // Set the width vector.
    m_scaledColumnWidth=QVector<int>(ViewColumnCount);
    for(int i=0; i<ViewColumnCount; ++i)
    {
        // Update the scaled width.
        m_scaledColumnWidth.replace(i,
                                    m_scaleFactor*(qreal)m_columnWidth.at(i));
    }
    // Update the column start position.
    m_columnStart=QVector<int>(StartPosCount);
    int columnSpacing=m_scaleFactor*(qreal)DocumentColumnSpacing,
        columnStart=0;
    // Assumptions.
    m_columnStart.replace(0, columnStart);
    // Line Number.
    columnStart+=m_scaledColumnWidth.at(ViewColumnAssumption)+columnSpacing;
    m_columnStart.replace(1, columnStart);
    // Formula
    columnStart+=m_scaledColumnWidth.at(ViewColumnLineNumber)+columnSpacing;
    m_columnStart.replace(2, columnStart);
    // Rule
    columnStart+=m_scaledColumnWidth.at(ViewColumnFormula)+columnSpacing+
                 m_scaledColumnWidth.at(ViewColumnSpacing)+columnSpacing;
    m_columnStart.replace(3, columnStart);
    // End
    columnStart+=m_scaledColumnWidth.at(ViewColumnRules);
    m_columnStart.replace(4, columnStart);
    // Update the left and right spacing.
    m_centralSpacing=(m_paperWidth-columnStart)>>1;
}

inline void KNLogicDocumentView::updateScrollBar()
{
    // Update the left spacing.
    int paperLeftWidth=width()-m_paperWidth;
    if(paperLeftWidth<0)
    {
        // Clear the paper spacing.
        m_paperSpacing=0;
        // Update the horizontal scroll bar.
        horizontalScrollBar()->setRange(0, -paperLeftWidth);
    }
    else
    {
        // Update the paper spacing.
        m_paperSpacing=paperLeftWidth>>1;
        // Clear the horizontal scroll bar.
        horizontalScrollBar()->setRange(0, 0);
    }
}

inline void KNLogicDocumentView::scaleSizeParameters()
{
    // Update font height.
    QFont scaledFont=font();
    scaledFont.setPixelSize(m_scaleFactor*(qreal)DocumentFontHeight);
    setFont(scaledFont);
    // Set the title spacing.
    m_titleSpacing=m_scaleFactor*(qreal)DocumentTitleSpacing;
    m_titleHeight=(m_titleSpacing<<1)+scaledFont.pixelSize();
    // Set the paper width.
    m_paperWidth=m_scaleFactor*(qreal)DocumentWidth;
    // Set the line height.
    m_lineMargin=m_scaleFactor*(qreal)DocumentLineMargin;
    m_lineHeight=scaledFont.pixelSize()+(m_lineMargin<<1);
    // Update the column positions.
    scaleColumnSizeParameters();
    // Update the scroll bar.
    updateScrollBar();
}
