void MList::selectItem(const QModelIndex &index)
{
    QItemSelectionModel *sModel = selectionModel();

    if (index.isValid() && sModel->model() != index.model()) {
        qWarning("MList::selectItem() failed: "
                 "Trying to select an item that is for"
                 " a different model than the view ");
        return;
    }

    if (sModel != NULL) {
        if (selectionMode() == MList::MultiSelection) {
            if (sModel->isSelected(index)) {
                sModel->select(index, QItemSelectionModel::Deselect);
            } else {
                sModel->select(index, QItemSelectionModel::Select);
            }
        } else if (selectionMode() == MList::SingleSelection) {
            sModel->select(index, QItemSelectionModel::ClearAndSelect);
        }
    }

    emit itemClicked(index);
}