/** Get the orientation of the frame at the specified time. The frame's orientation
  * is undefined whenever one or more of the following is true:
  *  - the state of either the primary or secondary object is undefined
  *  - the positions of the primary and secondary object are identical
  *  - the secondary is stationary with respect to the primary
  *  - the position and velocity vectors are exactly aligned
  */
Quaterniond
TwoBodyRotatingFrame::orientation(double t) const
{
    StateVector state = m_secondary->state(t) - m_primary->state(t);
    if (state.position().isZero() || state.velocity().isZero())
    {
        return Quaterniond::Identity();
    }

    // Compute the axes of the two body rotating frame,
    // convert this to a matrix, then derive a quaternion
    // from this matrix.

    // x-axis points in direction from the primary to the secondary
    Vector3d xAxis = state.position().normalized();
    Vector3d v = state.velocity().normalized();

    Vector3d zAxis;
    if (m_velocityAlligned) {
        // z-axis normal to both the x-axis and the velocity vector
        zAxis = xAxis.cross(v);
        if (zAxis.isZero())
        {
            return Quaterniond::Identity();
        }
    }
    else {
        // z-axis normal to both the x-axis and the z axis of the primary
        zAxis = xAxis.cross(m_primary->orientation(t) * Vector3d::UnitX());
        if (zAxis.isZero())
        {
            return Quaterniond::Identity();
        }
    }

    zAxis.normalize();
    Vector3d yAxis = zAxis.cross(xAxis);

    Matrix3d m;
    m << xAxis, yAxis, zAxis;

    return Quaterniond(m);
}