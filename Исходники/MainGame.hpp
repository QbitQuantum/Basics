	bool TestPlatCollision(sf::IntRect rect)
	{
		for (int i = 0; i < tiles.size(); i++)
			for (int j = 0; j < tiles[i].size(); j++)
				if (rect.intersects(tiles[i][j]->Rect()) && tiles[i][j]->IsSolid)
					return true;
		return false;
	}