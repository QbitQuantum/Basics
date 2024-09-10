PickRay RayPick::getMathematicalPick() const {
    if (!parentTransform) {
        return _mathPick;
    }

    Transform currentParentTransform = parentTransform->getTransform();
    glm::vec3 origin = currentParentTransform.transform(_mathPick.origin);
    glm::vec3 direction = glm::normalize(currentParentTransform.transformDirection(_mathPick.direction));
    return PickRay(origin, direction);
}