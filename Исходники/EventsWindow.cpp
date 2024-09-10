void EventsWindow::cursorIndexUpdated()
{
    const int row = m_modelEventsCursor->index();

    QItemSelectionModel *selectionModel = m_resultsView->selectionModel();
    const QModelIndexList selectedIndexes = selectionModel->selectedIndexes();
    if (selectedIndexes.count() == 1 && selectedIndexes.at(0).row() == row)
        return;

    selectionModel->select(m_resultsView->model()->index(row, 0), QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
}