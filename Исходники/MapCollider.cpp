sf::Vector2f MapCollider::tryMove(sf::Vector2f position, sf::Vector2f velocity, sf::FloatRect collisionBox)
{
	sf::Vector2f newPos = position;
	int oldX = newPos.x;
	int oldY = newPos.y;

	//check if box is outside of the screen.
	if (newPos.x  - collisionBox.width / 2 < 0)
	{ 
		newPos.x = collisionBox.width / 2;
	}
	if (newPos.y - collisionBox.height / 2 < 0)
	{
		newPos.y = collisionBox.height / 2;
	}
	if (newPos.x + collisionBox.width / 2 > mMap->getWidth() * tileSize)
	{
		newPos.x = (mMap->getWidth() * tileSize) - collisionBox.width / 2;
	}
	if (newPos.y + collisionBox.height / 2 > mMap->getHeight() * tileSize)
	{
 		newPos.y = (mMap->getHeight() * tileSize) - collisionBox.height / 2;
	}

	collisionBox.left = newPos.x - collisionBox.width / 2;
	collisionBox.top = newPos.y - collisionBox.height / 2;


	for (int iterY = (newPos.y - collisionBox.height / 2) / tileSize; iterY < (newPos.y + collisionBox.height / 2) / tileSize; iterY++)
	{
		for (int iterX = (newPos.x- collisionBox.width / 2) / tileSize; iterX < (newPos.x + collisionBox.width / 2) / tileSize; iterX++)
		{
			//If tile is outside of the collisionMap, ignore that tile
			if (iterX < 0 || iterX >= mMap->getWidth() ||
				iterY < 0 || iterY >= mMap->getHeight())
				continue;

			if ((*mMap)[iterX][iterY].getCollibable() == false)
				continue;

			sf::FloatRect tileBox = getRectFromTile(iterX, iterY);
			sf::FloatRect interRect;

			if (collisionBox.intersects(tileBox, interRect))
			{
				sf::Vector2f distance = distanceRectToRect(tileBox, collisionBox);
				sf::Vector2f major = getMajorVector(distance);

				//this tile is an internal edge if the next tile is also collidable.
				//if this tile is NOT such a tile, then handle collision.
				int nextTileX = iterX + major.x;
				int nextTileY = iterY + major.y;
				if ((*mMap)[nextTileX][nextTileY].getCollibable() == false)
				{
					//do not be tempted to use interRect, it won't move the position excactly right.
					if (major.x < -.5)
					{
						newPos.x = tileBox.left - collisionBox.width / 2;
						collisionBox.left = newPos.x - collisionBox.width / 2;
					}
					else if (major.x > .5)
					{
						newPos.x = tileBox.left + tileBox.width + collisionBox.width / 2;
						collisionBox.left = newPos.x - collisionBox.width / 2;
					}
					else if (major.y < -.5)
					{
						newPos.y = tileBox.top - collisionBox.height / 2;
						collisionBox.top = newPos.y - collisionBox.height / 2;

					}
					else if (major.y > .5)
					{
						newPos.y = tileBox.top + tileBox.height + collisionBox.height / 2;
						collisionBox.top = newPos.y - collisionBox.height / 2;
					}
				}
			
			}
		}
	}

	
	return newPos;
}