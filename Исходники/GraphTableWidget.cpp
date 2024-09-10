void GraphTableWidget::highlightElements(const std::set<unsigned int>& elementsToHighligh) {
  QItemSelectionModel *itemSelectionModel = new QItemSelectionModel(_tulipTableModel);

  for(int i = 0 ; i < _tulipTableModel->rowCount() ; ++i) {
    if(elementsToHighligh.find(_tulipTableModel->idForIndex(i))!=elementsToHighligh.end()) {
      itemSelectionModel->select(_tulipTableModel->index(i,0),QItemSelectionModel::Select| QItemSelectionModel::Rows);
    }
  }

  QItemSelectionModel *oldSelectionModel = selectionModel();
  setSelectionModel(itemSelectionModel);
  oldSelectionModel->deleteLater();
}