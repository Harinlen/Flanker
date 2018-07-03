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
#ifndef KNLOGICDOCUMENTVIEW_H
#define KNLOGICDOCUMENTVIEW_H

#include <QAbstractItemView>

class KNLogicDocument;
class KNLogicDocumentView : public QAbstractItemView
{
    Q_OBJECT
public:
    explicit KNLogicDocumentView(QWidget *parent = nullptr);

    /*!
     * \brief Reimplemented from QAbstractItemView::indexAt().
     */
    QModelIndex indexAt(const QPoint &point) const Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from QAbstractItemView::scrollTo().
     */
    void scrollTo(const QModelIndex &index,
                  ScrollHint hint = EnsureVisible) Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from QAbstractItemView::visualRect().
     */
    QRect visualRect(const QModelIndex &index) const Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from QAbstractItemView::setModel().
     */
    void setModel(QAbstractItemModel *model) Q_DECL_OVERRIDE;

signals:

public slots:

protected:
    /*!
     * \brief Reimplemented from QAbstractItemView::paintEvent().
     */
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from QAbstractItemView::resizeEvent().
     */
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from QAbstractItemView::moveCursor().
     */
    QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction,
                           Qt::KeyboardModifiers modifiers) Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from QAbstractItemView::horizontalOffset().
     */
    int horizontalOffset() const
    Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from QAbstractItemView::verticalOffset().
     */
    int verticalOffset() const
    Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from QAbstractItemView::isIndexHidden().
     */
    bool isIndexHidden(const QModelIndex &index) const
    Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from QAbstractItemView::setSelection().
     */
    void setSelection(const QRect &rect,
                      QItemSelectionModel::SelectionFlags command)
    Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from QAbstractItemView::visualRegionForSelection().
     */
    QRegion visualRegionForSelection(const QItemSelection &selection) const
    Q_DECL_OVERRIDE;

protected slots:
    /*!
     * \brief Reimplemented from QAbstractItemView::updateGeometries().
     */
    void updateGeometries() Q_DECL_OVERRIDE;

private:
    enum ViewColumns
    {
        ViewColumnAssumption,
        ViewColumnLineNumber,
        ViewColumnFormula,
        ViewColumnSpacing,
        ViewColumnRules,
        ViewColumnCount
    };

    enum ColumnStartPostions
    {
        StartPosAssumption,
        StartPosLineNumber,
        StartPosFormula,
        StartPosRules,
        StartPosEnd,
        StartPosCount
    };

    inline void scaleColumnSizeParameters();
    inline void updateScrollBar();
    inline void scaleSizeParameters();
    QVector<int> m_columnWidth, m_scaledColumnWidth, m_columnStart;
    QFontMetrics m_standardMetrics;
    qreal m_scaleFactor;

    KNLogicDocument *m_document;

    int m_titleSpacing, m_titleHeight, m_paperWidth, m_centralSpacing,
        m_paperSpacing, m_lineMargin, m_lineHeight;
};

#endif // KNLOGICDOCUMENTVIEW_H
