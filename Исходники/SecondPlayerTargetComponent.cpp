Point SecondPlayerTargetComponent::calculateVelocityVector() {
    Point firstPoint = indicatorPositionProvider_->getBorderIndicatorPosition();
    Point secondPoint = inputStateProvider_->getMousePosition();
    Point velocityVector = secondPoint - firstPoint;
    velocityVector.normalize();
    double distanceBetweenPoints = calculateDistanceBetweenPoints(firstPoint, secondPoint);
    velocityVector *= configuration_.getSecondPlayerAsteroidVelocityMultiplayer()*distanceBetweenPoints;
    return velocityVector;
}