void ComponentGrid::updateSeparators()
{
	mLines.clear();

	bool drawAll = Settings::getInstance()->getBool("DebugGrid");

	Eigen::Vector2f pos;
	Eigen::Vector2f size;
	for(auto it = mCells.begin(); it != mCells.end(); it++)
	{
		if(!it->border && !drawAll)
			continue;

		// find component position + size
		pos << 0, 0;
		size << 0, 0;
		for(int x = 0; x < it->pos.x(); x++)
			pos[0] += getColWidth(x);
		for(int y = 0; y < it->pos.y(); y++)
			pos[1] += getRowHeight(y);
		for(int x = it->pos.x(); x < it->pos.x() + it->dim.x(); x++)
			size[0] += getColWidth(x);
		for(int y = it->pos.y(); y < it->pos.y() + it->dim.y(); y++)
			size[1] += getRowHeight(y);

		if(it->border & BORDER_TOP || drawAll)
		{
			mLines.push_back(Vert(pos.x(), pos.y()));
			mLines.push_back(Vert(pos.x() + size.x(), pos.y()));
		}
		if(it->border & BORDER_BOTTOM || drawAll)
		{
			mLines.push_back(Vert(pos.x(), pos.y() + size.y()));
			mLines.push_back(Vert(pos.x() + size.x(), mLines.back().y));
		}
		if(it->border & BORDER_LEFT || drawAll)
		{
			mLines.push_back(Vert(pos.x(), pos.y()));
			mLines.push_back(Vert(pos.x(), pos.y() + size.y()));
		}
		if(it->border & BORDER_RIGHT || drawAll)
		{
			mLines.push_back(Vert(pos.x() + size.x(), pos.y()));
			mLines.push_back(Vert(mLines.back().x, pos.y() + size.y()));
		}
	}

	mLineColors.reserve(mLines.size());
	Renderer::buildGLColorArray((GLubyte*)mLineColors.data(), 0xC6C7C6FF, mLines.size());
}