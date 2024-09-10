bool
AP_GPS_SBP::_attempt_state_update()
{

    // If we currently have heartbeats
    //    - NO FIX
    //
    // If we have a full update available, save it
    //
    uint32_t now = AP_HAL::millis();
    bool ret = false;

    if (now - last_heatbeat_received_ms > SBP_TIMEOUT_HEATBEAT) {

        state.status = AP_GPS::NO_FIX;
        Debug("No Heartbeats from Piksi! Driver Ready to Die!");

    } else if (last_pos_llh_rtk.tow == last_vel_ned.tow
            && abs((int32_t) (last_gps_time.tow - last_vel_ned.tow)) < 10000
            && abs((int32_t) (last_dops.tow - last_vel_ned.tow)) < 60000
            && last_vel_ned.tow > last_full_update_tow) {

        // Use the RTK position
        sbp_pos_llh_t *pos_llh = &last_pos_llh_rtk;

        // Update time state
        state.time_week         = last_gps_time.wn;
        state.time_week_ms      = last_vel_ned.tow;

        state.hdop              = last_dops.hdop;

        // Update velocity state
        state.velocity[0]       = (float)(last_vel_ned.n * 1.0e-3);
        state.velocity[1]       = (float)(last_vel_ned.e * 1.0e-3);
        state.velocity[2]       = (float)(last_vel_ned.d * 1.0e-3);
        state.have_vertical_velocity = true;

        float ground_vector_sq = state.velocity[0]*state.velocity[0] + state.velocity[1]*state.velocity[1];
        state.ground_speed = safe_sqrt(ground_vector_sq);

        state.ground_course = wrap_360(degrees(atan2f(state.velocity[1], state.velocity[0])));

        // Update position state

        state.location.lat      = (int32_t) (pos_llh->lat * (double)1e7);
        state.location.lng      = (int32_t) (pos_llh->lon * (double)1e7);
        state.location.alt      = (int32_t) (pos_llh->height * 100);
        state.num_sats          = pos_llh->n_sats;

        if (pos_llh->flags == 0) {
            state.status = AP_GPS::GPS_OK_FIX_3D;
        } else if (pos_llh->flags == 2) {
            state.status = AP_GPS::GPS_OK_FIX_3D_RTK_FLOAT;
        } else if (pos_llh->flags == 1) {
            state.status = AP_GPS::GPS_OK_FIX_3D_RTK_FIXED;
        }

        last_full_update_tow = last_vel_ned.tow;
        last_full_update_cpu_ms = now;
        state.rtk_iar_num_hypotheses = last_iar_num_hypotheses;

        logging_log_full_update();
        ret = true;

    } else if (now - last_full_update_cpu_ms > SBP_TIMEOUT_PVT) {

        //INVARIANT: If we currently have a fix, ONLY return true after a full update.

        state.status = AP_GPS::NO_FIX;
        ret = true;

    } else {

        //No timeouts yet, no data yet, nothing has happened.

    }

    return ret;

}