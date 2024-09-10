void FrogShip::update(double deltaTime, PlayerShip* player, vector<Bullet*>& liveBullets) {
	
	GameObject::updateDebug(deltaTime);
	timeAlive += deltaTime;

	double percent = timeAlive / TIME_TO_CLIMAX;
	percent = 1 - cos(percent*XM_PIDIV2);
	double rt = 1 - percent;
	position = camera.screenToWorld(float(rt*rt)*startPos + 2 * float(rt*percent)*controlPoint
		+ float(percent*percent)*climaxPos);

	if (percent > .25) {
		// start aiming at player
		Vector2 dirToPlayer = player->getCenter() - position;
		dirToPlayer.Normalize();

		float angleToPlayer = atan2(dirToPlayer.y, dirToPlayer.x) + XM_PIDIV2;
		dirToPlayer = Vector2(cos(angleToPlayer), sin(angleToPlayer));
		//dirToPlayer += Vector2(cos(XM_PIDIV2), sin(XM_PIDIV2));
		Vector2 currentRot(cos(rotation), sin(rotation));

		currentRot += (dirToPlayer - currentRot) * float(deltaTime * rotationSpeed);
		setRotation(atan2(currentRot.y, currentRot.x));


		if (timeAlive >= TIME_TO_FIRE && closeEnough(dirToPlayer, currentRot)) {
			for (auto const& weapon : weaponSystems) {
				weapon->timeSinceFired += deltaTime;
				weapon->updatePosition(position);
				if (weapon->ready()) {
					weapon->fired = true;
					Bullet* bullet = weapon->launchBullet(player->getCenter());
					liveBullets.push_back(bullet);
				}
			}
		}
	}

	if (position.y > camera.screenToWorld(Vector2(0, float(camera.viewportHeight + 120))).y) {
		reset();
	}
}