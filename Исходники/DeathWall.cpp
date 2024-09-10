bool DeathWall::checkIfHitDeathBlock(sf::IntRect playerRect){
	for(Wall::size_type i = 0; i < deathWall.size(); i++){
		sf::IntRect rect;
		rect.left = static_cast <int>(deathWall[i]->getX());
		rect.top = static_cast <int>(deathWall[i]->getY());
		rect.width = static_cast <int>(deathWall[i]->getWidth());
		rect.height = static_cast <int>(deathWall[i]->getHeight());

		if(playerRect.intersects(rect))
			return true;
	}
	return false;
}