QList<QStandardItem*> DkFileAssociationsPreference::getItems(const QString& filter, bool browse, bool reg) {

	QList<QStandardItem* > items;
	QStandardItem* item = new QStandardItem(filter);
	item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	items.append(item);
	item = new QStandardItem("");
	//item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable);
	item->setCheckable(true);
	item->setCheckState(browse ? Qt::Checked : Qt::Unchecked);
	items.append(item);
	item = new QStandardItem("");
	//item->setFlags(Qt::Qt::ItemIsSelectable | Qt::ItemIsUserCheckable);
	item->setCheckable(true);
	item->setCheckState(reg ? Qt::Checked : Qt::Unchecked);
#ifndef Q_OS_WIN	// registering is windows only
	item->setEnabled(false);
#endif
	items.append(item);

	return items;

}