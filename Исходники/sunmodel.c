static void sunmodel_ae_0(double slat, double slon, double lat, double lon, 
        double *azm, double *elv, char use_arc) {
    double azimuth;
    double omega, csz, elevation, az_denom;
    double sinlat, coslat, sinslat, cosslat;
    
    omega = lon - slon;
    sinlat = sin(lat);
    coslat = cos(lat);
    sinslat = sin(slat);
    cosslat = cos(slat);
    
    csz = sinlat * sinslat + coslat * cosslat * cos(omega);
    
    if (csz > 1.0) {
        csz = 1.0;
    }
    else {
        if (csz < -1.0) { 
            csz = -1.0;
        }
    }
    
    elevation = asin(csz);
    az_denom = coslat * cos(elevation);
    
    if (fabs(az_denom) > DBL_EPSILON) { // TODO check relatyvely nominator
        azimuth = (sinlat * csz - sinslat) / az_denom;
    
        if (fabs(azimuth) > 1.0) {
            if (azimuth < 0.0) {
                azimuth = -1.0;
            } 
            else {
                azimuth = 1.0;
            }
        }
        
        azimuth = M_PI - acos(azimuth);
        if (omega > 0.0) {
            azimuth = -azimuth;
        }
    } 
    else {
        if (lat > 0.0) {
            azimuth = M_PI;
        } else { 
            azimuth = 0.0;
        }
    }
    
    if (azimuth < 0.0) {
        azimuth += 2.0 * M_PI;
    }
    
    if (use_arc == 1 || use_arc == 'y') {
        elevation += sunmodel_atmo_refraction_correction(elevation);
    }

//    if (elevation < DEG2RAD(-18.0)) {
//        puts("A Night at the Roxbury");
//    }
    
    if (azm != NULL) {
        (*azm) = azimuth;
    }
    
    if (elv != NULL) {
        (*elv) = elevation;
    }
}