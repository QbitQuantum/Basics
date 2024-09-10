void CameraDragRotate::_onDrag(const Point& pt)
{
    if (!mTerrainHitInfo.hitted)
        return;

    Ogre::Vector3 oldPosition = getCamera()->getDerivedPosition();
    Ogre::Quaternion oldOrientation = getCamera()->getDerivedOrientation();

    getCamera()->yaw(Ogre::Degree(-mDragDelta.x * getSceneManipulator()->getRotateFactor() / getViewport()->getActualWidth()));

    // 只有在不使用真实摄像机的情况下才允许上下旋转摄像机
    if ( !getSceneManipulator()->getUseRealCameraAngle() )
        getCamera()->pitch(Ogre::Degree(-mDragDelta.y * getSceneManipulator()->getRotateFactor() / getViewport()->getActualHeight()));

    Ogre::Quaternion newOrientation = getCamera()->getDerivedOrientation();
    Ogre::Vector3 newPosition = mTerrainHitInfo.hitPosition +
                                newOrientation * oldOrientation.Inverse() * (oldPosition - mTerrainHitInfo.hitPosition);

    getSceneManipulator()->setCameraPosition(newPosition);
}