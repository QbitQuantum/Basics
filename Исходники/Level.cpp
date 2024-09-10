bool Level::isRegionEmpty(int x0, int y0, int x1, int y1)
{
	int xt0 = (x0 >> 4) - 1;
	int yt0 = (y0 >> 4) - 1;
	int xt1 = (x1 >> 4) + 1;
	int yt1 = (y1 >> 4) + 1;
	for (int y = yt0; y <= yt1; ++y)
	{
		if (y < 0 || y >= h) continue;
		int yByWidth = y * this->w;
		for (int x = xt0; x <= xt1; ++x)
		{
			if (x < 0  || x >= w) continue;
			list<Entity*> &ent = entitiesInTiles[x + yByWidth];
			if (ent.empty()) continue;
			for (list<Entity*>::iterator it = ent.begin(); it != ent.end(); it++ )
			{
				Entity * e = *it;
				if (e->intersects(x0, y0, x1, y1)) return false;
			}
		}
	}
	return true;
}