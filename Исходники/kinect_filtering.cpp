int extractFrame (const pcl::ModelCoefficients& coeffs,
                  const ARPoint& p1, const ARPoint& p2,
                  const ARPoint& p3, const ARPoint& p4,
                  tf::Matrix3x3 &retmat)
{
    // Get plane coeffs and project points onto the plane
    double a=0, b=0, c=0, d=0;
    if(getCoeffs(coeffs, &a, &b, &c, &d) < 0)
        return -1;

    const tf::Vector3 q1 = project(p1, a, b, c, d);
    const tf::Vector3 q2 = project(p2, a, b, c, d);
    const tf::Vector3 q3 = project(p3, a, b, c, d);
    const tf::Vector3 q4 = project(p4, a, b, c, d);

    // Make sure points aren't the same so things are well-defined
    if((q2-q1).length() < 1e-3)
        return -1;

    // (inverse) matrix with the given properties
    const tf::Vector3 v = (q2-q1).normalized();
    const tf::Vector3 n(a, b, c);
    const tf::Vector3 w = -v.cross(n);
    tf::Matrix3x3 m(v[0], v[1], v[2], w[0], w[1], w[2], n[0], n[1], n[2]);

    // Possibly flip things based on third point
    const tf::Vector3 diff = (q4-q3).normalized();
    //ROS_INFO_STREAM("w = " << w << " and d = " << diff);
    if (w.dot(diff)<0)
    {
        //ROS_INFO_STREAM("Flipping normal based on p3.  Current value: " << m);
        m[1] = -m[1];
        m[2] = -m[2];
        //ROS_INFO_STREAM("New value: " << m);
    }

    // Invert and return
    retmat = m.inverse();
    //cerr << "Frame is " << retmat << endl;
    return 0;
}