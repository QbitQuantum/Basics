/// Guess position in 3D corresponding to a 2D click
///
/// `clickPos` - 2D position in viewport, as from a mouse event.
Imath::V3d View3D::guessClickPosition(const QPoint& clickPos)
{
    // Get new point in the projected coordinate system using the click
    // position x,y and the z of a reference position.  Take the reference point
    // of interest to be between the camera rotation center and the camera
    // position, as a rough guess of the depth the user is interested in.
    //
    // This works pretty well, except when there are noise points intervening
    // between the reference position and the user's actual point of interest.
    V3d refPos = 0.3*m_camera.position() + 0.7*m_camera.center();
    M44d mat = m_camera.viewMatrix()*m_camera.projectionMatrix()*m_camera.viewportMatrix();
    double refZ = (refPos * mat).z;
    V3d newPointProj(clickPos.x(), clickPos.y(), refZ);
    // Map projected point back into model coordinates
    return newPointProj * mat.inverse();
}