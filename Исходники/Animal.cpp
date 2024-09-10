void Animal::handleCollisions(Environment *environment) {
    Vector2D boundsCorrection;
    if (getBounds().getMinX() < environment->getBounds().getMinX()) {
        boundsCorrection.setX(environment->getBounds().getMinX() - getBounds().getMinX());
    }
    if (getBounds().getMinY() < environment->getBounds().getMinY()) {
        boundsCorrection.setY(environment->getBounds().getMinY() - getBounds().getMinY());
    }
    if (getBounds().getMaxX() > environment->getBounds().getMaxX()) {
        boundsCorrection.setX(environment->getBounds().getMaxX() - getBounds().getMaxX());
    }
    if (getBounds().getMaxY() > environment->getBounds().getMaxY()) {
        boundsCorrection.setY(environment->getBounds().getMaxY() - getBounds().getMaxY());
    }
    translate(boundsCorrection);
    
    std::vector<Object *> nearestObjects = environment->getNearestObjects(this);
    for (int k = 0; k < nearestObjects.size(); k++) {
        Object *nearestObject = nearestObjects[k];
        double distance = getPosition().distanceTo(nearestObject->getPosition());
        double radius = (OBJECT_WIDTH / 2);
        if (distance < 2.0 * radius) {
            Vector2D overlapVector = Vector2D(nearestObject->getPosition(), getPosition());        
            overlapVector = overlapVector.normalize();
            
            double overlapLength = 2.0 * radius - distance;
            overlapVector = overlapVector.mult(overlapLength);
            
            translate(overlapVector);
            
            handleCollision(environment, nearestObject);
        }
    }
}