Vector2* MobileEntity::getMovementDirection() {
	Vector2* moveDirection = new Vector2(endPos->getX() - currentPos->getX(),
			endPos->getY() - currentPos->getY());

	if (moveDirection->getNorm() == 0) {
		return moveDirection;
	}

	moveDirection->normalize();

	return moveDirection;
}