void ObjectsView::synchronizeSelectedItems()
{
    Q_ASSERT(!mSynching);
    Q_ASSERT(mMapDocument);

    QItemSelection itemSelection;

    for (MapObject *o : mMapDocument->selectedObjects()) {
        QModelIndex index = mProxyModel->mapFromSource(mapObjectModel()->index(o));
        itemSelection.select(index, index);
    }

    mSynching = true;
    selectionModel()->select(itemSelection,
                             QItemSelectionModel::Select |
                             QItemSelectionModel::Rows |
                             QItemSelectionModel::Clear);
    mSynching = false;
}