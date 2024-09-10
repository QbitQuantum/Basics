void ccDBRoot::unselectEntity(ccHObject* obj)
{
	if (obj && obj->isSelected())
	{
		QModelIndex objIndex = index(obj);
		if (objIndex.isValid())
		{
			QItemSelectionModel* selectionModel = m_dbTreeWidget->selectionModel();
			assert(selectionModel);
			selectionModel->select(objIndex,QItemSelectionModel::Deselect);
		}
	}
}