void GameWorld::addBall(int num)
{
	for (int i = 0;i < num;i++) {
		int type = i % 2 == 0 ? POSITIVE_BALL : NEGATIVE_BALL;
		//type = POSITIVE_BALL;
		Color4f color;
		switch (type)
		{
		case POSITIVE_BALL:
			color.red = 50/255.0;
			color.green = 225/255.0;
			color.blue = 50/255.0;
			break;
		case NEGATIVE_BALL:
			color.red = 100/255.0;
			color.green = 0;
			color.blue = 255/255.0;
			break;
		default:
			break;
		}
		double friction = 0.5;
		Vector3d direction;
		direction.x = rand() % 100;
		direction.z = rand() % 100;
		direction.y = 0.0;
		Vector3d position;
		position.x = rand() % 100;
		position.y = 5.0;
		position.z = rand() % 100;
		for (int j = 0;j < ballVector.size();j++) {
			Vector3d ballPos = ballVector[j].position;
			Vector3d deltpos = position - ballPos;
			if (deltpos.length() <= 10.0) {
				position.x = rand() % 100;
				position.y = 5.0;
				position.z = rand() % 100;
				break;
			}
		}
		Ball newball = Ball(5.0, friction, 60, direction,position, color, type);
		ballVector.push_back(newball);
	}
}