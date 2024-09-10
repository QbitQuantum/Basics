void Entity::interactionWithEntity(vector<Entity> *enemys , int id , const float deltaTime)// ÈÑÏÐÀÂÜ for enity and mainPerson
{
	if (!wasCollision) {
		float &dx = movement.x;
		float &dy = movement.y;

		float x;
		float y;
		x = getXPos();
		y = getYPos();


		Sprite *spriteObject;
		FloatRect objectBound;

		int levelUnlifeObject;

		spriteEntity->move(movement);
		FloatRect entityBound = spriteEntity->getGlobalBounds();
		spriteEntity->move(-movement);


		vector<Entity> &objects = *enemys;
		for (int i = 0; i != objects.size(); ++i) {

			if (id != i) {
				levelUnlifeObject = objects[i].currentLevelFloor;

				spriteObject = objects[i].spriteEntity;
				objectBound = spriteObject->getGlobalBounds();


				if (entityBound.intersects(objectBound) && (levelUnlifeObject == currentLevelFloor)) {
					wasCollision = true;

					founds.findEnemy = &objects[i];
					directions.directionWalk = NONE_DIRECTION;
					break;
				}

			}

		}
	}
}