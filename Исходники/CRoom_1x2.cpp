bool CRoom_1x2::correctRoomCollision_down()
{
	for (int i = 0; i < m_pRoom_collision->size(); ++i)
	{
		CRoom* pRoom = m_pRoom_collision->at(i);

		if (this->equals(pRoom))
		{
			continue;
		}

		SCoords2<int> other_topLeft;
		SCoords2<int> other_topRight;
		SCoords2<int> other_bottomLeft;
		SCoords2<int> other_bottomRight;
		pRoom->getEverything(&other_topLeft, &other_topRight, &other_bottomLeft, &other_bottomRight);

		// Point collision detection extended from the midpoint on the bottom row
		SCoords2<int> midBottom;
		midBottom.setCoords(m_bottomLeft.x + m_width / 2, (int)(m_bottomLeft.y + m_sAtributes.velosity_y));
		if (pRoom->collision(&midBottom))
		{
			if (pRoom->getLayout()->x == 1)
			{
				setBottomRight(other_topRight.x, other_topRight.y);
			}
			else if (pRoom->getLayout()->x == 2)
			{
				SCoords2<int> subRoom = pRoom->whichSubRoom(&midBottom);

				if (subRoom.x == 1) // left side
				{
					setBottomLeft(other_topLeft.x, other_topLeft.y);
				}
				else if (subRoom.x == 2) // right side
				{
					setBottomRight(other_topRight.x, other_topRight.y);
				}
			}
			m_sAtributes.gravityTimer.start();
			isFalling = false;
			return true;
		}
	}

	return false;
}