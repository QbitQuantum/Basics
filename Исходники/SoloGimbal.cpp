Vector3f SoloGimbal::get_ang_vel_dem_yaw(const Quaternion &quatEst)
{
    static const float tc = 0.1f;
    static const float yawErrorLimit = radians(5.7f);
    float dt = _measurement.delta_time;
    float alpha = dt/(dt+tc);

    const AP_AHRS_NavEKF &_ahrs = AP::ahrs_navekf();
    Matrix3f Tve = _ahrs.get_rotation_body_to_ned();
    Matrix3f Teg;
    quatEst.inverse().rotation_matrix(Teg);


    //_vehicle_yaw_rate_ef_filt = _ahrs.get_yaw_rate_earth();

    // filter the vehicle yaw rate to remove noise
    _vehicle_yaw_rate_ef_filt += (_ahrs.get_yaw_rate_earth() - _vehicle_yaw_rate_ef_filt) * alpha;

    float yaw_rate_ff = 0;

    // calculate an earth-frame yaw rate feed-forward that prevents gimbal from exceeding the maximum yaw error
    if (_vehicle_yaw_rate_ef_filt > _gimbalParams.get_K_rate()*yawErrorLimit) {
        yaw_rate_ff = _vehicle_yaw_rate_ef_filt-_gimbalParams.get_K_rate()*yawErrorLimit;
    } else if (_vehicle_yaw_rate_ef_filt < -_gimbalParams.get_K_rate()*yawErrorLimit) {
        yaw_rate_ff = _vehicle_yaw_rate_ef_filt+_gimbalParams.get_K_rate()*yawErrorLimit;
    }

    // filter the feed-forward to remove noise
    //_yaw_rate_ff_ef_filt += (yaw_rate_ff - _yaw_rate_ff_ef_filt) * alpha;

    Vector3f gimbalRateDemVecYaw;
    gimbalRateDemVecYaw.z = yaw_rate_ff - _gimbalParams.get_K_rate() * _filtered_joint_angles.z / constrain_float(Tve.c.z,0.5f,1.0f);
    gimbalRateDemVecYaw.z /= constrain_float(Tve.c.z,0.5f,1.0f);

    // rotate the rate demand into gimbal frame
    gimbalRateDemVecYaw = Teg * gimbalRateDemVecYaw;

    return gimbalRateDemVecYaw;
}