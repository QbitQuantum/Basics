void ComponentAIProjectile::update()
{
	/*if(!GameManager::getInstance()->getMapManager()->isEmpty(parent->position))
	{

		parent->kill();

	}*/
	Vector2d direction = parent->velocity;
	direction.normalize();
	parent->position += direction * (Math::random(-50,50)/100.0);
}