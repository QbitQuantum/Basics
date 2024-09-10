// return a ground speed estimate in m/s
Vector2f AP_AHRS::groundspeed_vector(void)
{
    // Generate estimate of ground speed vector using air data system
    Vector2f gndVelADS;
    Vector2f gndVelGPS;
    float airspeed = 0;
    const bool gotAirspeed = airspeed_estimate_true(&airspeed);
    const bool gotGPS = (AP::gps().status() >= AP_GPS::GPS_OK_FIX_2D);
    if (gotAirspeed) {
        const Vector3f wind = wind_estimate();
        const Vector2f wind2d(wind.x, wind.y);
        const Vector2f airspeed_vector(_cos_yaw * airspeed, _sin_yaw * airspeed);
        gndVelADS = airspeed_vector - wind2d;
    }

    // Generate estimate of ground speed vector using GPS
    if (gotGPS) {
        const float cog = radians(AP::gps().ground_course_cd()*0.01f);
        gndVelGPS = Vector2f(cosf(cog), sinf(cog)) * AP::gps().ground_speed();
    }
    // If both ADS and GPS data is available, apply a complementary filter
    if (gotAirspeed && gotGPS) {
        // The LPF is applied to the GPS and the HPF is applied to the air data estimate
        // before the two are summed
        //Define filter coefficients
        // alpha and beta must sum to one
        // beta = dt/Tau, where
        // dt = filter time step (0.1 sec if called by nav loop)
        // Tau = cross-over time constant (nominal 2 seconds)
        // More lag on GPS requires Tau to be bigger, less lag allows it to be smaller
        // To-Do - set Tau as a function of GPS lag.
        const float alpha = 1.0f - beta;
        // Run LP filters
        _lp = gndVelGPS * beta  + _lp * alpha;
        // Run HP filters
        _hp = (gndVelADS - _lastGndVelADS) + _hp * alpha;
        // Save the current ADS ground vector for the next time step
        _lastGndVelADS = gndVelADS;
        // Sum the HP and LP filter outputs
        return _hp + _lp;
    }
    // Only ADS data is available return ADS estimate
    if (gotAirspeed && !gotGPS) {
        return gndVelADS;
    }
    // Only GPS data is available so return GPS estimate
    if (!gotAirspeed && gotGPS) {
        return gndVelGPS;
    }

    if (airspeed > 0) {
        // we have a rough airspeed, and we have a yaw. For
        // dead-reckoning purposes we can create a estimated
        // groundspeed vector
        Vector2f ret(cosf(yaw), sinf(yaw));
        ret *= airspeed;
        // adjust for estimated wind
        const Vector3f wind = wind_estimate();
        ret.x += wind.x;
        ret.y += wind.y;
        return ret;
    }

    return Vector2f(0.0f, 0.0f);
}