//==============================================================================
Eigen::Vector3d DefaultEventHandler::getDeltaCursor(
    const Eigen::Vector3d& _fromPosition,
    ConstraintType _constraint,
    const Eigen::Vector3d& _constraintVector) const
{
    osg::Vec3d eye, center, up;
    mViewer->getCamera()->getViewMatrixAsLookAt(eye, center, up);

    Eigen::Vector3d near, far;
    getNearAndFarPointUnderCursor(near, far);
    Eigen::Vector3d v1 = far-near;

    if(LINE_CONSTRAINT == _constraint)
    {
        const Eigen::Vector3d& b1 = near;
        const Eigen::Vector3d& v2 = _constraintVector;
        const Eigen::Vector3d& b2 = _fromPosition;

        double v1_v1 = v1.dot(v1);
        double v2_v2 = v2.dot(v2);
        double v2_v1 = v2.dot(v1);

        double denominator = v1_v1*v2_v2 - v2_v1*v2_v1;
        double s;
        if(fabs(denominator) < 1e-10)
            s = 0;
        else
            s = (v1_v1*(v2.dot(b1)-v2.dot(b2)) + v2_v1*(v1.dot(b2)-v1.dot(b1)))/denominator;

        return v2*s;
    }
    else if(PLANE_CONSTRAINT == _constraint)
    {
        const Eigen::Vector3d& n = _constraintVector;
        double s = n.dot(_fromPosition - near) / n.dot(v1);
        return near - _fromPosition + s*v1;
    }
    else
    {
        Eigen::Vector3d n = osgToEigVec3(center - eye);
        double s = n.dot(_fromPosition - near) / n.dot(v1);
        return near - _fromPosition + s*v1;
    }

    return Eigen::Vector3d::Zero();
}