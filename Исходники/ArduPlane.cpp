/*
  main flight mode dependent update code 
 */
void Plane::update_flight_mode(void)
{
    enum FlightMode effective_mode = control_mode;
    if (control_mode == AUTO && g.auto_fbw_steer == 42) {
        effective_mode = FLY_BY_WIRE_A;
    }

    if (effective_mode != AUTO) {
        // hold_course is only used in takeoff and landing
        steer_state.hold_course_cd = -1;
    }

    // ensure we are fly-forward when we are flying as a pure fixed
    // wing aircraft. This helps the EKF produce better state
    // estimates as it can make stronger assumptions
    if (quadplane.in_vtol_mode() ||
        quadplane.in_assisted_flight()) {
        ahrs.set_fly_forward(false);
    } else if (flight_stage == AP_Vehicle::FixedWing::FLIGHT_LAND) {
        ahrs.set_fly_forward(landing.is_flying_forward());
    } else {
        ahrs.set_fly_forward(true);
    }

    switch (effective_mode) 
    {
    case AUTO:
        handle_auto_mode();
        break;

    case AVOID_ADSB:
    case GUIDED:
        if (auto_state.vtol_loiter && quadplane.available()) {
            quadplane.guided_update();
            break;
        }
        FALLTHROUGH;

    case RTL:
    case LOITER:
        calc_nav_roll();
        calc_nav_pitch();
        calc_throttle();
        break;
        
    case TRAINING: {
        training_manual_roll = false;
        training_manual_pitch = false;
        update_load_factor();
        
        // if the roll is past the set roll limit, then
        // we set target roll to the limit
        if (ahrs.roll_sensor >= roll_limit_cd) {
            nav_roll_cd = roll_limit_cd;
        } else if (ahrs.roll_sensor <= -roll_limit_cd) {
            nav_roll_cd = -roll_limit_cd;                
        } else {
            training_manual_roll = true;
            nav_roll_cd = 0;
        }
        
        // if the pitch is past the set pitch limits, then
        // we set target pitch to the limit
        if (ahrs.pitch_sensor >= aparm.pitch_limit_max_cd) {
            nav_pitch_cd = aparm.pitch_limit_max_cd;
        } else if (ahrs.pitch_sensor <= pitch_limit_min_cd) {
            nav_pitch_cd = pitch_limit_min_cd;
        } else {
            training_manual_pitch = true;
            nav_pitch_cd = 0;
        }
        if (fly_inverted()) {
            nav_pitch_cd = -nav_pitch_cd;
        }
        break;
    }

    case ACRO: {
        // handle locked/unlocked control
        if (acro_state.locked_roll) {
            nav_roll_cd = acro_state.locked_roll_err;
        } else {
            nav_roll_cd = ahrs.roll_sensor;
        }
        if (acro_state.locked_pitch) {
            nav_pitch_cd = acro_state.locked_pitch_cd;
        } else {
            nav_pitch_cd = ahrs.pitch_sensor;
        }
        break;
    }

    case AUTOTUNE:
    case FLY_BY_WIRE_A: {
        // set nav_roll and nav_pitch using sticks
        nav_roll_cd  = channel_roll->norm_input() * roll_limit_cd;
        nav_roll_cd = constrain_int32(nav_roll_cd, -roll_limit_cd, roll_limit_cd);
        update_load_factor();
        float pitch_input = channel_pitch->norm_input();
        if (pitch_input > 0) {
            nav_pitch_cd = pitch_input * aparm.pitch_limit_max_cd;
        } else {
            nav_pitch_cd = -(pitch_input * pitch_limit_min_cd);
        }
        adjust_nav_pitch_throttle();
        nav_pitch_cd = constrain_int32(nav_pitch_cd, pitch_limit_min_cd, aparm.pitch_limit_max_cd.get());
        if (fly_inverted()) {
            nav_pitch_cd = -nav_pitch_cd;
        }
        if (failsafe.rc_failsafe && g.fs_action_short == FS_ACTION_SHORT_FBWA) {
            // FBWA failsafe glide
            nav_roll_cd = 0;
            nav_pitch_cd = 0;
            SRV_Channels::set_output_limit(SRV_Channel::k_throttle, SRV_Channel::SRV_CHANNEL_LIMIT_MIN);
        }
        if (g.fbwa_tdrag_chan > 0) {
            // check for the user enabling FBWA taildrag takeoff mode
            bool tdrag_mode = (RC_Channels::get_radio_in(g.fbwa_tdrag_chan-1) > 1700);
            if (tdrag_mode && !auto_state.fbwa_tdrag_takeoff_mode) {
                if (auto_state.highest_airspeed < g.takeoff_tdrag_speed1) {
                    auto_state.fbwa_tdrag_takeoff_mode = true;
                    gcs().send_text(MAV_SEVERITY_WARNING, "FBWA tdrag mode");
                }
            }
        }
        break;
    }

    case FLY_BY_WIRE_B:
        // Thanks to Yury MonZon for the altitude limit code!
        nav_roll_cd = channel_roll->norm_input() * roll_limit_cd;
        nav_roll_cd = constrain_int32(nav_roll_cd, -roll_limit_cd, roll_limit_cd);
        update_load_factor();
        update_fbwb_speed_height();
        break;
        
    case CRUISE:
        /*
          in CRUISE mode we use the navigation code to control
          roll when heading is locked. Heading becomes unlocked on
          any aileron or rudder input
        */
        if (channel_roll->get_control_in() != 0 || channel_rudder->get_control_in() != 0) {
            cruise_state.locked_heading = false;
            cruise_state.lock_timer_ms = 0;
        }                 
        
        if (!cruise_state.locked_heading) {
            nav_roll_cd = channel_roll->norm_input() * roll_limit_cd;
            nav_roll_cd = constrain_int32(nav_roll_cd, -roll_limit_cd, roll_limit_cd);
            update_load_factor();
        } else {
            calc_nav_roll();
        }
        update_fbwb_speed_height();
        break;
        
    case STABILIZE:
        nav_roll_cd        = 0;
        nav_pitch_cd       = 0;
        // throttle is passthrough
        break;
        
    case CIRCLE:
        // we have no GPS installed and have lost radio contact
        // or we just want to fly around in a gentle circle w/o GPS,
        // holding altitude at the altitude we set when we
        // switched into the mode
        nav_roll_cd  = roll_limit_cd / 3;
        update_load_factor();
        calc_nav_pitch();
        calc_throttle();
        break;

    case MANUAL:
        SRV_Channels::set_output_scaled(SRV_Channel::k_aileron, channel_roll->get_control_in_zero_dz());
        SRV_Channels::set_output_scaled(SRV_Channel::k_elevator, channel_pitch->get_control_in_zero_dz());
        steering_control.steering = steering_control.rudder = channel_rudder->get_control_in_zero_dz();
        break;

    case QSTABILIZE:
    case QHOVER:
    case QLOITER:
    case QLAND:
    case QRTL: {
        // set nav_roll and nav_pitch using sticks
        int16_t roll_limit = MIN(roll_limit_cd, quadplane.aparm.angle_max);
        nav_roll_cd  = (channel_roll->get_control_in() / 4500.0) * roll_limit;
        nav_roll_cd = constrain_int32(nav_roll_cd, -roll_limit, roll_limit);
        float pitch_input = channel_pitch->norm_input();
        // Scale from normalized input [-1,1] to centidegrees
        if (quadplane.tailsitter_active()) {
            // For tailsitters, the pitch range is symmetrical: [-Q_ANGLE_MAX,Q_ANGLE_MAX]
            nav_pitch_cd = pitch_input * quadplane.aparm.angle_max;
        } else {
            // pitch is further constrained by LIM_PITCH_MIN/MAX which may impose
            // tighter (possibly asymmetrical) limits than Q_ANGLE_MAX
            if (pitch_input > 0) {
                nav_pitch_cd = pitch_input * MIN(aparm.pitch_limit_max_cd, quadplane.aparm.angle_max);
            } else {
                nav_pitch_cd = pitch_input * MIN(-pitch_limit_min_cd, quadplane.aparm.angle_max);
            }
            nav_pitch_cd = constrain_int32(nav_pitch_cd, pitch_limit_min_cd, aparm.pitch_limit_max_cd.get());
        }
        break;
    }
        
    case INITIALISING:
        // handled elsewhere
        break;
    }
}