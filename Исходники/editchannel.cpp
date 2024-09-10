void EditChannel::refreshCapabilities()
{
	QListIterator <QLCCapability*> it(*m_channel->capabilities());
	QLCCapability* cap = NULL;
	QTreeWidgetItem* item = NULL;
	QString str;
	
	m_capabilityList->clear();
	
	/* Fill capabilities */
	while (it.hasNext() == true)
	{
		cap = it.next();

		item = new QTreeWidgetItem(m_capabilityList);
		
		// Min
		str.sprintf("%.3d", cap->min());
		item->setText(KColumnMin, str);

		// Max
		str.sprintf("%.3d", cap->max());
		item->setText(KColumnMax, str);
		
		// Name
		item->setText(KColumnName, cap->name());
		
		// Store the capability pointer to the listview as a string
		str.sprintf("%lu", (unsigned long) cap);
		item->setText(KColumnPointer, str);
	}
	
	m_capabilityList->sortItems(KColumnMin, Qt::AscendingOrder);
	
	slotCapabilityListSelectionChanged(m_capabilityList->currentItem());
}