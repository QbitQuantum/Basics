void Projectile::update(const sf::Time& dt) {
	Entity::update(dt);

	if(!this->active) return;

	if(position->x < 0 || position->x > Settings::Width ||
			position->y < 0 || position->y > Settings::Height) {
		this->destroy();
		return;
	}

	std::vector<Entity*>* entities = Entity::getEntities();
	for(auto it = entities->begin(); it!=entities->end(); ++it) {
		Entity* e = *it;

		if(e->getID() == Entity::Type::Item)
			continue;

		if(e->getID() != Entity::Type::Projectile) {
			if(e->getTeam() != this->team)
				if(e->intersects(this)) {
					e->damage(30);
					if(e->isDead())
						ProjectileUtility::transferExp(10);
					this->destroy();
				}
		} else {
			//TODO: Projectile x Projectile collision. HIPPOPOTAMUS.
		}
	}
}