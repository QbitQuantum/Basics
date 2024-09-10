void ThumbView::invertSelection()
{
	QItemSelection toggleSelection;
	QModelIndex firstIndex = thumbViewModel->index(0, 0);
	QModelIndex lastIndex = thumbViewModel->index(thumbViewModel->rowCount() - 1, 0);
	toggleSelection.select(firstIndex, lastIndex);
	selectionModel()->select(toggleSelection, QItemSelectionModel::Toggle);
}