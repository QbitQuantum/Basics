void Spit_projectile::Update(sf::Time DeltaTime){

	grav += gravity * DeltaTime.asSeconds();

	m_Sprite.move(direction.x * speed * DeltaTime.asSeconds(), direction.y * speed * DeltaTime.asSeconds() + grav*DeltaTime.asSeconds() - distGY*DeltaTime.asSeconds());


	if(this->checkCollisionPointInRadie(m_Sprite.getPosition(), player)){
		player->takeDamage();
		deleteMe = true;
	}

	spitAnim.update();

}