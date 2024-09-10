QTreeWidgetItem *SoundPage::addItem(QTreeWidgetItem *groupItem, const QString &name, const QString &event)
{
	QTreeWidgetItem *item = new QTreeWidgetItem(TYPE_ITEM);
	item->setData(COLUMN_DATA, ROLE_EVENT, event);
	item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
	item->setCheckState(COLUMN_NAME, soundManager->eventEnabled(event) ? Qt::Checked : Qt::Unchecked);
	item->setText(COLUMN_NAME, name);
	item->setText(COLUMN_FILENAME, soundManager->eventFilename(event));
	groupItem->addChild(item);

	return item;
}