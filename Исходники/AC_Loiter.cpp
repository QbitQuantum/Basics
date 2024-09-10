// sanity check parameters
void AC_Loiter::sanity_check_params()
{
    _speed_cms = MAX(_speed_cms, LOITER_SPEED_MIN);
    _accel_cmss = MIN(_accel_cmss, GRAVITY_MSS * 100.0f * tanf(ToRad(_attitude_control.lean_angle_max() * 0.01f)));
}