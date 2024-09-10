void NMGMeasureListWidget::selectAllItems(QAbstractItemModel* model, 
                                          QItemSelectionModel* selectionModel,
                                          const QModelIndex& parent)
{
  if(model->hasChildren(parent))
  {
    if(selectionModel->isSelected(parent))
    {
      // this is done because of the removeSelectedItems() behaviour and the signals emitted,
      // to avoid extra signaling (e.g. extra parent deletion signal done by 
      // removeSelectedItems() due to no more children).
      selectionModel->select(parent, QItemSelectionModel::Deselect);
    }
    QModelIndex topLeft = model->index(0, 0, parent);
    QModelIndex bottomRight = model->index(model->rowCount(parent)-1, 
                                           model->columnCount(parent)-1, parent);
    QItemSelection selection;
    selection.select(topLeft, bottomRight);    
    selectionModel->select(selection, QItemSelectionModel::Select | QItemSelectionModel::Rows);
    
    QModelIndexList selectedIndexes = selection.indexes();
    QModelIndexList::const_iterator it;
    for(it = selectedIndexes.constBegin(); it != selectedIndexes.constEnd(); it++)
    {
      selectAllItems(model, selectionModel, *it);
    }
  }
}