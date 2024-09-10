bool Box::contains(
    const Vector3&      point) const {

    // Form axes from three edges, transform the point into that
    // space, and perform 3 interval tests

    Vector3 u = _corner[4] - _corner[0];
    Vector3 v = _corner[3] - _corner[0];
    Vector3 w = _corner[1] - _corner[0];

    Matrix3 M = Matrix3(u.x, v.x, w.x,
                        u.y, v.y, w.y,
                        u.z, v.z, w.z);

    // M^-1 * (point - _corner[0]) = point in unit cube's object space
    // compute the inverse of M
    Vector3 osPoint = M.inverse() * (point - _corner[0]);

    return
        (osPoint.x >= 0) && 
        (osPoint.y >= 0) &&
        (osPoint.z >= 0) &&
        (osPoint.x <= 1) &&
        (osPoint.y <= 1) &&
        (osPoint.z <= 1);
}