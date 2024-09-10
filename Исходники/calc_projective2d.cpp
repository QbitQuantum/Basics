Mat3 calc_projective (double* frame_ts,
                      Vec4* gyro_quat,
                      Vec3* acc_trans,
                      double* gyro_ts,
                      CalibrationParams calib)
{
    double ts0 = frame_ts[0] + calib.gyro_delay;
    Quatern rot0 = Quatern(gyro_quat[0] + calib.gyro_drift);
    double ts1 = frame_ts[1] + calib.gyro_delay;
    Quatern rot1 = Quatern(gyro_quat[1] + calib.gyro_drift);

    Vec3 trans0 = acc_trans[0];
    Vec3 trans1 = acc_trans[1];

    Mat3 extr0 = calc_extrinsic(rot0);
    Mat3 extr1 = calc_extrinsic(rot1);
    Mat3 intrin = calc_intrinsic(calib.fx, calib.fy, calib.cx, calib.cy, calib.skew);

    return intrin * extr0 * extr1.transpose() * intrin.inverse();
}