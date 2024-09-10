    /*
     * Creates a rotation matrix which describes how a point in an auxiliary
     * coordinate system, whose x axis is desbibed by vec_along_x_axis and has
     * a point on its xz-plane vec_on_xz_plane, rotates into the real coordinate
     * system.
     */
    void Cornea::createRotationMatrix(const Eigen::Vector3d &vec_along_x_axis,
                                      const Eigen::Vector3d &vec_on_xz_plane,
                                      Eigen::Matrix3d &R) {

        // normalise pw
        Eigen::Vector3d vec_on_xz_plane_n = vec_on_xz_plane.normalized();

        // define helper variables x, y and z
        // x
        Eigen::Vector3d xn = vec_along_x_axis.normalized();

        // y
        Eigen::Vector3d tmp = vec_on_xz_plane_n.cross(xn);
        Eigen::Vector3d yn = tmp.normalized();

        // z
        tmp = xn.cross(yn);
        Eigen::Vector3d zn = tmp.normalized();

        // create the rotation matrix
        R.col(0) << xn(0), xn(1), xn(2);
        R.col(1) << yn(0), yn(1), yn(2);
        R.col(2) << zn(0), zn(1), zn(2);

    }