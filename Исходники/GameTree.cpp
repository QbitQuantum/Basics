void DGameTree::AddGame(GameFile* item)
{
	if (m_items.values().contains(item))
		return;

	QString folder = item->GetFolderName();
	if (!m_path_nodes.contains(folder))
	{
		QTreeWidgetItem* i = new QTreeWidgetItem;
		i->setText(0, folder);
		m_path_nodes.insert(folder, i);
		if (m_current_style == STYLE_TREE)
			addTopLevelItem(i);
	}

	QTreeWidgetItem* i = new QTreeWidgetItem;
	i->setIcon(COL_TYPE, QIcon(Resources::GetPlatformPixmap(item->GetPlatform())));
	i->setIcon(COL_BANNER, QIcon(item->GetBitmap()));
	i->setText(COL_TITLE, item->GetName(true));
	i->setText(COL_DESCRIPTION, item->GetDescription());
	i->setIcon(COL_REGION, QIcon(Resources::GetRegionPixmap(item->GetCountry())));
	i->setText(COL_SIZE, NiceSizeFormat(item->GetFileSize()));
	i->setIcon(COL_STATE, QIcon(Resources::GetRatingPixmap(item->GetEmuState())));
	if (item->IsCompressed())
	{
		for (int col = 0; col < columnCount(); col++)
			i->setTextColor(col, QColor("#00F"));
	}
	m_items.insert(i, item);

	RebuildTree(); // TODO: only call this once per group of items added
}