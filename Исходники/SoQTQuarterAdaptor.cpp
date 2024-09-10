void SIM::Coin3D::Quarter::SoQTQuarterAdaptor::seekToPoint(const SbVec3f& scenepos)
{
    SbVec3f hitpoint(scenepos);

    m_camerastartposition = getSoRenderManager()->getCamera()->position.getValue();
    m_camerastartorient = getSoRenderManager()->getCamera()->orientation.getValue();

    // move point to the camera coordinate system, consider
    // transformations before camera in the scene graph
    SbMatrix cameramatrix, camerainverse;
    getCameraCoordinateSystem(getSoRenderManager()->getCamera(),
                              getSceneGraph(),
                              cameramatrix,
                              camerainverse);
    camerainverse.multVecMatrix(hitpoint, hitpoint);

    float fd = m_seekdistance;

    if(!m_seekdistanceabs)
        fd *= (hitpoint - getSoRenderManager()->getCamera()->position.getValue()).length()/100.0f;

    getSoRenderManager()->getCamera()->focalDistance = fd;

    SbVec3f dir = hitpoint - m_camerastartposition;
    dir.normalize();

    // find a rotation that rotates current camera direction into new
    // camera direction.
    SbVec3f olddir;
    getSoRenderManager()->getCamera()->orientation.getValue().multVec(SbVec3f(0, 0, -1), olddir);
    SbRotation diffrot(olddir, dir);
    m_cameraendposition = hitpoint - fd * dir;
    m_cameraendorient = getSoRenderManager()->getCamera()->orientation.getValue() * diffrot;

    if(m_seeksensor->isScheduled()) {
        m_seeksensor->unschedule();
        interactiveCountDec();
    }

    m_seeksensor->setBaseTime(SbTime::getTimeOfDay());
    m_seeksensor->schedule();
    interactiveCountInc();
}