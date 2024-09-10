	bool BookmarksManagerDialog::CheckSave (const QModelIndex& index)
	{
		if (!index.isValid ())
			return false;

		if (!CurrentEditor_)
			return false;

		QStandardItem *item = BMModel_->itemFromIndex (index);
		if (!item)
			return false;

		QVariantMap oldMap = item->data ().toMap ();
		const QVariantMap& ourMap = CurrentEditor_->GetIdentifyingData ();
		if (!ourMap.contains ("AccountID"))
			oldMap.remove ("AccountID");

		if (oldMap == ourMap)
			return false;

		if (QMessageBox::question (this,
					tr ("Save the bookmark?"),
					tr ("You've changed the bookmark. Do you want to save the changes?"),
					QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
			return false;

		item->setData (ourMap);
		Save ();
		return true;
	}