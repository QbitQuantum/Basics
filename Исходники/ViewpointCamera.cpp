void ViewpointCamera::rotate(const Location& startLocation, const Location& endLocation)
{
    Core::Vector3d startLocOnSphere = this->projectToSphere(startLocation);
    Core::Vector3d endLocOnSphere = this->projectToSphere(endLocation);

    double angle = std::acos(startLocOnSphere.dot(endLocOnSphere) /
                             (startLocOnSphere.norm() * endLocOnSphere.norm()));
    angle = angle * psa::kDegreeMultiplier;
    Core::Vector3d axis = startLocOnSphere.cross(endLocOnSphere);
    axis.normalize();

    Core::Matrix3x3 eyeRotMatrix = m_viewpoint->eyeRotationMatrix();
    eyeRotMatrix.rotate(Core::Quaternion{axis, -angle});

    m_viewpoint->setEyeRotationMatrix(eyeRotMatrix);
    this->updateViewMatrix();
}