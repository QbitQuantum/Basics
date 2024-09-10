bool HistoryView::update() {

	int stRow = row(st->sha());
	if (stRow == -1)
		return false; // main/tree view asked us a sha not in history

	QModelIndex index = currentIndex();
	QItemSelectionModel* sel = selectionModel();

	if (index.isValid() && (index.row() == stRow)) {

		if (sel->isSelected(index) != st->selectItem())
			sel->select(index, QItemSelectionModel::Toggle);

		scrollTo(index);
	} else {
		// setCurrentIndex() does not clear previous
		// selections in a multi selection QListView
		clearSelection();

		QModelIndex newIndex = model()->index(stRow, 0);
		if (newIndex.isValid()) {

			// emits QItemSelectionModel::currentChanged()
			setCurrentIndex(newIndex);
			scrollTo(newIndex);
			if (!st->selectItem())
				sel->select(newIndex, QItemSelectionModel::Deselect);
		}
	}
	if (git->isMainHistory(fh))
		emit diffTargetChanged(row(st->diffToSha()));

	return currentIndex().isValid();
}