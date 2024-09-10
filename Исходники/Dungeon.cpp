int Dungeon::Step()
{
	int count = static_cast<int>(m_Rooms.size());

	if (m_State == State::CreateRooms)
	{
		if (count < RoomCount)
		{
			float radius = 150.0f;
			Vector2i position;
			GetPositionInCircle(radius, position);

			Vector2i dimensions;
			dimensions.X = m_Random.NextInt(4, 12);
			dimensions.Y = m_Random.NextInt(4, 12);

			m_Rooms.push_back(Room(
				position,
				dimensions,
				m_Random.NextInt(50, 250),
				m_Random.NextInt(50, 250),
				m_Random.NextInt(50, 250)
			));
		}
		else
		{
			m_State = State::SeparateRooms;
		}
	}
	else if (m_State == State::SeparateRooms)
	{
		bool hasCollisions = false;

		for (int i = 0; i < count; ++i)
		{
			for (int j = 0; j < count; ++j)
			{
				if (i == j) continue;

				const Vector2i& positionA = m_Rooms[i].GetPosition();
				const Vector2i& dimensionsA = m_Rooms[i].GetDimensions();
				const Vector2i& positionB = m_Rooms[j].GetPosition();
				const Vector2i& dimensionsB = m_Rooms[j].GetDimensions();

				Vector2i vector;
				if (Math::Intersect(positionA, dimensionsA, positionB, dimensionsB, vector))
				{
					int size = static_cast<int>(fmaxl(vector.X, vector.Y)) / Tile::Size;
					int adj = (size % 2 != 0) ? 1 : 0;

					if (vector.X != 0)
					{
						m_Rooms[i].Move((size / 2) * Tile::Size, 0);
						m_Rooms[j].Move((size / 2 + adj) * -Tile::Size, 0);
					}
					else if (vector.Y != 0)
					{
						m_Rooms[i].Move(0, (size / 2) * Tile::Size);
						m_Rooms[j].Move(0, (size / 2 + adj) * -Tile::Size);
					}

					hasCollisions = true;
				}
			}
		}

		if (!hasCollisions)
		{
			m_State = State::PickRooms;
		}
	}
	else if (m_State == State::PickRooms)
	{
	}
	else if (m_State == State::Triangulation)
	{
	}
	else if (m_State == State::MinimumSpanningTree)
	{
	}
	else if (m_State == State::CreateHallways)
	{
	}

	return 0;
}