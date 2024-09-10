void MonsterEntity::update(sf::Time delta) {
	timer += delta.asSeconds();
	if (timer > .5) {
		swapAppearance();
		timer = 0;
	}
	if (type == monster_flyer) {
		move(velocity * delta.asSeconds());
	} else if (type == monster_crawler) {
		velocity.y += (gravity.y * delta.asSeconds());
		velocity.x -= (gravity.y * delta.asSeconds());
		move(velocity * delta.asSeconds());
	}
}