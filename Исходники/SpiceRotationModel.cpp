Vector3d
SpiceRotationModel::angularVelocity(double tdbSec) const
{
    double et = tdbSec;
    SpiceDouble transform[6][6];

    sxform_c(m_fromFrame.c_str(), m_toFrame.c_str(), et, transform);
    if (!failed_c())
    {
        // Extract the angular velocity vector from the state transform matrix
        // Rotation matrix is the top left 3x3 matrix
        Matrix3d R;
        R << transform[0][0], transform[0][1], transform[0][2],
             transform[1][0], transform[1][1], transform[1][2],
             transform[2][0], transform[2][1], transform[2][2];

        // W*R is the lower left 3x3 matrix
        Matrix3d WR;
        WR << transform[3][0], transform[3][1], transform[3][2],
              transform[4][0], transform[4][1], transform[4][2],
              transform[5][0], transform[5][1], transform[5][2];

        // Multiply by inverse of R (= transpose, since R is a rotation) to get
        // the skew-symmetric matrix W*
        Matrix3d W = WR * R.transpose();

        return Vector3d(-W(1, 2), W(0, 2), -W(0, 1));
    }
    else
    {
        char errorMessage[1024];
        getmsg_c("long", sizeof(errorMessage), errorMessage);
        cerr << errorMessage << std::endl;
        reset_c();
        return Vector3d::Zero();
    }
}