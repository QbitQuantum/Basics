void VCSliderProperties::levelUpdateCapabilityNode(QTreeWidgetItem* parent,
						   QLCCapability* cap)
{
	QTreeWidgetItem* item;
	QString str;

	Q_ASSERT(parent != NULL);
	Q_ASSERT(cap != NULL);

	item = new QTreeWidgetItem(parent);
	item->setText(KColumnName, cap->name());
	item->setText(KColumnRange, str.sprintf("%.3d - %.3d",
						cap->min(), cap->max()));
	item->setFlags(item->flags() & (~Qt::ItemIsUserCheckable));
}