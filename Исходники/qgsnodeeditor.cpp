void QgsNodeEditor::updateTableSelection()
{
  if ( mUpdatingNodeSelection )
    return;

  mUpdatingTableSelection = true;
  mTableView->selectionModel()->clearSelection();
  const QList<QgsVertexEntry*>& vertexMap = mSelectedFeature->vertexMap();
  int firstSelectedRow = -1;
  QItemSelection selection;
  for ( int i = 0, n = vertexMap.size(); i < n; ++i )
  {
    if ( vertexMap[i]->isSelected() )
    {
      if ( firstSelectedRow < 0 )
        firstSelectedRow = i;
      selection.select( mNodeModel->index( i, 0 ), mNodeModel->index( i, mNodeModel->columnCount() - 1 ) );
    }
  }
  mTableView->selectionModel()->select( selection, QItemSelectionModel::Select );

  if ( firstSelectedRow >= 0 )
    mTableView->scrollTo( mNodeModel->index( firstSelectedRow, 0 ), QAbstractItemView::PositionAtTop );

  mUpdatingTableSelection = false;
}