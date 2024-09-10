void TagsDialog::on_edit_tag(const QModelIndex &index)
{
	if(!index.isValid())
		return;

	EditTagsDialog d(this);

	QString old_text =model_.item(index.row(), 1)->text();
	d.set_text(old_text);

	if(d.exec() == QInputDialog::Accepted)
	{
		QString new_text = d.get_text();
		if(old_text == new_text)
			return;

		if(new_text.isEmpty())
		{
			QMessageBox::critical(&d, "Name", "This name already exists in database");
			return;
		}

		for(int i=0; i<model_.rowCount(); ++i)
		{
			if(new_text == model_.item(i, 1)->text() && old_text != new_text)
			{
				QMessageBox::critical(&d, "Name", "This name already exists in database");
				return;
			}
		}

		QStandardItem* newitem = new QStandardItem(d.get_text());
		newitem->setFlags(newitem->flags() & ~Qt::ItemIsEditable);
		model_.setItem(index.row(), 1, newitem);
	}
}