///
/// \brief GlFrame::applyCameraTransformations
///     Apply camera transforms from current orientation
///     This is called at every frame in the rendering loop
///
void GlFrame::applyCameraTransformations()
{
    pProjMatrix = m_Camera->getProjectionMatrix();
    pViewMatrix = m_Camera->getViewMatrix();

    Vec3 pos = m_Camera->getPosition();
    Quaternion rot = m_Camera->getOrientation();

    Quaternion q_lookat = rot * Quaternion(0.0f, 0.0f, 0.0f, -1.0f) * rot.conjugate();
    q_lookat.normalize();

    Quaternion q_up = rot * Quaternion(0.0f, 0.0f, 1.0f, 0.0f) * rot.conjugate();
    q_up.normalize();

//    std::cout << "POS : " << pos.x << " ; " << pos.y << " ; " << pos.z << std::endl;
//    std::cout << "LOOK : " << q_lookat.x << " ; " << q_lookat.y << " ; " << q_lookat.z << std::endl;

    lookAt(pos.x, pos.y, pos.z, pos.x + q_lookat.x, pos.y + q_lookat.y, pos.z + q_lookat.z, q_up.x, q_up.y, q_up.z);
}