// produce a yaw error value. The returned value is proportional
// to sin() of the current heading error in earth frame
float
AP_AHRS_DCM::yaw_error_compass(void)
{
    Vector3f mag = Vector3f(_compass->mag_x, _compass->mag_y, _compass->mag_z);
    // get the mag vector in the earth frame
    Vector2f rb = _dcm_matrix.mulXY(mag);

    rb.normalize();
    if (rb.is_inf()) {
        // not a valid vector
        return 0.0;
    }

    // update vector holding earths magnetic field (if required)
    if( _last_declination != _compass->get_declination() ) {
        _last_declination = _compass->get_declination();
        _mag_earth.x = cosf(_last_declination);
        _mag_earth.y = sinf(_last_declination);
    }

    // calculate the error term in earth frame
    // calculate the Z component of the cross product of rb and _mag_earth
    return rb % _mag_earth;
}