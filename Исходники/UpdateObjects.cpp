void GameScreen::DefineDirectionToEnemyForObject(CLifeObject * object, const Vec2 & positionEnemy)
{
	Vec2 direction = positionEnemy - object->getPosition();

	direction.normalize();
	object->SetDirection(direction);
}