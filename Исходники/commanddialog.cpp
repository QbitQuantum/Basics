void CommandTreeView::handleRowsRemoved(const QModelIndex &parent, int, int)
{
    if (parent.isValid())
        return;

    // Reselect the same row index of the removed row
    QItemSelectionModel *sModel = selectionModel();
    QModelIndex index = sModel->currentIndex();

    sModel->select(index.sibling(index.row() + 1,index.column()),
                   QItemSelectionModel::ClearAndSelect |
                   QItemSelectionModel::Rows);
}