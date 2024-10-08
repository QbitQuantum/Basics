static void uavoMavlinkBridgeTask(void *parameters) {
	uint32_t lastSysTime;
	// Main task loop
	lastSysTime = PIOS_Thread_Systime();

	FlightBatterySettingsData batSettings = {};

	if (FlightBatterySettingsHandle() != NULL )
		FlightBatterySettingsGet(&batSettings);

	SystemStatsData systemStats;

	while (1) {
		PIOS_Thread_Sleep_Until(&lastSysTime, 1000 / TASK_RATE_HZ);

		if (stream_trigger(MAV_DATA_STREAM_EXTENDED_STATUS)) {
			FlightBatteryStateData batState = {};

			if (FlightBatteryStateHandle() != NULL )
				FlightBatteryStateGet(&batState);

			SystemStatsGet(&systemStats);

			int8_t battery_remaining = 0;
			if (batSettings.Capacity != 0) {
				if (batState.ConsumedEnergy < batSettings.Capacity) {
					battery_remaining = 100 - lroundf(batState.ConsumedEnergy / batSettings.Capacity * 100);
				}
			}

			uint16_t voltage = 0;
			if (batSettings.VoltagePin != FLIGHTBATTERYSETTINGS_VOLTAGEPIN_NONE)
				voltage = lroundf(batState.Voltage * 1000);

			uint16_t current = 0;
			if (batSettings.CurrentPin != FLIGHTBATTERYSETTINGS_CURRENTPIN_NONE)
				current = lroundf(batState.Current * 100);

			mavlink_msg_sys_status_pack(0, 200, mav_msg,
					// onboard_control_sensors_present Bitmask showing which onboard controllers and sensors are present. Value of 0: not present. Value of 1: present. Indices: 0: 3D gyro, 1: 3D acc, 2: 3D mag, 3: absolute pressure, 4: differential pressure, 5: GPS, 6: optical flow, 7: computer vision position, 8: laser based position, 9: external ground-truth (Vicon or Leica). Controllers: 10: 3D angular rate control 11: attitude stabilization, 12: yaw position, 13: z/altitude control, 14: x/y position control, 15: motor outputs / control
					0,
					// onboard_control_sensors_enabled Bitmask showing which onboard controllers and sensors are enabled:  Value of 0: not enabled. Value of 1: enabled. Indices: 0: 3D gyro, 1: 3D acc, 2: 3D mag, 3: absolute pressure, 4: differential pressure, 5: GPS, 6: optical flow, 7: computer vision position, 8: laser based position, 9: external ground-truth (Vicon or Leica). Controllers: 10: 3D angular rate control 11: attitude stabilization, 12: yaw position, 13: z/altitude control, 14: x/y position control, 15: motor outputs / control
					0,
					// onboard_control_sensors_health Bitmask showing which onboard controllers and sensors are operational or have an error:  Value of 0: not enabled. Value of 1: enabled. Indices: 0: 3D gyro, 1: 3D acc, 2: 3D mag, 3: absolute pressure, 4: differential pressure, 5: GPS, 6: optical flow, 7: computer vision position, 8: laser based position, 9: external ground-truth (Vicon or Leica). Controllers: 10: 3D angular rate control 11: attitude stabilization, 12: yaw position, 13: z/altitude control, 14: x/y position control, 15: motor outputs / control
					0,
					// load Maximum usage in percent of the mainloop time, (0%: 0, 100%: 1000) should be always below 1000
					(uint16_t)systemStats.CPULoad * 10,
					// voltage_battery Battery voltage, in millivolts (1 = 1 millivolt)
					voltage,
					// current_battery Battery current, in 10*milliamperes (1 = 10 milliampere), -1: autopilot does not measure the current
					current,
					// battery_remaining Remaining battery energy: (0%: 0, 100%: 100), -1: autopilot estimate the remaining battery
					battery_remaining,
					// drop_rate_comm Communication drops in percent, (0%: 0, 100%: 10'000), (UART, I2C, SPI, CAN), dropped packets on all links (packets that were corrupted on reception on the MAV)
					0,
					// errors_comm Communication errors (UART, I2C, SPI, CAN), dropped packets on all links (packets that were corrupted on reception on the MAV)
					0,
					// errors_count1 Autopilot-specific errors
					0,
					// errors_count2 Autopilot-specific errors
					0,
					// errors_count3 Autopilot-specific errors
					0,
					// errors_count4 Autopilot-specific errors
					0);

			send_message();
		}

		if (stream_trigger(MAV_DATA_STREAM_RC_CHANNELS)) {
			ManualControlCommandData manualState;
			FlightStatusData flightStatus;

			ManualControlCommandGet(&manualState);
			FlightStatusGet(&flightStatus);
			SystemStatsGet(&systemStats);

			//TODO connect with RSSI object and pass in last argument
			mavlink_msg_rc_channels_raw_pack(0, 200, mav_msg,
					// time_boot_ms Timestamp (milliseconds since system boot)
					systemStats.FlightTime,
					// port Servo output port (set of 8 outputs = 1 port). Most MAVs will just use one, but this allows to encode more than 8 servos.
					0,
					// chan1_raw RC channel 1 value, in microseconds
					manualState.Channel[0],
					// chan2_raw RC channel 2 value, in microseconds
					manualState.Channel[1],
					// chan3_raw RC channel 3 value, in microseconds
					manualState.Channel[2],
					// chan4_raw RC channel 4 value, in microseconds
					manualState.Channel[3],
					// chan5_raw RC channel 5 value, in microseconds
					manualState.Channel[4],
					// chan6_raw RC channel 6 value, in microseconds
					manualState.Channel[5],
					// chan7_raw RC channel 7 value, in microseconds
					manualState.Channel[6],
					// chan8_raw RC channel 8 value, in microseconds
					manualState.Channel[7],
					// rssi Receive signal strength indicator, 0: 0%, 255: 100%
					manualState.Rssi);

			send_message();
		}

		if (stream_trigger(MAV_DATA_STREAM_POSITION)) {
			GPSPositionData gpsPosData = {};
			HomeLocationData homeLocation = {};
			SystemStatsGet(&systemStats);

			if (GPSPositionHandle() != NULL )
				GPSPositionGet(&gpsPosData);
			if (HomeLocationHandle() != NULL )
				HomeLocationGet(&homeLocation);
			SystemStatsGet(&systemStats);

			uint8_t gps_fix_type;
			switch (gpsPosData.Status)
			{
			case GPSPOSITION_STATUS_NOGPS:
				gps_fix_type = 0;
				break;
			case GPSPOSITION_STATUS_NOFIX:
				gps_fix_type = 1;
				break;
			case GPSPOSITION_STATUS_FIX2D:
				gps_fix_type = 2;
				break;
			case GPSPOSITION_STATUS_FIX3D:
			case GPSPOSITION_STATUS_DIFF3D:
				gps_fix_type = 3;
				break;
			default:
				gps_fix_type = 0;
				break;
			}

			mavlink_msg_gps_raw_int_pack(0, 200, mav_msg,
					// time_usec Timestamp (microseconds since UNIX epoch or microseconds since system boot)
					(uint64_t)systemStats.FlightTime * 1000,
					// fix_type 0-1: no fix, 2: 2D fix, 3: 3D fix. Some applications will not use the value of this field unless it is at least two, so always correctly fill in the fix.
					gps_fix_type,
					// lat Latitude in 1E7 degrees
					gpsPosData.Latitude,
					// lon Longitude in 1E7 degrees
					gpsPosData.Longitude,
					// alt Altitude in 1E3 meters (millimeters) above MSL
					gpsPosData.Altitude * 1000,
					// eph GPS HDOP horizontal dilution of position in cm (m*100). If unknown, set to: 65535
					gpsPosData.HDOP * 100,
					// epv GPS VDOP horizontal dilution of position in cm (m*100). If unknown, set to: 65535
					gpsPosData.VDOP * 100,
					// vel GPS ground speed (m/s * 100). If unknown, set to: 65535
					gpsPosData.Groundspeed * 100,
					// cog Course over ground (NOT heading, but direction of movement) in degrees * 100, 0.0..359.99 degrees. If unknown, set to: 65535
					gpsPosData.Heading * 100,
					// satellites_visible Number of satellites visible. If unknown, set to 255
					gpsPosData.Satellites);

			send_message();

			mavlink_msg_gps_global_origin_pack(0, 200, mav_msg,
					// latitude Latitude (WGS84), expressed as * 1E7
					homeLocation.Latitude,
					// longitude Longitude (WGS84), expressed as * 1E7
					homeLocation.Longitude,
					// altitude Altitude(WGS84), expressed as * 1000
					homeLocation.Altitude * 1000);

			send_message();

			//TODO add waypoint nav stuff
			//wp_target_bearing
			//wp_dist = mavlink_msg_nav_controller_output_get_wp_dist(&msg);
			//alt_error = mavlink_msg_nav_controller_output_get_alt_error(&msg);
			//aspd_error = mavlink_msg_nav_controller_output_get_aspd_error(&msg);
			//xtrack_error = mavlink_msg_nav_controller_output_get_xtrack_error(&msg);
			//mavlink_msg_nav_controller_output_pack
			//wp_number
			//mavlink_msg_mission_current_pack
		}

		if (stream_trigger(MAV_DATA_STREAM_EXTRA1)) {
			AttitudeActualData attActual;
			SystemStatsData systemStats;

			AttitudeActualGet(&attActual);
			SystemStatsGet(&systemStats);

			mavlink_msg_attitude_pack(0, 200, mav_msg,
					// time_boot_ms Timestamp (milliseconds since system boot)
					systemStats.FlightTime,
					// roll Roll angle (rad)
					attActual.Roll * DEG2RAD,
					// pitch Pitch angle (rad)
					attActual.Pitch * DEG2RAD,
					// yaw Yaw angle (rad)
					attActual.Yaw * DEG2RAD,
					// rollspeed Roll angular speed (rad/s)
					0,
					// pitchspeed Pitch angular speed (rad/s)
					0,
					// yawspeed Yaw angular speed (rad/s)
					0);

			send_message();
		}

		if (stream_trigger(MAV_DATA_STREAM_EXTRA2)) {
			ActuatorDesiredData actDesired;
			AttitudeActualData attActual;
			AirspeedActualData airspeedActual = {};
			GPSPositionData gpsPosData = {};
			BaroAltitudeData baroAltitude = {};
			FlightStatusData flightStatus;

			if (AirspeedActualHandle() != NULL )
				AirspeedActualGet(&airspeedActual);
			if (GPSPositionHandle() != NULL )
				GPSPositionGet(&gpsPosData);
			if (BaroAltitudeHandle() != NULL )
				BaroAltitudeGet(&baroAltitude);
			ActuatorDesiredGet(&actDesired);
			AttitudeActualGet(&attActual);
			FlightStatusGet(&flightStatus);

			float altitude = 0;
			if (BaroAltitudeHandle() != NULL)
				altitude = baroAltitude.Altitude;
			else if (GPSPositionHandle() != NULL)
				altitude = gpsPosData.Altitude;

			// round attActual.Yaw to nearest int and transfer from (-180 ... 180) to (0 ... 360)
			int16_t heading = lroundf(attActual.Yaw);
			if (heading < 0)
				heading += 360;

			mavlink_msg_vfr_hud_pack(0, 200, mav_msg,
					// airspeed Current airspeed in m/s
					airspeedActual.TrueAirspeed,
					// groundspeed Current ground speed in m/s
					gpsPosData.Groundspeed,
					// heading Current heading in degrees, in compass units (0..360, 0=north)
					heading,
					// throttle Current throttle setting in integer percent, 0 to 100
					actDesired.Throttle * 100,
					// alt Current altitude (MSL), in meters
					altitude,
					// climb Current climb rate in meters/second
					0);

			send_message();

			uint8_t armed_mode = 0;
			if (flightStatus.Armed == FLIGHTSTATUS_ARMED_ARMED)
				armed_mode |= MAV_MODE_FLAG_SAFETY_ARMED;

			uint8_t custom_mode = CUSTOM_MODE_STAB;

			switch (flightStatus.FlightMode) {
				case FLIGHTSTATUS_FLIGHTMODE_MANUAL:
				case FLIGHTSTATUS_FLIGHTMODE_MWRATE:
				case FLIGHTSTATUS_FLIGHTMODE_VIRTUALBAR:
				case FLIGHTSTATUS_FLIGHTMODE_HORIZON:
					/* Kinda a catch all */
					custom_mode = CUSTOM_MODE_SPORT;
					break;
				case FLIGHTSTATUS_FLIGHTMODE_ACRO:
				case FLIGHTSTATUS_FLIGHTMODE_AXISLOCK:
					custom_mode = CUSTOM_MODE_ACRO;
					break;
				case FLIGHTSTATUS_FLIGHTMODE_STABILIZED1:
				case FLIGHTSTATUS_FLIGHTMODE_STABILIZED2:
				case FLIGHTSTATUS_FLIGHTMODE_STABILIZED3:
					/* May want these three to try and
					 * infer based on roll axis */
				case FLIGHTSTATUS_FLIGHTMODE_LEVELING:
					custom_mode = CUSTOM_MODE_STAB;
					break;
				case FLIGHTSTATUS_FLIGHTMODE_AUTOTUNE:
					custom_mode = CUSTOM_MODE_DRIFT;
					break;
				case FLIGHTSTATUS_FLIGHTMODE_ALTITUDEHOLD:
					custom_mode = CUSTOM_MODE_ALTH;
					break;
				case FLIGHTSTATUS_FLIGHTMODE_RETURNTOHOME:
					custom_mode = CUSTOM_MODE_RTL;
					break;
				case FLIGHTSTATUS_FLIGHTMODE_TABLETCONTROL:
				case FLIGHTSTATUS_FLIGHTMODE_POSITIONHOLD:
					custom_mode = CUSTOM_MODE_POSH;
					break;
				case FLIGHTSTATUS_FLIGHTMODE_PATHPLANNER:
					custom_mode = CUSTOM_MODE_AUTO;
					break;
			}

			mavlink_msg_heartbeat_pack(0, 200, mav_msg,
					// type Type of the MAV (quadrotor, helicopter, etc., up to 15 types, defined in MAV_TYPE ENUM)
					MAV_TYPE_GENERIC,
					// autopilot Autopilot type / class. defined in MAV_AUTOPILOT ENUM
					MAV_AUTOPILOT_GENERIC,
					// base_mode System mode bitfield, see MAV_MODE_FLAGS ENUM in mavlink/include/mavlink_types.h
					armed_mode,
					// custom_mode A bitfield for use for autopilot-specific flags.
					custom_mode,
					// system_status System status flag, see MAV_STATE ENUM
					0);

			send_message();
		}
	}
}