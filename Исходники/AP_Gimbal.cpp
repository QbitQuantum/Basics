Vector3f AP_Gimbal::getGimbalRateDemVecYaw(const Quaternion &quatEst)
{
        // define the rotation from vehicle to earth
        Matrix3f Tve = _ahrs.get_dcm_matrix();
        Matrix3f Teg;
        quatEst.inverse().rotation_matrix(Teg);

        // multiply the yaw joint angle by a gain to calculate a demanded vehicle frame relative rate vector required to keep the yaw joint centered
        Vector3f gimbalRateDemVecYaw;
        gimbalRateDemVecYaw.z = - _gimbalParams.get_K_rate() * filtered_joint_angles.z;

        // Get filtered vehicle turn rate in earth frame
        vehicleYawRateFilt = (1.0f - yawRateFiltPole * _measurement.delta_time) * vehicleYawRateFilt + yawRateFiltPole * _measurement.delta_time * _ahrs.get_yaw_rate_earth();
        Vector3f vehicle_rate_ef(0,0,vehicleYawRateFilt);

         // calculate the maximum steady state rate error corresponding to the maximum permitted yaw angle error
        float maxRate = _gimbalParams.get_K_rate() * yawErrorLimit;
        float vehicle_rate_mag_ef = vehicle_rate_ef.length();
        float excess_rate_correction = fabsf(vehicle_rate_mag_ef) - maxRate; 
        if (vehicle_rate_mag_ef > maxRate) {
            if (vehicle_rate_ef.z>0.0f){
                gimbalRateDemVecYaw += _ahrs.get_dcm_matrix().transposed()*Vector3f(0,0,excess_rate_correction);
            } else {
                gimbalRateDemVecYaw -= _ahrs.get_dcm_matrix().transposed()*Vector3f(0,0,excess_rate_correction);
            }
        }

        // rotate the rate demand into earth frame
        gimbalRateDemVecYaw = Tve * gimbalRateDemVecYaw;
        // zero the tilt components
        gimbalRateDemVecYaw.x = 0;
        gimbalRateDemVecYaw.y = 0;
        // rotate the rate demand into gimbal frame
        gimbalRateDemVecYaw = Teg * gimbalRateDemVecYaw;
        return gimbalRateDemVecYaw;
}