void game_list_frame::PopulateGameGrid(uint maxCols, const QSize& image_size)
{
	uint r = 0;
	uint c = 0;

	std::string selected_item = CurrentSelectionIconPath();

	delete m_xgrid;

	bool showText = m_Icon_Size_Str != GUI::gl_icon_key_small && m_Icon_Size_Str != GUI::gl_icon_key_tiny;

	if (m_Icon_Size_Str == GUI::gl_icon_key_medium)
	{
		m_xgrid = new game_list_grid(image_size, m_Margin_Factor, m_Text_Factor * 2, showText);
	}
	else
	{
		m_xgrid = new game_list_grid(image_size, m_Margin_Factor, m_Text_Factor, showText);
	}

	// Get number of things that'll be in grid and precompute grid size.
	int entries = 0;
	for (GUI_GameInfo game : m_game_data)
	{
		if (qstr(game.info.category) == category::disc_Game || qstr(game.info.category) == category::hdd_Game)
		{
			if (SearchMatchesApp(game.info.name, game.info.serial) == false)
			{
				continue;
			}
			++entries;
		}
	}

	// Edge cases!
	if (entries == 0)
	{ // For whatever reason, 0%x is division by zero.  Absolute nonsense by definition of modulus.  But, I'll acquiesce.
		return;
	}
	if (maxCols == 0)
	{
		maxCols = 1;
	}
	if (maxCols > entries)
	{
		maxCols = entries;
	}

	int needsExtraRow = (entries % maxCols) != 0;
	int maxRows = needsExtraRow + entries / maxCols;
	m_xgrid->setRowCount(maxRows);
	m_xgrid->setColumnCount(maxCols);

	for (uint i = 0; i < m_game_data.size(); i++)
	{
		if (SearchMatchesApp(m_game_data[i].info.name, m_game_data[i].info.serial) == false)
		{
			continue;
		}

		QString category = qstr(m_game_data[i].info.category);

		if (category == category::hdd_Game || category == category::disc_Game)
		{
			m_xgrid->addItem(m_game_data[i].pxmap, qstr(m_game_data[i].info.name), i, r, c);

			if (selected_item == m_game_data[i].info.icon_path) m_xgrid->setCurrentItem(m_xgrid->item(r, c));;

			if (++c >= maxCols)
			{
				c = 0;
				r++;
			}
		}
	}

	if (c != 0)
	{ // if left over games exist -- if empty entries exist
		for (int col = c; col < maxCols; ++col)
		{
			QTableWidgetItem* emptyItem = new QTableWidgetItem();
			emptyItem->setFlags(Qt::NoItemFlags);
			emptyItem->setData(Qt::UserRole, -1);
			m_xgrid->setItem(r, col, emptyItem);
		}
	}

	m_xgrid->resizeColumnsToContents();
	m_xgrid->resizeRowsToContents();
}