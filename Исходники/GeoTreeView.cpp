void GeoTreeView::selectionChangedFromOutside( const QItemSelection &selected,
                                               const QItemSelection &deselected )
{
    QItemSelectionModel* selModel = this->selectionModel();

    selModel->blockSignals(true);
    selModel->select(deselected, QItemSelectionModel::Deselect);
    selModel->select(selected, QItemSelectionModel::Select);
    selModel->blockSignals(false);

    QTreeView::selectionChanged(selected, deselected);
}