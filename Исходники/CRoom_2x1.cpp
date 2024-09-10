bool CRoom_2x1::correctRoomCollision_down()
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

		// Here we are going to do a point collision detection on the extended midpoint
		//		from all of the sub rooms along the bottom row. If ANY of them collide with something,
		//		the respective corner is set, and this room will not fall any farther
		SCoords2<int> this_midBottomLeft, this_midBottomRight;
		this_midBottomLeft.setCoords(
		    m_bottomLeft.x + m_width / 4,
		    (int)(m_bottomLeft.y + m_sAtributes.velosity_y));
		this_midBottomRight.setCoords(
		    m_bottomRight.x - m_width / 4,
		    (int)(m_bottomLeft.y + m_sAtributes.velosity_y));

		bool collision_bottomLeft = pRoom->collision(&this_midBottomLeft);
		bool collision_bottomRight = pRoom->collision(&this_midBottomRight);

		if (collision_bottomLeft && collision_bottomRight) // dead on collision
		{
			setBottomLeft(other_topLeft);
			m_sAtributes.gravityTimer.start();
			isFalling = false;
			return true;
		}
		else if (collision_bottomLeft && !collision_bottomRight) // hanging off of the right side
		{
			if (pRoom->getLayout()->x == 1)
			{
				setBottomLeft(other_topLeft);
			}
			else if (pRoom->getLayout()->x == 2)
			{
				setBottomLeft(other_topLeft.x + pRoom->getWidth() / 2, other_topLeft.y);
			}

			m_sAtributes.gravityTimer.start();
			isFalling = false;
			return true;
		}
		else if (!collision_bottomLeft && collision_bottomRight) // hanging off of the left side
		{
			if (pRoom->getLayout()->x == 1)
			{
				setBottomRight(other_topRight);
			}
			else if (pRoom->getLayout()->x == 2)
			{
				setBottomRight(other_topLeft.x + pRoom->getWidth() / 2, other_topLeft.y);
			}

			m_sAtributes.gravityTimer.start();
			isFalling = false;
			return true;
		}
	}

	return false;
}