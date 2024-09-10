void Virus::update() {
  double maxSpeed = 0.2;
  double maxAccel = 0.1;

  switch (virusData->getBodyType()) {
  case VIRUS_BODYTYPE_WORM:
    maxSpeed = virusData->getMovementSpeed();
    maxAccel = 0.012;
    if (gotDestination && state == VIRUSSTATE_MOVING) {
      Vector direction = Vector(position, destination);
      direction = direction.normalize();

      double angle = atan2(direction.y, direction.x) - atan2(0.0, 1.0);
      angle = angle * 180.0 / M_PI;

      double turnSpeed = 0.0;
      double turnTo = angle;
      double distanceAdd;
      double distanceSub;
      if (orientation < turnTo) {
	distanceAdd = turnTo - orientation;
	distanceSub = turnTo + 360.0 - orientation;
      } else {
	distanceAdd = turnTo + 360.0 - orientation;
	distanceSub = orientation - turnTo;
      }

      double distance = std::min(distanceAdd, distanceSub);
      
      if (fabs(distance) > 50.0) {
	turnSpeed = 10.0;
      } else if (fabs(distance) > 10.0) {
	turnSpeed = 5.0;
      } else if (fabs(distance) > 5.0) {
	turnSpeed = 2.5;
      } else if (fabs(distance) > 1.0) {
	turnSpeed = 1.0;
      } else {
	turnSpeed = 0.0;
      }
      
      if (distanceSub < distanceAdd) {
	orientation -= turnSpeed;
      } else {
	orientation += turnSpeed;
      }
      
      if (orientation >= 360.0) {
	orientation -= 360.0;
      }
    }
    break;

  case VIRUS_BODYTYPE_AMOEBA:
    maxSpeed = virusData->getMovementSpeed();
    maxAccel = 0.008;
    orientation += (rotateSpeed / 2.0);
    if (orientation >= 360.0) {
      orientation -= 360.0;
    }
    break;

  case VIRUS_BODYTYPE_SPHERE:
    maxSpeed = virusData->getMovementSpeed();
    maxAccel = 0.2;
    orientation += rotateSpeed;
    if (orientation >= 360.0) {
      orientation -= 360.0;
    }
    break;
  }

  frame++;

  // Virus being cloned inside cell
  if (state == VIRUSSTATE_INACTIVE) {
    Vector speed = Vector(position, destination);
    if (speed.length() > getBoundingCircle().getRadius() / 5.0) {
      speed = speed.normalize();
      speed = speed.mult(0.1);
      position = position.translate(speed);
    }
    return;
  }

  // Virus entering cell
  if (state == VIRUSSTATE_TAKINGCELL) {
    Vector speed = Vector(position, destination);
    if (speed.length() > getBoundingCircle().getRadius() / 5.0) {
      speed = speed.normalize();
      speed = speed.mult(0.05);
      position = position.translate(speed);
    } else {
      dead = true;
      takenCell->startCloning(owner, id);
    }
    return;
  }

  // Virus moving
  if (state == VIRUSSTATE_MOVING) {
    if (!gotDestination) {
      getDestination();
    } else if (reachedDestination()) {
      if (!moveDelay) {
	currentPath.pop_front();
	if (!currentPath.empty()) {
	  getDestination();
	} else {
	  gotDestination = false;
	  state = VIRUSSTATE_IDLE;
	}
      } else {
	gotDestination = false;
	destination = position;
      }
    }
  }

  Vector accel = Vector(0.0, 0.0, 0.0);
  if (gotDestination) {
    accel = Vector(position, destination);
    accel = accel.normalize();
    accel = accel.mult(maxAccel);
  } else {
    speed = Vector(0.0, 0.0, 0.0);
  }

  if (timeOnDestination) {
    double t = (double)timeOnDestination / 60.0;
    maxSpeed *= (0.5) * (1.0 - t);
  }
  speed = speed.translate(accel);
  if (speed.length() > maxSpeed) {
    speed = speed.normalize();
    speed = speed.mult(maxSpeed);
  }

  setPosition(position.translate(speed));

  if (moveDelay) {
    moveDelay--;
  }
  if (attackCooldown) {
    attackCooldown--;
  }
  if (flash) {
    flash--;
  }
  if (reproduceCooldown) {
    reproduceCooldown--;
  }
}