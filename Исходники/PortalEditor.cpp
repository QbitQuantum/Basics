//-------------------------------------------------------------------------------
bool PortalEditor::snapTpPortal(PortalEditor* dest,bool bAllowMove )
{
    //reposition & realign this portal (and its parent zone)
    //to connect with this portal.

    //Before snapping portals togther, we should check that the zone is
    //not already locked into position by another portal join.
    //However, even if this is the case, we can still join portals if
    //they are already in the correct position.

    //get current position data:
    Ogre::Quaternion qZone = mParentZone->getDerivedOrientation();
    Ogre::Quaternion qDest = dest->getDerivedOrientation();
    Ogre::Quaternion qPortal = this->getOrientation();
    Ogre::Vector3 vDest = dest->getDerivedPosition();
    Ogre::Vector3 vPortal = this->getDerivedPosition();


    const Ogre::Real DIST_EPSILON(0.01f);//fudge factor
    const Ogre::Radian ANG_EPSILON(0.01f);
    if(vPortal.distance(vDest)<DIST_EPSILON && qPortal.equals(qDest*Ogre::Quaternion(0,0,1,0),ANG_EPSILON))return true;
    if(!bAllowMove)return false;

    //orientation
    Ogre::Quaternion qNew = (qDest*Ogre::Quaternion(0,0,1,0))*qPortal.Inverse();
    mParentZone->setDerivedOrientation(qNew);

    //position
    Ogre::Vector3 vZone = mParentZone->getDerivedPosition();
    vPortal = this->getDerivedPosition();

    mParentZone->setDerivedPosition( (vDest - (vPortal-vZone)));

    return true;
}