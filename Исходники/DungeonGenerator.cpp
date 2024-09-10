MapManager DungeonGenerator::Generate(const DungeonSize& sizeData, const DungeonData& dungeonData)
{
	MapManager manager;
	for (size_t i = 0; i < sizeData.DungeonHeight(); ++i)
	{
		for (size_t j = 0; j < sizeData.DungeonWidth(); ++j)
		{
			if (dungeonData.IsThis(ObjTypeOnMap::WALL, i, j))
			{
				auto wall = std::make_shared<Wall>(Wall(Vector2(j*GeneralConstant::img_size_width, i*GeneralConstant::img_size_height)));
				manager.Add(wall);
				continue;
			}
			if (dungeonData.IsThis(ObjTypeOnMap::FLOOR, i, j))
			{
				auto floor = std::make_shared<Floor>(Floor(Vector2(j*GeneralConstant::img_size_width, i*GeneralConstant::img_size_height)));
				manager.Add(floor);
				continue;
			}
			if (dungeonData.IsThis(ObjTypeOnMap::PATH, i, j))
			{
				auto path = std::make_shared<Path>(Path(Vector2(j*GeneralConstant::img_size_width, i*GeneralConstant::img_size_height)));
				manager.Add(path);
				continue;
			}
		}
	}

	return  manager;
}