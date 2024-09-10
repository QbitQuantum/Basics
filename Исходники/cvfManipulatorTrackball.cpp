//--------------------------------------------------------------------------------------------------
/// Pan the camera up/down and left/right
/// 
/// \return  Returns true if input caused changes to the camera an false if no changes occurred
//--------------------------------------------------------------------------------------------------
bool ManipulatorTrackball::pan(int posX, int posY)
{
    if (m_camera.isNull()) return false;
    if (posX == m_lastPosX && posY == m_lastPosY) return false;

    const double vpPixSizeX = m_camera->viewport()->width();
    const double vpPixSizeY = m_camera->viewport()->height();
    if (vpPixSizeX <= 0 || vpPixSizeY <= 0) return false;

    // Normalized movement in screen plane 
    double tx = (posX - m_lastPosX)/vpPixSizeX;
    double ty = (posY - m_lastPosY)/vpPixSizeY;

    // Viewport size in world coordinates
    const double aspect = m_camera->aspectRatio();
    const double vpWorldSizeY = m_camera->frontPlaneFrustumHeight();
    const double vpWorldSizeX = vpWorldSizeY*aspect;

    const Vec3d camUp = m_camera->up();
    const Vec3d camRight = m_camera->right();


    Vec3d translation(0, 0, 0);

    Camera::ProjectionType projType = m_camera->projection();
    if (projType == Camera::PERSPECTIVE)
    {
        const Vec3d camPos = m_camera->position();
        const Vec3d camDir = m_camera->direction();
        const double nearPlane = m_camera->nearPlane();

        // Compute distance from camera to rotation point projected onto camera forward direction
        const Vec3d vDiff = m_rotationPoint - camPos;
        const double camRotPointDist = Math::abs(camDir*vDiff);

        Vec3d vX =  camRight*((tx*vpWorldSizeX)/nearPlane)*camRotPointDist;
        Vec3d vY =  camUp*((ty*vpWorldSizeY)/nearPlane)*camRotPointDist;
        translation = vX + vY;
    }
    else if (projType == Camera::ORTHO)
    {
        Vec3d vX =  camRight*tx*vpWorldSizeX;
        Vec3d vY =  camUp*ty*vpWorldSizeY;
        translation = vX + vY;
    }

    Mat4d viewMat = m_camera->viewMatrix();
    viewMat.translatePostMultiply(translation);
    m_camera->setViewMatrix(viewMat);

    m_lastPosX = posX;
    m_lastPosY = posY;

    return true;
}