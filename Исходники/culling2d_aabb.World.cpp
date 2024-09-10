	std::vector<Object*> &World::GetCullingObjects(RectF cullingRange)
	{
		tempObjects.clear();

		for (int r = 0; r <= resolution; ++r)
		{
			auto layer = layers[r];

			auto cellSize = layer->GetGrids()[0]->GetGridRange().GetSize();

			//分解能0の場合はワールド全部を探索
			RectF searchRange = (r != 0) ? RectF(cullingRange.X - cellSize.X / 2, cullingRange.Y - cellSize.Y / 2, cullingRange.Width + cellSize.X, cullingRange.Height + cellSize.Y)
				: layer->GetGrids()[0]->GetGridRange();

			Vector2DI upperLeft;
			Vector2DI lowerRight;

			//カリング対象のグリッド区間絞込
			{
				Vector2DF upperLeftRaw = (searchRange.GetPosition() - worldRange.GetPosition()) / cellSize;
				Vector2DF lowerRightRaw = (searchRange.GetPosition() + searchRange.GetSize() - worldRange.GetPosition()) / cellSize;

				upperLeftRaw.X = Max(0.0f, upperLeftRaw.X);
				upperLeftRaw.Y = Max(0.0f, upperLeftRaw.Y);

				lowerRightRaw.X = Min(worldRange.GetSize().X / cellSize.X - 1.0f, lowerRightRaw.X);
				lowerRightRaw.Y = Min(worldRange.GetSize().Y / cellSize.Y - 1.0f, lowerRightRaw.Y);

				upperLeft = Vector2DI((int)floor(upperLeftRaw.X), (int)floor(upperLeftRaw.Y));
				lowerRight = Vector2DI((int)floor(lowerRightRaw.X), (int)floor(lowerRightRaw.Y));
			}

			int xSize = 1 << r;

			for (int x = upperLeft.X; x <= lowerRight.X; ++x)
			{
				for (int y = upperLeft.Y; y <= lowerRight.Y; ++y)
				{
					auto grid = layer->GetGrids()[y*xSize + x];

					grid->GetCullingObjects(searchRange, tempObjects);
				}
			}
		}
		std::sort(tempObjects.begin(), tempObjects.end(), [](Object* obj1, Object* obj2)
		{
			return obj1->GetSortedKey() < obj2->GetSortedKey();
		});
		return tempObjects;
	}