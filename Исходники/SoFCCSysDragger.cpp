void RDragger::dragStart()
{
    SoSwitch *sw;
    sw = SO_GET_ANY_PART(this, "rotatorSwitch", SoSwitch);
    SoInteractionKit::setSwitchValue(sw, 1);

    projector.setViewVolume(this->getViewVolume());
    projector.setWorkingSpace(this->getLocalToWorldMatrix());
    projector.setPlane(SbPlane(SbVec3f(0.0, 0.0, 1.0), 0.0));

    SbVec3f hitPoint;
    if (!projector.tryProject(getNormalizedLocaterPosition(), 0.0, hitPoint))
        return;
    hitPoint.normalize();

    SbMatrix localToWorld = getLocalToWorldMatrix();
    localToWorld.multVecMatrix(hitPoint, hitPoint);
    setStartingPoint((hitPoint));

    rotationIncrementCount.setValue(0);
}