static void settingsUpdatedCb(UAVObjEvent * objEv) {
    AttitudeSettingsData attitudeSettings;
    AttitudeSettingsGet(&attitudeSettings);
    SensorSettingsGet(&sensorSettings);


    accelKp = attitudeSettings.AccelKp;
    accelKi = attitudeSettings.AccelKi;
    yawBiasRate = attitudeSettings.YawBiasRate;

    // Calculate accel filter alpha, in the same way as for gyro data in stabilization module.
    const float fakeDt = 0.0025f;
    if(attitudeSettings.AccelTau < 0.0001f) {
        accel_alpha = 0;   // not trusting this to resolve to 0
        accel_filter_enabled = false;
    } else {
        accel_alpha = expf(-fakeDt  / attitudeSettings.AccelTau);
        accel_filter_enabled = true;
    }

    zero_during_arming = attitudeSettings.ZeroDuringArming == ATTITUDESETTINGS_ZERODURINGARMING_TRUE;
    bias_correct_gyro = attitudeSettings.BiasCorrectGyro == ATTITUDESETTINGS_BIASCORRECTGYRO_TRUE;

    gyro_correct_int[0] = 0;
    gyro_correct_int[1] = 0;
    gyro_correct_int[2] = 0;

    // Indicates not to expend cycles on rotation
    if(attitudeSettings.BoardRotation[0] == 0 && attitudeSettings.BoardRotation[1] == 0 &&
            attitudeSettings.BoardRotation[2] == 0) {
        rotate = 0;

        // Shouldn't be used but to be safe
        float rotationQuat[4] = {1,0,0,0};
        Quaternion2R(rotationQuat, Rsb);
    } else {
        float rotationQuat[4];
        const float rpy[3] = {attitudeSettings.BoardRotation[ATTITUDESETTINGS_BOARDROTATION_ROLL] / 100.0f,
                              attitudeSettings.BoardRotation[ATTITUDESETTINGS_BOARDROTATION_PITCH] / 100.0f,
                              attitudeSettings.BoardRotation[ATTITUDESETTINGS_BOARDROTATION_YAW] / 100.0f
                             };
        RPY2Quaternion(rpy, rotationQuat);
        Quaternion2R(rotationQuat, Rsb);
        rotate = 1;
    }

    if (attitudeSettings.TrimFlight == ATTITUDESETTINGS_TRIMFLIGHT_START) {
        trim_accels[0] = 0;
        trim_accels[1] = 0;
        trim_accels[2] = 0;
        trim_samples = 0;
        trim_requested = true;
    } else if (attitudeSettings.TrimFlight == ATTITUDESETTINGS_TRIMFLIGHT_LOAD) {
        trim_requested = false;

        // Get sensor data  mean
        float a_body[3] = { trim_accels[0] / trim_samples,
                            trim_accels[1] / trim_samples,
                            trim_accels[2] / trim_samples
                          };

        // Inverse rotation of sensor data, from body frame into sensor frame
        float a_sensor[3];
        rot_mult(Rsb, a_body, a_sensor, false);

        // Temporary variables
        float psi, theta, phi;

        psi = attitudeSettings.BoardRotation[ATTITUDESETTINGS_BOARDROTATION_YAW] * DEG2RAD / 100.0f;

        float cP = cosf(psi);
        float sP = sinf(psi);

        // In case psi is too small, we have to use a different equation to solve for theta
        if (fabsf(psi) > PI / 2)
            theta = atanf((a_sensor[1] + cP * (sP * a_sensor[0] -
                                               cP * a_sensor[1])) / (sP * a_sensor[2]));
        else
            theta = atanf((a_sensor[0] - sP * (sP * a_sensor[0] -
                                               cP * a_sensor[1])) / (cP * a_sensor[2]));

        phi = atan2f((sP * a_sensor[0] - cP * a_sensor[1]) / GRAVITY,
                     (a_sensor[2] / cosf(theta) / GRAVITY));

        attitudeSettings.BoardRotation[ATTITUDESETTINGS_BOARDROTATION_ROLL] = phi * RAD2DEG * 100.0f;
        attitudeSettings.BoardRotation[ATTITUDESETTINGS_BOARDROTATION_PITCH] = theta * RAD2DEG * 100.0f;

        attitudeSettings.TrimFlight = ATTITUDESETTINGS_TRIMFLIGHT_NORMAL;
        AttitudeSettingsSet(&attitudeSettings);

    }
}