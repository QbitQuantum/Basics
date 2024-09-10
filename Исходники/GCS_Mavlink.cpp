void GCS_MAVLINK_Rover::handleMessage(mavlink_message_t* msg)
{
    switch (msg->msgid) {

    case MAVLINK_MSG_ID_REQUEST_DATA_STREAM:
        {
            handle_request_data_stream(msg, true);
            break;
        }

    case MAVLINK_MSG_ID_COMMAND_LONG:
        {
            // decode
            mavlink_command_long_t packet;
            mavlink_msg_command_long_decode(msg, &packet);

            uint8_t result = MAV_RESULT_UNSUPPORTED;

            // do command

            switch(packet.command) {

            case MAV_CMD_START_RX_PAIR:
                // initiate bind procedure
                if (!hal.rcin->rc_bind(packet.param1)) {
                    result = MAV_RESULT_FAILED;
                } else {
                    result = MAV_RESULT_ACCEPTED;
                }
                break;

            case MAV_CMD_NAV_RETURN_TO_LAUNCH:
                rover.set_mode(RTL);
                result = MAV_RESULT_ACCEPTED;
                break;

#if MOUNT == ENABLED
            // Sets the region of interest (ROI) for the camera
            case MAV_CMD_DO_SET_ROI:
                // sanity check location
                if (!check_latlng(packet.param5, packet.param6)) {
                    break;
                }
                Location roi_loc;
                roi_loc.lat = (int32_t)(packet.param5 * 1.0e7f);
                roi_loc.lng = (int32_t)(packet.param6 * 1.0e7f);
                roi_loc.alt = (int32_t)(packet.param7 * 100.0f);
                if (roi_loc.lat == 0 && roi_loc.lng == 0 && roi_loc.alt == 0) {
                    // switch off the camera tracking if enabled
                    if (rover.camera_mount.get_mode() == MAV_MOUNT_MODE_GPS_POINT) {
                        rover.camera_mount.set_mode_to_default();
                    }
                } else {
                    // send the command to the camera mount
                    rover.camera_mount.set_roi_target(roi_loc);
                }
                result = MAV_RESULT_ACCEPTED;
                break;
#endif

#if CAMERA == ENABLED
        case MAV_CMD_DO_DIGICAM_CONFIGURE:
            rover.camera.configure(packet.param1,
                                   packet.param2,
                                   packet.param3,
                                   packet.param4,
                                   packet.param5,
                                   packet.param6,
                                   packet.param7);

            result = MAV_RESULT_ACCEPTED;
            break;

        case MAV_CMD_DO_DIGICAM_CONTROL:
            if (rover.camera.control(packet.param1,
                                     packet.param2,
                                     packet.param3,
                                     packet.param4,
                                     packet.param5,
                                     packet.param6)) {
                rover.log_picture();
            }
            result = MAV_RESULT_ACCEPTED;
            break;
#endif // CAMERA == ENABLED

            case MAV_CMD_DO_MOUNT_CONTROL:
#if MOUNT == ENABLED
                rover.camera_mount.control(packet.param1, packet.param2, packet.param3, (MAV_MOUNT_MODE) packet.param7);
                result = MAV_RESULT_ACCEPTED;
#endif
                break;

            case MAV_CMD_MISSION_START:
                rover.set_mode(AUTO);
                result = MAV_RESULT_ACCEPTED;
                break;

            case MAV_CMD_PREFLIGHT_CALIBRATION:
                if(hal.util->get_soft_armed()) {
                    result = MAV_RESULT_FAILED;
                    break;
                }
                if (is_equal(packet.param1,1.0f)) {
                    rover.ins.init_gyro();
                    if (rover.ins.gyro_calibrated_ok_all()) {
                        rover.ahrs.reset_gyro_drift();
                        result = MAV_RESULT_ACCEPTED;
                    } else {
                        result = MAV_RESULT_FAILED;
                    }
                } else if (is_equal(packet.param3,1.0f)) {
                    rover.init_barometer(false);
                    result = MAV_RESULT_ACCEPTED;
                } else if (is_equal(packet.param4,1.0f)) {
                    rover.trim_radio();
                    result = MAV_RESULT_ACCEPTED;
                } else if (is_equal(packet.param5,1.0f)) {
                    result = MAV_RESULT_ACCEPTED;
                    // start with gyro calibration
                    rover.ins.init_gyro();
                    // reset ahrs gyro bias
                    if (rover.ins.gyro_calibrated_ok_all()) {
                        rover.ahrs.reset_gyro_drift();
                    } else {
                        result = MAV_RESULT_FAILED;
                    }
                    rover.ins.acal_init();
                    rover.ins.get_acal()->start(this);

                } else if (is_equal(packet.param5,2.0f)) {
                    // start with gyro calibration
                    rover.ins.init_gyro();
                    // accel trim
                    float trim_roll, trim_pitch;
                    if(rover.ins.calibrate_trim(trim_roll, trim_pitch)) {
                        // reset ahrs's trim to suggested values from calibration routine
                        rover.ahrs.set_trim(Vector3f(trim_roll, trim_pitch, 0));
                        result = MAV_RESULT_ACCEPTED;
                    } else {
                        result = MAV_RESULT_FAILED;
                    }
                }
                else {
                    send_text(MAV_SEVERITY_WARNING, "Unsupported preflight calibration");
                }
                break;

        case MAV_CMD_PREFLIGHT_SET_SENSOR_OFFSETS:
            {
                uint8_t compassNumber = -1;
                if (is_equal(packet.param1, 2.0f)) {
                    compassNumber = 0;
                } else if (is_equal(packet.param1, 5.0f)) {
                    compassNumber = 1;
                } else if (is_equal(packet.param1, 6.0f)) {
                    compassNumber = 2;
                }
                if (compassNumber != (uint8_t) -1) {
                    rover.compass.set_and_save_offsets(compassNumber, packet.param2, packet.param3, packet.param4);
                    result = MAV_RESULT_ACCEPTED;
                }
                break;
            }

        case MAV_CMD_DO_SET_MODE:
            switch ((uint16_t)packet.param1) {
            case MAV_MODE_MANUAL_ARMED:
            case MAV_MODE_MANUAL_DISARMED:
                rover.set_mode(MANUAL);
                result = MAV_RESULT_ACCEPTED;
                break;

            case MAV_MODE_AUTO_ARMED:
            case MAV_MODE_AUTO_DISARMED:
                rover.set_mode(AUTO);
                result = MAV_RESULT_ACCEPTED;
                break;

            case MAV_MODE_STABILIZE_DISARMED:
            case MAV_MODE_STABILIZE_ARMED:
                rover.set_mode(LEARNING);
                result = MAV_RESULT_ACCEPTED;
                break;

            default:
                result = MAV_RESULT_UNSUPPORTED;
            }
            break;

        case MAV_CMD_DO_SET_SERVO:
            if (rover.ServoRelayEvents.do_set_servo(packet.param1, packet.param2)) {
                result = MAV_RESULT_ACCEPTED;
            }
            break;

        case MAV_CMD_DO_REPEAT_SERVO:
            if (rover.ServoRelayEvents.do_repeat_servo(packet.param1, packet.param2, packet.param3, packet.param4*1000)) {
                result = MAV_RESULT_ACCEPTED;
            }
            break;

        case MAV_CMD_DO_SET_RELAY:
            if (rover.ServoRelayEvents.do_set_relay(packet.param1, packet.param2)) {
                result = MAV_RESULT_ACCEPTED;
            }
            break;

        case MAV_CMD_DO_REPEAT_RELAY:
            if (rover.ServoRelayEvents.do_repeat_relay(packet.param1, packet.param2, packet.param3*1000)) {
                result = MAV_RESULT_ACCEPTED;
            }
            break;

        case MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN:
            if (is_equal(packet.param1,1.0f) || is_equal(packet.param1,3.0f)) {
                // when packet.param1 == 3 we reboot to hold in bootloader
                hal.scheduler->reboot(is_equal(packet.param1,3.0f));
                result = MAV_RESULT_ACCEPTED;
            }
            break;

        case MAV_CMD_COMPONENT_ARM_DISARM:
            if (is_equal(packet.param1,1.0f)) {
                // run pre_arm_checks and arm_checks and display failures
                if (rover.arm_motors(AP_Arming::MAVLINK)) {
                    result = MAV_RESULT_ACCEPTED;
                } else {
                    result = MAV_RESULT_FAILED;
                }
            } else if (is_zero(packet.param1))  {
                if (rover.disarm_motors()) {
                    result = MAV_RESULT_ACCEPTED;
                } else {
                    result = MAV_RESULT_FAILED;
                }
            } else {
                result = MAV_RESULT_UNSUPPORTED;
            }
            break;

        case MAV_CMD_GET_HOME_POSITION:
            if (rover.home_is_set != HOME_UNSET) {
                send_home(rover.ahrs.get_home());
                result = MAV_RESULT_ACCEPTED;
            }
            break;

        case MAV_CMD_REQUEST_AUTOPILOT_CAPABILITIES: {
            if (is_equal(packet.param1,1.0f)) {
                send_autopilot_version(FIRMWARE_VERSION);
                result = MAV_RESULT_ACCEPTED;
            }
            break;
        }

        case MAV_CMD_DO_SET_HOME:
        {
            // param1 : use current (1=use current location, 0=use specified location)
            // param5 : latitude
            // param6 : longitude
            // param7 : altitude
            result = MAV_RESULT_FAILED; // assume failure
            if (is_equal(packet.param1,1.0f)) {
                rover.init_home();
            } else {
                if (is_zero(packet.param5) && is_zero(packet.param6) && is_zero(packet.param7)) {
                    // don't allow the 0,0 position
                    break;
                }
                // sanity check location
                if (!check_latlng(packet.param5, packet.param6)) {
                    break;
                }
                Location new_home_loc {};
                new_home_loc.lat = (int32_t)(packet.param5 * 1.0e7f);
                new_home_loc.lng = (int32_t)(packet.param6 * 1.0e7f);
                new_home_loc.alt = (int32_t)(packet.param7 * 100.0f);
                rover.ahrs.set_home(new_home_loc);
                rover.home_is_set = HOME_SET_NOT_LOCKED;
                rover.Log_Write_Home_And_Origin();
                GCS_MAVLINK::send_home_all(new_home_loc);
                result = MAV_RESULT_ACCEPTED;
                rover.gcs_send_text_fmt(MAV_SEVERITY_INFO, "Set HOME to %.6f %.6f at %um",
                                        (double)(new_home_loc.lat*1.0e-7f),
                                        (double)(new_home_loc.lng*1.0e-7f),
                                        (uint32_t)(new_home_loc.alt*0.01f));
            }
            break;
        }

        case MAV_CMD_DO_START_MAG_CAL:
        case MAV_CMD_DO_ACCEPT_MAG_CAL:
        case MAV_CMD_DO_CANCEL_MAG_CAL:
            result = rover.compass.handle_mag_cal_command(packet);
            break;

        default:
                break;
            }

            mavlink_msg_command_ack_send_buf(
                msg,
                chan,
                packet.command,
                result);

            break;
        }

    case MAVLINK_MSG_ID_SET_MODE:
		{
            handle_set_mode(msg, FUNCTOR_BIND(&rover, &Rover::mavlink_set_mode, bool, uint8_t));
            break;
        }

    case MAVLINK_MSG_ID_MISSION_REQUEST_LIST:
        {
            handle_mission_request_list(rover.mission, msg);
            break;
        }


	// XXX read a WP from EEPROM and send it to the GCS
    case MAVLINK_MSG_ID_MISSION_REQUEST_INT:
    case MAVLINK_MSG_ID_MISSION_REQUEST:
    {
        handle_mission_request(rover.mission, msg);
        break;
    }


    case MAVLINK_MSG_ID_MISSION_ACK:
        {
            // not used
            break;
        }

    case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
        {
            // mark the firmware version in the tlog
            send_text(MAV_SEVERITY_INFO, FIRMWARE_STRING);

#if defined(PX4_GIT_VERSION) && defined(NUTTX_GIT_VERSION)
            send_text(MAV_SEVERITY_INFO, "PX4: " PX4_GIT_VERSION " NuttX: " NUTTX_GIT_VERSION);
#endif
            handle_param_request_list(msg);
            break;
        }

    case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
    {
        handle_param_request_read(msg);
        break;
    }

    case MAVLINK_MSG_ID_MISSION_CLEAR_ALL:
        {
            handle_mission_clear_all(rover.mission, msg);
            break;
        }

    case MAVLINK_MSG_ID_MISSION_SET_CURRENT:
        {
            handle_mission_set_current(rover.mission, msg);
            break;
        }

    case MAVLINK_MSG_ID_MISSION_COUNT:
        {
            handle_mission_count(rover.mission, msg);
            break;
        }

    case MAVLINK_MSG_ID_MISSION_WRITE_PARTIAL_LIST:
    {
        handle_mission_write_partial_list(rover.mission, msg);
        break;
    }

    // GCS has sent us a mission item, store to EEPROM
    case MAVLINK_MSG_ID_MISSION_ITEM:
    {
        if (handle_mission_item(msg, rover.mission)) {
            rover.DataFlash.Log_Write_EntireMission(rover.mission);
        }
        break;
    }

    case MAVLINK_MSG_ID_MISSION_ITEM_INT:
    {
        if (handle_mission_item(msg, rover.mission)) {
            rover.DataFlash.Log_Write_EntireMission(rover.mission);
        }
        break;
    }

    case MAVLINK_MSG_ID_PARAM_SET:
    {
        handle_param_set(msg, &rover.DataFlash);
        break;
    }

    case MAVLINK_MSG_ID_RC_CHANNELS_OVERRIDE:
    {
        // allow override of RC channel values for HIL
        // or for complete GCS control of switch position
        // and RC PWM values.
        if(msg->sysid != rover.g.sysid_my_gcs) break;                         // Only accept control from our gcs
        mavlink_rc_channels_override_t packet;
        int16_t v[8];
        mavlink_msg_rc_channels_override_decode(msg, &packet);

        v[0] = packet.chan1_raw;
        v[1] = packet.chan2_raw;
        v[2] = packet.chan3_raw;
        v[3] = packet.chan4_raw;
        v[4] = packet.chan5_raw;
        v[5] = packet.chan6_raw;
        v[6] = packet.chan7_raw;
        v[7] = packet.chan8_raw;

        hal.rcin->set_overrides(v, 8);

        rover.failsafe.rc_override_timer = AP_HAL::millis();
        rover.failsafe_trigger(FAILSAFE_EVENT_RC, false);
        break;
    }

    case MAVLINK_MSG_ID_HEARTBEAT:
        {
            // We keep track of the last time we received a heartbeat from our GCS for failsafe purposes
			if(msg->sysid != rover.g.sysid_my_gcs) break;
            rover.last_heartbeat_ms = rover.failsafe.rc_override_timer = AP_HAL::millis();
            rover.failsafe_trigger(FAILSAFE_EVENT_GCS, false);
            break;
        }

    case MAVLINK_MSG_ID_GPS_INPUT:
        {
            rover.gps.handle_msg(msg);
            break;
        }

#if HIL_MODE != HIL_MODE_DISABLED
	case MAVLINK_MSG_ID_HIL_STATE:
		{
			mavlink_hil_state_t packet;
			mavlink_msg_hil_state_decode(msg, &packet);
			
            // sanity check location
            if (!check_latlng(packet.lat, packet.lon)) {
                break;
            }

            // set gps hil sensor
            Location loc;
            loc.lat = packet.lat;
            loc.lng = packet.lon;
            loc.alt = packet.alt/10;
            Vector3f vel(packet.vx, packet.vy, packet.vz);
            vel *= 0.01f;
            
            gps.setHIL(0, AP_GPS::GPS_OK_FIX_3D,
                       packet.time_usec/1000,
                       loc, vel, 10, 0);
			
			// rad/sec
            Vector3f gyros;
            gyros.x = packet.rollspeed;
            gyros.y = packet.pitchspeed;
            gyros.z = packet.yawspeed;

            // m/s/s
            Vector3f accels;
            accels.x = packet.xacc * (GRAVITY_MSS/1000.0f);
            accels.y = packet.yacc * (GRAVITY_MSS/1000.0f);
            accels.z = packet.zacc * (GRAVITY_MSS/1000.0f);
            
            ins.set_gyro(0, gyros);

            ins.set_accel(0, accels);
            compass.setHIL(0, packet.roll, packet.pitch, packet.yaw);
            compass.setHIL(1, packet.roll, packet.pitch, packet.yaw);
            break;
		}
#endif // HIL_MODE

#if CAMERA == ENABLED
    //deprecated. Use MAV_CMD_DO_DIGICAM_CONFIGURE
    case MAVLINK_MSG_ID_DIGICAM_CONFIGURE:
    {
        break;
    }

    //deprecated. Use MAV_CMD_DO_DIGICAM_CONFIGURE
    case MAVLINK_MSG_ID_DIGICAM_CONTROL:
    {
        rover.camera.control_msg(msg);
        rover.log_picture();
        break;
    }
#endif // CAMERA == ENABLED

#if MOUNT == ENABLED
    //deprecated. Use MAV_CMD_DO_MOUNT_CONFIGURE
    case MAVLINK_MSG_ID_MOUNT_CONFIGURE:
		{
			rover.camera_mount.configure_msg(msg);
			break;
		}

    //deprecated. Use MAV_CMD_DO_MOUNT_CONTROL
    case MAVLINK_MSG_ID_MOUNT_CONTROL:
		{
			rover.camera_mount.control_msg(msg);
			break;
		}
#endif // MOUNT == ENABLED

    case MAVLINK_MSG_ID_RADIO:
    case MAVLINK_MSG_ID_RADIO_STATUS:
        {
            handle_radio_status(msg, rover.DataFlash, rover.should_log(MASK_LOG_PM));
            break;
        }

    case MAVLINK_MSG_ID_LOG_REQUEST_DATA:
    case MAVLINK_MSG_ID_LOG_ERASE:
        rover.in_log_download = true;
        /* no break */
    case MAVLINK_MSG_ID_LOG_REQUEST_LIST:
        if (!rover.in_mavlink_delay) {
            handle_log_message(msg, rover.DataFlash);
        }
        break;
    case MAVLINK_MSG_ID_LOG_REQUEST_END:
        rover.in_log_download = false;
        if (!rover.in_mavlink_delay) {
            handle_log_message(msg, rover.DataFlash);
        }
        break;

    case MAVLINK_MSG_ID_SERIAL_CONTROL:
        handle_serial_control(msg, rover.gps);
        break;

    case MAVLINK_MSG_ID_GPS_INJECT_DATA:
        handle_gps_inject(msg, rover.gps);
        break;

    case MAVLINK_MSG_ID_DISTANCE_SENSOR:
        rover.sonar.handle_msg(msg);
        break;

    case MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS:
        rover.DataFlash.remote_log_block_status_msg(chan, msg);
        break;

    case MAVLINK_MSG_ID_AUTOPILOT_VERSION_REQUEST:
        send_autopilot_version(FIRMWARE_VERSION);
        break;

    case MAVLINK_MSG_ID_SETUP_SIGNING:
        handle_setup_signing(msg);
        break;

    case MAVLINK_MSG_ID_LED_CONTROL:
        // send message to Notify
        AP_Notify::handle_led_control(msg);
        break;

    case MAVLINK_MSG_ID_PLAY_TUNE:
        // send message to Notify
        AP_Notify::handle_play_tune(msg);
        break;
    } // end switch
} // end handle mavlink