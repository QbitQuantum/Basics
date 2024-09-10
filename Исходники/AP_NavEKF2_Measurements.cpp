/*
 *  Read IMU delta angle and delta velocity measurements and downsample to 100Hz
 *  for storage in the data buffers used by the EKF. If the IMU data arrives at
 *  lower rate than 100Hz, then no downsampling or upsampling will be performed.
 *  Downsampling is done using a method that does not introduce coning or sculling
 *  errors.
 */
void NavEKF2_core::readIMUData()
{
    const AP_InertialSensor &ins = _ahrs->get_ins();

    // average IMU sampling rate
    dtIMUavg = 1.0f/ins.get_sample_rate();

    // the imu sample time is used as a common time reference throughout the filter
    imuSampleTime_ms = AP_HAL::millis();

    // use the nominated imu or primary if not available
    if (ins.use_accel(imu_index)) {
        readDeltaVelocity(imu_index, imuDataNew.delVel, imuDataNew.delVelDT);
    } else {
        readDeltaVelocity(ins.get_primary_accel(), imuDataNew.delVel, imuDataNew.delVelDT);
    }

    // Get delta angle data from primary gyro or primary if not available
    if (ins.use_gyro(imu_index)) {
        readDeltaAngle(imu_index, imuDataNew.delAng);
    } else {
        readDeltaAngle(ins.get_primary_gyro(), imuDataNew.delAng);
    }
    imuDataNew.delAngDT = MAX(ins.get_delta_time(),1.0e-4f);

    // Get current time stamp
    imuDataNew.time_ms = imuSampleTime_ms;

    // remove gyro scale factor errors
    imuDataNew.delAng.x = imuDataNew.delAng.x * stateStruct.gyro_scale.x;
    imuDataNew.delAng.y = imuDataNew.delAng.y * stateStruct.gyro_scale.y;
    imuDataNew.delAng.z = imuDataNew.delAng.z * stateStruct.gyro_scale.z;

    // remove sensor bias errors
    imuDataNew.delAng -= stateStruct.gyro_bias;
    imuDataNew.delVel.z -= stateStruct.accel_zbias;

    // Accumulate the measurement time interval for the delta velocity and angle data
    imuDataDownSampledNew.delAngDT += imuDataNew.delAngDT;
    imuDataDownSampledNew.delVelDT += imuDataNew.delVelDT;

    // Rotate quaternon atitude from previous to new and normalise.
    // Accumulation using quaternions prevents introduction of coning errors due to downsampling
    Quaternion deltaQuat;
    deltaQuat.rotate(imuDataNew.delAng);
    imuQuatDownSampleNew = imuQuatDownSampleNew*deltaQuat;
    imuQuatDownSampleNew.normalize();

    // Rotate the accumulated delta velocity into the new frame of reference created by the latest delta angle
    // This prevents introduction of sculling errors due to downsampling
    Matrix3f deltaRotMat;
    deltaQuat.inverse().rotation_matrix(deltaRotMat);
    imuDataDownSampledNew.delVel = deltaRotMat*imuDataDownSampledNew.delVel;

    // accumulate the latest delta velocity
    imuDataDownSampledNew.delVel += imuDataNew.delVel;

    // Keep track of the number of IMU frames since the last state prediction
    framesSincePredict++;

    // If 10msec has elapsed, and the frontend has allowed us to start a new predict cycle, then store the accumulated IMU data
    // to be used by the state prediction, ignoring the frontend permission if more than 20msec has lapsed
    if ((dtIMUavg*(float)framesSincePredict >= 0.01f && startPredictEnabled) || (dtIMUavg*(float)framesSincePredict >= 0.02f)) {
        // convert the accumulated quaternion to an equivalent delta angle
        imuQuatDownSampleNew.to_axis_angle(imuDataDownSampledNew.delAng);
        // Time stamp the data
        imuDataDownSampledNew.time_ms = imuSampleTime_ms;
        // Write data to the FIFO IMU buffer
        storedIMU.push_youngest_element(imuDataDownSampledNew);
        // zero the accumulated IMU data and quaternion
        imuDataDownSampledNew.delAng.zero();
        imuDataDownSampledNew.delVel.zero();
        imuDataDownSampledNew.delAngDT = 0.0f;
        imuDataDownSampledNew.delVelDT = 0.0f;
        imuQuatDownSampleNew[0] = 1.0f;
        imuQuatDownSampleNew[3] = imuQuatDownSampleNew[2] = imuQuatDownSampleNew[1] = 0.0f;
        // reset the counter used to let the frontend know how many frames have elapsed since we started a new update cycle
        framesSincePredict = 0;
        // set the flag to let the filter know it has new IMU data nad needs to run
        runUpdates = true;
    } else {
        // we don't have new IMU data in the buffer so don't run filter updates on this time step
        runUpdates = false;
    }

    // extract the oldest available data from the FIFO buffer
    imuDataDelayed = storedIMU.pop_oldest_element();
    float minDT = 0.1f*dtEkfAvg;
    imuDataDelayed.delAngDT = MAX(imuDataDelayed.delAngDT,minDT);
    imuDataDelayed.delVelDT = MAX(imuDataDelayed.delVelDT,minDT);

}