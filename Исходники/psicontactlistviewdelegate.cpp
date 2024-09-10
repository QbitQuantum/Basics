void PsiContactListViewDelegate::updateAlerts()
{
	Q_ASSERT(!alertingIndexes_.isEmpty());
	if (!contactList()->isVisible())
		return; // needed?

	QRect contactListRect = contactList()->rect();
	QHashIterator<QModelIndex, bool> it(alertingIndexes_);
	while (it.hasNext()) {
		it.next();
		QRect r = contactList()->visualRect(it.key());
		if (contactListRect.intersects(r)) {
			contactList()->dataChanged(it.key(), it.key());
		}
	}
}