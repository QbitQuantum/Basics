// get_variances - provides the innovations normalised using the innovation variance where a value of 0
// indicates prefect consistency between the measurement and the EKF solution and a value of of 1 is the maximum
// inconsistency that will be accpeted by the filter
// boolean false is returned if variances are not available
bool AP_AHRS_NavEKF::get_variances(float &velVar, float &posVar, float &hgtVar, Vector3f &magVar, float &tasVar, Vector2f &offset) const
{
    switch (ekf_type()) {
    case EKF_TYPE_NONE:
        // We are not using an EKF so no data
        return false;

#if AP_AHRS_WITH_EKF1
    case EKF_TYPE1:
        // use EKF to get variance
        EKF1.getVariances(velVar, posVar, hgtVar, magVar, tasVar, offset);
        return true;
#endif

    case EKF_TYPE2:
    default:
        // use EKF to get variance
        EKF2.getVariances(-1,velVar, posVar, hgtVar, magVar, tasVar, offset);
        return true;

#if CONFIG_HAL_BOARD == HAL_BOARD_SITL
    case EKF_TYPE_SITL:
        velVar = 0;
        posVar = 0;
        hgtVar = 0;
        magVar.zero();
        tasVar = 0;
        offset.zero();
        return true;
#endif
    }
}