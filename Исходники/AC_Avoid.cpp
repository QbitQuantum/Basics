/*
 * Adjusts the desired velocity for the polygon fence.
 */
void AC_Avoid::adjust_velocity_polygon_fence(float kP, float accel_cmss, Vector2f &desired_vel)
{
    // exit if the polygon fence is not enabled
    if ((_fence.get_enabled_fences() & AC_FENCE_TYPE_POLYGON) == 0) {
        return;
    }

    // exit if the polygon fence has already been breached
    if ((_fence.get_breaches() & AC_FENCE_TYPE_POLYGON) != 0) {
        return;
    }

    // exit immediately if no desired velocity
    if (desired_vel.is_zero()) {
        return;
    }

    // get polygon boundary
    // Note: first point in list is the return-point (which copter does not use)
    uint16_t num_points;
    Vector2f* boundary = _fence.get_polygon_points(num_points);

    // adjust velocity using polygon
    adjust_velocity_polygon(kP, accel_cmss, desired_vel, boundary, num_points, true);
}