float AP_Landing_Deepstall::update_steering()
{
    Location current_loc;
    if (!landing.ahrs.get_position(current_loc)) {
        // panic if no position source is available
        // continue the  but target just holding the wings held level as deepstall should be a minimal energy
        // configuration on the aircraft, and if a position isn't available aborting would be worse
        GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL, "Deepstall: No position available. Attempting to hold level");
        memcpy(&current_loc, &landing_point, sizeof(Location));
    }
    uint32_t time = AP_HAL::millis();
    float dt = constrain_float(time - last_time, (uint32_t)10UL, (uint32_t)200UL) / 1000.0;
    last_time = time;


    Vector2f ab = location_diff(arc_exit, extended_approach);
    ab.normalize();
    Vector2f a_air = location_diff(arc_exit, current_loc);

    crosstrack_error = a_air % ab;
    float sine_nu1 = constrain_float(crosstrack_error / MAX(L1_period, 0.1f), -0.7071f, 0.7107f);
    float nu1 = asinf(sine_nu1);

    if (L1_i > 0) {
        L1_xtrack_i += nu1 * L1_i / dt;
        L1_xtrack_i = constrain_float(L1_xtrack_i, -0.5f, 0.5f);
        nu1 += L1_xtrack_i;
    }

    float desired_change = wrap_PI(radians(target_heading_deg) + nu1 - landing.ahrs.yaw);

    float yaw_rate = landing.ahrs.get_gyro().z;
    float yaw_rate_limit_rps = radians(yaw_rate_limit);
    float error = wrap_PI(constrain_float(desired_change / time_constant,
                                          -yaw_rate_limit_rps, yaw_rate_limit_rps) - yaw_rate);

#ifdef DEBUG_PRINTS
    GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_INFO, "x: %f e: %f r: %f d: %f",
                                    (double)crosstrack_error,
                                    (double)error,
                                    (double)degrees(yaw_rate),
                                    (double)location_diff(current_loc, landing_point).length());
#endif // DEBUG_PRINTS

    return ds_PID.get_pid(error);
}