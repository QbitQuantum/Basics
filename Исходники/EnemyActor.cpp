void EnemyActor::update(const sf::Time& delta_t)
{
	Actor::update(delta_t);
	
	if(delta_t.asSeconds() == 0.0)
		return;
		
	if (getState() == EnemyActor::Patrol || getState() == EnemyActor::Follow)
		patrolTimer -= delta_t.asSeconds();
	if (getState() == EnemyActor::Patrol && patrolTimer <= 0.0) {
		setNeedSeek(true);
		patrolTimer = patrolTimerMin;
	}
}