PickParabola ParabolaPick::getMathematicalPick() const {
    if (!parentTransform) {
        PickParabola mathPick = _mathPick;
        if (_rotateAccelerationWithAvatar) {
            mathPick.acceleration = DependencyManager::get<AvatarManager>()->getMyAvatar()->getWorldOrientation() * mathPick.acceleration;
        }
        return mathPick;
    }

    Transform currentParentTransform = parentTransform->getTransform();

    glm::vec3 position = currentParentTransform.transform(_mathPick.origin);
    glm::vec3 velocity = _mathPick.velocity;
    if (_scaleWithParent) {
        velocity = currentParentTransform.transformDirection(velocity);
    } else {
        glm::vec3 transformedVelocity = currentParentTransform.transformDirection(velocity);
        velocity = glm::normalize(transformedVelocity) * _speed;
    }
    glm::vec3 acceleration = _mathPick.acceleration;
    if (_scaleWithParent) {
        acceleration *= currentParentTransform.getScale();
    }
    if (_rotateAccelerationWithAvatar) {
        acceleration = DependencyManager::get<AvatarManager>()->getMyAvatar()->getWorldOrientation() * acceleration;
    } else if (_rotateAccelerationWithParent) {
        acceleration = currentParentTransform.getRotation() * acceleration;
    }

    return PickParabola(position, velocity, acceleration);
}