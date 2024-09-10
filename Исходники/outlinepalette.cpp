void OutlineWidget::selectItems(QList<QTreeWidgetItem*> items)
{
	QItemSelection itemSelection;
	for (int i = 0; i < items.count(); ++i)
	{
		QModelIndex index = this->indexFromItem(items.at(i));
		if (index.isValid())
		{
			itemSelection.select(index, index);
		}
	}
	selectionModel()->select(itemSelection, QItemSelectionModel::Select);
}