MoveTo_TaskSpace::MoveTo_TaskSpace(const Affine3d &pose, const Vector3d &dp, double pos_tol,
                     const Vector3d &rpy_minus, const Vector3d &rpy_plus)
{
    double X, Y, Z, roll, pitch, yaw ;

    poseToXYZRPY(pose, X, Y, Z, roll, pitch, yaw) ;

    c0 = Vector3d(X, Y, Z) ;
    a0 = Vector3d(roll, pitch, yaw) ;

    Vector3d c1 = c0 + dp ;

    // We define a coordinate system with the Z axis pointing towards the target point

    Matrix3d r = getLookAtMatrix(dp) ;

    frame = r  ;
    iframe = r.inverse() ;

    // we use a cylinder parameterization of the position

    lower[0] = 0.0      ; upper[0] = dp.norm() ; // cylinder length
    lower[1] = -M_PI    ; upper[1] = M_PI ; // polar angle
    lower[2] = 0.0      ; upper[2] = pos_tol ; // radius

    const double small_ = 0.001 ;

    double roll_min = std::max(a0.x() - fabs(rpy_minus.x()) - small_, -M_PI) ;
    double roll_max = std::min(a0.x() + fabs(rpy_plus.x()) + small_, M_PI) ;

    double pitch_min = std::max(a0.y() - fabs(rpy_minus.y()) - small_, -M_PI) ;
    double pitch_max = std::min(a0.y() + fabs(rpy_plus.y()) + small_, M_PI) ;

    double yaw_min = std::max(a0.z() - fabs(rpy_minus.z()) - small_, -M_PI) ;
    double yaw_max = std::min(a0.z() + fabs(rpy_plus.z()) + small_, M_PI) ;

    upper[3] = roll_max     ; lower[3] = roll_min ;
    upper[4] = pitch_max    ; lower[4] = pitch_min ;
    upper[5] = yaw_max      ; lower[5] = yaw_min ;

}