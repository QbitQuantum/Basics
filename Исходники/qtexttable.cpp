/*!
    \fn void QTextTable::removeColumns(int index, int columns)

    Removes a number of \a columns starting with the column at the specified
    \a index.

    \sa insertRows(), insertColumns(), removeRows(), resize(), appendRows(), appendColumns()
*/
void QTextTable::removeColumns(int pos, int num)
{
    Q_D(QTextTable);
//     qDebug() << "-------- removeCols" << pos << num;

    if (num <= 0 || pos < 0)
        return;
    if (d->dirty)
        d->update();
    if (pos >= d->nCols)
        return;
    if (pos + num > d->nCols)
        pos = d->nCols - num;

    QTextDocumentPrivate *p = d->pieceTable;
    QTextFormatCollection *collection = p->formatCollection();
    p->beginEditBlock();

    // delete whole table?
    if (pos == 0 && num == d->nCols) {
        const int pos = p->fragmentMap().position(d->fragment_start);
        p->remove(pos, p->fragmentMap().position(d->fragment_end) - pos + 1);
        p->endEditBlock();
        return;
    }

    p->aboutToRemoveCell(cellAt(0, pos).firstPosition(), cellAt(d->nRows - 1, pos + num - 1).lastPosition());

    QList<int> touchedCells;
    for (int r = 0; r < d->nRows; ++r) {
        for (int c = pos; c < pos + num; ++c) {
            int cell = d->grid[r*d->nCols + c];
            QTextDocumentPrivate::FragmentIterator it(&p->fragmentMap(), cell);
            QTextCharFormat fmt = collection->charFormat(it->format);
            int span = fmt.tableCellColumnSpan();
            if (touchedCells.contains(cell) && span <= 1)
                continue;
            touchedCells << cell;

            if (span > 1) {
                fmt.setTableCellColumnSpan(span - 1);
                p->setCharFormat(it.position(), 1, fmt);
            } else {
                // remove cell
                int index = d->cells.indexOf(cell) + 1;
                int f_end = index < d->cells.size() ? d->cells.at(index) : d->fragment_end;
                p->remove(it.position(), p->fragmentMap().position(f_end) - it.position());
            }
        }
    }

    QTextTableFormat tfmt = format();
    tfmt.setColumns(tfmt.columns()-num);
    QVector<QTextLength> columnWidths = tfmt.columnWidthConstraints();
    if (columnWidths.count() > pos) {
        columnWidths.remove(pos, num);
        tfmt.setColumnWidthConstraints (columnWidths);
    }
    QTextObject::setFormat(tfmt);

    p->endEditBlock();
//     qDebug() << "-------- end removeCols" << pos << num;
}