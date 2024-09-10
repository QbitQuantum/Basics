void ListingTable::updateData()
{
	QModelIndexList sel = selectionModel()->selectedRows();
	QList<unsigned int> selIds;

	for (QModelIndexList::iterator it = sel.begin() ; it != sel.end() ; it++) {
		QModelIndex idx = *it;
		selIds << model->getIndexID(idx);
	}

	QModelIndex cidx = currentIndex();
	unsigned int cidxId = model->getIndexID(cidx);

	model->updateData();

	QItemSelection newSel;

	unsigned int ns = 0;

	for (QList<unsigned int>::iterator it = selIds.begin() ; it != selIds.end() ; it++) {
		unsigned int id = *it;
		QModelIndex idx = model->getIndexWithID(id);

		if (idx.isValid()) {
			newSel.select(idx, model->index(idx.row(), model->columnCount()-1));
			ns++;
		}
	}

	selectionModel()->select(newSel, QItemSelectionModel::Select);

	cidx = model->getIndexWithID(cidxId);
	setCurrentIndex(cidx);

	if (!cidx.isValid()) {
		// There is no current part. One way this could happen is if parts were previously selected, but they were all
		// removed. In this case, setCurrentIndex(cidx) above was a no-op because the model was previously reset which
		// clears any current part selection WITHOUT EMITTING THE currentRowChanged SIGNAL! In this case, we have to emit
		// currentPartChanged() manually.
		emit currentPartChanged(INVALID_PART_ID);
	}

	if (!selectionModel()->hasSelection()) {
		// Same as above, but for selection.
		emit selectedPartsChanged(QList<unsigned int>());
	}
}