// Determine if learning of wind and magnetic field will be enabled and set corresponding indexing limits to
// avoid unnecessary operations
void NavEKF2_core::setWindMagStateLearningMode()
{
    // If we are on ground, or in constant position mode, or don't have the right vehicle and sensing to estimate wind, inhibit wind states
    bool setWindInhibit = (!useAirspeed() && !assume_zero_sideslip()) || onGround || (PV_AidingMode == AID_NONE);
    if (!inhibitWindStates && setWindInhibit) {
        inhibitWindStates = true;
    } else if (inhibitWindStates && !setWindInhibit) {
        inhibitWindStates = false;
        // set states and variances
        if (yawAlignComplete && useAirspeed()) {
            // if we have airspeed and a valid heading, set the wind states to the reciprocal of the vehicle heading
            // which assumes the vehicle has launched into the wind
             Vector3f tempEuler;
            stateStruct.quat.to_euler(tempEuler.x, tempEuler.y, tempEuler.z);
            float windSpeed =  sqrtf(sq(stateStruct.velocity.x) + sq(stateStruct.velocity.y)) - tasDataDelayed.tas;
            stateStruct.wind_vel.x = windSpeed * cosf(tempEuler.z);
            stateStruct.wind_vel.y = windSpeed * sinf(tempEuler.z);

            // set the wind sate variances to the measurement uncertainty
            for (uint8_t index=22; index<=23; index++) {
                P[index][index] = sq(constrain_float(frontend->_easNoise, 0.5f, 5.0f) * constrain_float(_ahrs->get_EAS2TAS(), 0.9f, 10.0f));
            }
        } else {
            // set the variances using a typical wind speed
            for (uint8_t index=22; index<=23; index++) {
                P[index][index] = sq(5.0f);
            }
        }
    }

    // determine if the vehicle is manoevring
    if (accNavMagHoriz > 0.5f) {
        manoeuvring = true;
    } else {
        manoeuvring = false;
    }

    // Determine if learning of magnetic field states has been requested by the user
    uint8_t magCal = effective_magCal();
    bool magCalRequested =
            ((magCal == 0) && inFlight) || // when flying
            ((magCal == 1) && manoeuvring)  || // when manoeuvring
            ((magCal == 3) && firstInflightYawInit && firstInflightMagInit) || // when initial in-air yaw and mag field reset is complete
            (magCal == 4); // all the time

    // Deny mag calibration request if we aren't using the compass, it has been inhibited by the user,
    // we do not have an absolute position reference or are on the ground (unless explicitly requested by the user)
    bool magCalDenied = !use_compass() || (magCal == 2) || (onGround && magCal != 4);

    // Inhibit the magnetic field calibration if not requested or denied
    bool setMagInhibit = !magCalRequested || magCalDenied;
    if (!inhibitMagStates && setMagInhibit) {
        inhibitMagStates = true;
    } else if (inhibitMagStates && !setMagInhibit) {
        inhibitMagStates = false;
        // when commencing use of magnetic field states, set the variances equal to the observation uncertainty
        for (uint8_t index=16; index<=21; index++) {
            P[index][index] = sq(frontend->_magNoise);
        }
        // request a reset of the yaw and magnetic field states if not done before
        if (!magStateInitComplete || (!firstInflightMagInit && inFlight)) {
            magYawResetRequest = true;
        }
    }

    // If on ground we clear the flag indicating that the magnetic field in-flight initialisation has been completed
    // because we want it re-done for each takeoff
    if (onGround) {
        firstInflightYawInit = false;
        firstInflightMagInit = false;
    }

    // Adjust the indexing limits used to address the covariance, states and other EKF arrays to avoid unnecessary operations
    // if we are not using those states
    if (inhibitMagStates && inhibitWindStates) {
        stateIndexLim = 15;
    } else if (inhibitWindStates) {
        stateIndexLim = 21;
    } else {
        stateIndexLim = 23;
    }
}