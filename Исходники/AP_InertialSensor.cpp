// _calibrate_model - perform low level accel calibration
// accel_sample are accelerometer samples collected in 6 different positions
// accel_offsets are output from the calibration routine
// accel_scale are output from the calibration routine
// returns true if successful
bool AP_InertialSensor::_calibrate_accel( Vector3f accel_sample[6], Vector3f& accel_offsets, Vector3f& accel_scale )
{
    int16_t i;
    int16_t num_iterations = 0;
    float eps = 0.000000001;
    float change = 100.0;
    float data[3];
    float beta[6];
    float delta[6];
    float ds[6];
    float JS[6][6];
    bool success = true;

    // reset
    beta[0] = beta[1] = beta[2] = 0;
    beta[3] = beta[4] = beta[5] = 1.0/GRAVITY;
    
    while( num_iterations < 20 && change > eps ) {
        num_iterations++;

        _calibrate_reset_matrices(ds, JS);

        for( i=0; i<6; i++ ) {
            data[0] = accel_sample[i].x;
            data[1] = accel_sample[i].y;
            data[2] = accel_sample[i].z;
            _calibrate_update_matrices(ds, JS, beta, data);
        }

        _calibrate_find_delta(ds, JS, delta);

        change =    delta[0]*delta[0] +
                    delta[0]*delta[0] +
                    delta[1]*delta[1] +
                    delta[2]*delta[2] +
                    delta[3]*delta[3] / (beta[3]*beta[3]) +
                    delta[4]*delta[4] / (beta[4]*beta[4]) +
                    delta[5]*delta[5] / (beta[5]*beta[5]);

        for( i=0; i<6; i++ ) {
            beta[i] -= delta[i];
        }
    }

    // copy results out
    accel_scale.x = beta[3] * GRAVITY;
    accel_scale.y = beta[4] * GRAVITY;
    accel_scale.z = beta[5] * GRAVITY;
    accel_offsets.x = beta[0] * accel_scale.x;
    accel_offsets.y = beta[1] * accel_scale.y;
    accel_offsets.z = beta[2] * accel_scale.z;

    // sanity check scale
    if( accel_scale.is_nan() || fabs(accel_scale.x-1.0) > 0.1 || fabs(accel_scale.y-1.0) > 0.1 || fabs(accel_scale.z-1.0) > 0.1 ) {
        success = false;
    }
    // sanity check offsets (2.0 is roughly 2/10th of a G, 5.0 is roughly half a G)
    if( accel_offsets.is_nan() || fabs(accel_offsets.x) > 2.0 || fabs(accel_offsets.y) > 2.0 || fabs(accel_offsets.z) > 2.0 ) {
        success = false;
    }

    // return success or failure
    return success;
}