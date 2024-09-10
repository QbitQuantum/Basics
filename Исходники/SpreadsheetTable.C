void
SpreadsheetTable::selectAll()
{
    QModelIndex topLeft = model()->index(0,0);
    QModelIndex bottomRight = model()->index(model()->rowCount()-1, model()->columnCount()-1);
    QItemSelection selection;
    selection.select(topLeft, bottomRight);
    selectionModel()->select(selection, QItemSelectionModel::ClearAndSelect);
}