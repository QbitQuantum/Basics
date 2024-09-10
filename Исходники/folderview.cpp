void FolderView::invertSelection() {
  if(model_) {
    QItemSelectionModel* selModel = view->selectionModel();
    int rows = model_->rowCount();
    QItemSelectionModel::SelectionFlags flags = QItemSelectionModel::Toggle;
    if(mode == DetailedListMode)
      flags |= QItemSelectionModel::Rows;
    for(int row = 0; row < rows; ++row) {
      QModelIndex index = model_->index(row, 0);
      selModel->select(index, flags);
    }
  }
}