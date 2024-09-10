// perform pre-arm checks and set ap.pre_arm_check flag
//  return true if the checks pass successfully
bool Copter::pre_arm_checks(bool display_failure)
{
    // exit immediately if already armed
    if (motors.armed()) {
        return true;
    }

    // check if motor interlock and Emergency Stop aux switches are used
    // at the same time.  This cannot be allowed.
    if (check_if_auxsw_mode_used(AUXSW_MOTOR_INTERLOCK) && check_if_auxsw_mode_used(AUXSW_MOTOR_ESTOP)){
        if (display_failure) {
            gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Interlock/E-Stop Conflict");
        }
        return false;
    }

    // check if motor interlock aux switch is in use
    // if it is, switch needs to be in disabled position to arm
    // otherwise exit immediately.  This check to be repeated,
    // as state can change at any time.
    if (ap.using_interlock && motors.get_interlock()){
        if (display_failure) {
            gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Motor Interlock Enabled");
        }
        return false;
    }

    // exit immediately if we've already successfully performed the pre-arm check
    if (ap.pre_arm_check) {
        // run gps checks because results may change and affect LED colour
        // no need to display failures because arm_checks will do that if the pilot tries to arm
        pre_arm_gps_checks(false);
        return true;
    }

    // succeed if pre arm checks are disabled
    if (g.arming_check == ARMING_CHECK_NONE) {
        set_pre_arm_check(true);
        set_pre_arm_rc_check(true);
        return true;
    }

    // pre-arm rc checks a prerequisite
    pre_arm_rc_checks();
    if (!ap.pre_arm_rc_check) {
        if (display_failure) {
            gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: RC not calibrated");
        }
        return false;
    }
    // check Baro
    if ((g.arming_check == ARMING_CHECK_ALL) || (g.arming_check & ARMING_CHECK_BARO)) {
        // barometer health check
        if (!barometer.all_healthy()) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Barometer not healthy");
            }
            return false;
        }
        // Check baro & inav alt are within 1m if EKF is operating in an absolute position mode.
        // Do not check if intending to operate in a ground relative height mode as EKF will output a ground relative height
        // that may differ from the baro height due to baro drift.
        nav_filter_status filt_status = inertial_nav.get_filter_status();
        bool using_baro_ref = (!filt_status.flags.pred_horiz_pos_rel && filt_status.flags.pred_horiz_pos_abs);
        if (using_baro_ref) {
            if (fabsf(inertial_nav.get_altitude() - baro_alt) > PREARM_MAX_ALT_DISPARITY_CM) {
                if (display_failure) {
                    gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Altitude disparity");
                }
                return false;
            }
        }
    }

    // check Compass
    if ((g.arming_check == ARMING_CHECK_ALL) || (g.arming_check & ARMING_CHECK_COMPASS)) {
        //check if compass has calibrated and requires reboot
        if (compass.compass_cal_requires_reboot()) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL, "PreArm: Compass calibrated requires reboot");
            }
            return false;
        }

        // check the primary compass is healthy
        if (!compass.healthy()) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Compass not healthy");
            }
            return false;
        }

        // check compass learning is on or offsets have been set
        if (!compass.configured()) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Compass not calibrated");
            }
            return false;
        }

        // check for unreasonable compass offsets
        Vector3f offsets = compass.get_offsets();
        if (offsets.length() > COMPASS_OFFSETS_MAX) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Compass offsets too high");
            }
            return false;
        }

        // check for unreasonable mag field length
        float mag_field = compass.get_field().length();
        if (mag_field > COMPASS_MAGFIELD_EXPECTED*1.65f || mag_field < COMPASS_MAGFIELD_EXPECTED*0.35f) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Check mag field");
            }
            return false;
        }

        // check all compasses point in roughly same direction
        if (!compass.consistent()) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: inconsistent compasses");
            }
            return false;
        }

    }

    // check GPS
    if (!pre_arm_gps_checks(display_failure)) {
        return false;
    }

    #if AC_FENCE == ENABLED
    // check fence is initialised
    if (!fence.pre_arm_check()) {
        if (display_failure) {
            gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: check fence");
        }
        return false;
    }
    #endif

    // check INS
    if ((g.arming_check == ARMING_CHECK_ALL) || (g.arming_check & ARMING_CHECK_INS)) {
        // check accelerometers have been calibrated
        if (!ins.accel_calibrated_ok_all()) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Accels not calibrated");
            }
            return false;
        }

        // check accels are healthy
        if (!ins.get_accel_health_all()) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Accelerometers not healthy");
            }
            return false;
        }

        //check if accelerometers have calibrated and require reboot
        if (ins.accel_cal_requires_reboot()) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL, "PreArm: Accelerometers calibrated requires reboot");
            }
            return false;
        }

        // check all accelerometers point in roughly same direction
        if (ins.get_accel_count() > 1) {
            const Vector3f &prime_accel_vec = ins.get_accel();
            for(uint8_t i=0; i<ins.get_accel_count(); i++) {
                // get next accel vector
                const Vector3f &accel_vec = ins.get_accel(i);
                Vector3f vec_diff = accel_vec - prime_accel_vec;
                float threshold = PREARM_MAX_ACCEL_VECTOR_DIFF;
                if (i >= 2) {
                    /*
                     * for boards with 3 IMUs we only use the first two
                     * in the EKF. Allow for larger accel discrepancy
                     * for IMU3 as it may be running at a different temperature
                     */
                    threshold *= 2;
                }
                if (vec_diff.length() > threshold) {
                    if (display_failure) {
                        gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: inconsistent Accelerometers");
                    }
                    return false;
                }
            }
        }

        // check gyros are healthy
        if (!ins.get_gyro_health_all()) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Gyros not healthy");
            }
            return false;
        }

        // check all gyros are consistent
        if (ins.get_gyro_count() > 1) {
            for(uint8_t i=0; i<ins.get_gyro_count(); i++) {
                // get rotation rate difference between gyro #i and primary gyro
                Vector3f vec_diff = ins.get_gyro(i) - ins.get_gyro();
                if (vec_diff.length() > PREARM_MAX_GYRO_VECTOR_DIFF) {
                    if (display_failure) {
                        gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: inconsistent Gyros");
                    }
                    return false;
                }
            }
        }

        // get ekf attitude (if bad, it's usually the gyro biases)
        if (!pre_arm_ekf_attitude_check()) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: gyros still settling");
            }
            return false;
        }
    }
    #if CONFIG_HAL_BOARD != HAL_BOARD_VRBRAIN
    #ifndef CONFIG_ARCH_BOARD_PX4FMU_V1
    // check board voltage
    if ((g.arming_check == ARMING_CHECK_ALL) || (g.arming_check & ARMING_CHECK_VOLTAGE)) {
        if (hal.analogin->board_voltage() < BOARD_VOLTAGE_MIN || hal.analogin->board_voltage() > BOARD_VOLTAGE_MAX) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Check Board Voltage");
            }
            return false;
        }
    }
    #endif
    #endif

    // check battery voltage
    if ((g.arming_check == ARMING_CHECK_ALL) || (g.arming_check & ARMING_CHECK_VOLTAGE)) {
        if (failsafe.battery || (!ap.usb_connected && battery.exhausted(g.fs_batt_voltage, g.fs_batt_mah))) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Check Battery");
            }
            return false;
        }
    }

    // check various parameter values
    if ((g.arming_check == ARMING_CHECK_ALL) || (g.arming_check & ARMING_CHECK_PARAMETERS)) {

        // ensure ch7 and ch8 have different functions
        if (check_duplicate_auxsw()) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Duplicate Aux Switch Options");
            }
            return false;
        }

        // failsafe parameter checks
        if (g.failsafe_throttle) {
            // check throttle min is above throttle failsafe trigger and that the trigger is above ppm encoder's loss-of-signal value of 900
            if (channel_throttle->radio_min <= g.failsafe_throttle_value+10 || g.failsafe_throttle_value < 910) {
                if (display_failure) {
                    gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Check FS_THR_VALUE");
                }
                return false;
            }
        }

        // lean angle parameter check
        if (aparm.angle_max < 1000 || aparm.angle_max > 8000) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Check ANGLE_MAX");
            }
            return false;
        }

        // acro balance parameter check
        if ((g.acro_balance_roll > attitude_control.get_angle_roll_p().kP()) || (g.acro_balance_pitch > attitude_control.get_angle_pitch_p().kP())) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: ACRO_BAL_ROLL/PITCH");
            }
            return false;
        }

        #if CONFIG_SONAR == ENABLED && OPTFLOW == ENABLED
        // check range finder if optflow enabled
        if (optflow.enabled() && !sonar.pre_arm_check()) {
            if (display_failure) {
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: check range finder");
            }
            return false;
        }
        #endif
        #if FRAME_CONFIG == HELI_FRAME
        // check helicopter parameters
        if (!motors.parameter_check(display_failure)) {
            return false;
        }
        #endif // HELI_FRAME

        // check for missing terrain data
        if (!pre_arm_terrain_check()) {
            gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Waiting for Terrain data");
            return false;
        }
    }

    // check throttle is above failsafe throttle
    // this is near the bottom to allow other failures to be displayed before checking pilot throttle
    if ((g.arming_check == ARMING_CHECK_ALL) || (g.arming_check & ARMING_CHECK_RC)) {
        if (g.failsafe_throttle != FS_THR_DISABLED && channel_throttle->radio_in < g.failsafe_throttle_value) {
            if (display_failure) {
                #if FRAME_CONFIG == HELI_FRAME
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Collective below Failsafe");
                #else
                gcs_send_text(MAV_SEVERITY_CRITICAL,"PreArm: Throttle below Failsafe");
                #endif
            }
            return false;
        }
    }

    return true;
}