/**
 * \brief Calculate distance between two points
 * This function uses an algorithm for an oblate spheroid earth model.
 * The algorithm is described here: 
 * http://www.ngs.noaa.gov/PUBS_LIB/inverse.pdf
 * \return Distance in meters
 */
double nmea_distance_ellipsoid(
        const nmeaPOS *from_pos,    /**< From position in radians */
        const nmeaPOS *to_pos,      /**< To position in radians */
        double *from_azimuth,       /**< (O) azimuth at "from" position in radians */
        double *to_azimuth          /**< (O) azimuth at "to" position in radians */
        )
{
    /* All variables */
    double f, a, b, sqr_a, sqr_b;
    double L, phi1, phi2, U1, U2, sin_U1, sin_U2, cos_U1, cos_U2;
    double sigma, sin_sigma, cos_sigma, cos_2_sigmam, sqr_cos_2_sigmam, sqr_cos_alpha, lambda, sin_lambda, cos_lambda, delta_lambda;
    int remaining_steps; 
    double sqr_u, A, B, delta_sigma;

    /* Check input */
    NMEA_ASSERT(from_pos != 0);
    NMEA_ASSERT(to_pos != 0);

    if ((from_pos->lat == to_pos->lat) && (from_pos->lon == to_pos->lon))
    { /* Identical points */
        if ( from_azimuth != 0 )
            *from_azimuth = 0;
        if ( to_azimuth != 0 )
            *to_azimuth = 0;
        return 0;    
    } /* Identical points */

    /* Earth geometry */
    f = NMEA_EARTH_FLATTENING;
    a = NMEA_EARTH_SEMIMAJORAXIS_M;
    b = (1 - f) * a;
    sqr_a = a * a;
    sqr_b = b * b;

    /* Calculation */
    L = to_pos->lon - from_pos->lon;
    phi1 = from_pos->lat;
    phi2 = to_pos->lat;
    U1 = atan((1 - f) * tan(phi1));
    U2 = atan((1 - f) * tan(phi2));
    sin_U1 = sin(U1);
    sin_U2 = sin(U2);
    cos_U1 = cos(U1);
    cos_U2 = cos(U2);

    /* Initialize iteration */
    sigma = 0;
    sin_sigma = sin(sigma);
    cos_sigma = cos(sigma);
    cos_2_sigmam = 0;
    sqr_cos_2_sigmam = cos_2_sigmam * cos_2_sigmam;
    sqr_cos_alpha = 0;
    lambda = L;
    sin_lambda = sin(lambda);                            
    cos_lambda = cos(lambda);                       
    delta_lambda = lambda;
    remaining_steps = 20; 

    while ((delta_lambda > 1e-12) && (remaining_steps > 0)) 
    { /* Iterate */
        /* Variables */
        double tmp1, tmp2, sin_alpha, cos_alpha, C, lambda_prev;

        /* Calculation */
        tmp1 = cos_U2 * sin_lambda;
        tmp2 = cos_U1 * sin_U2 - sin_U1 * cos_U2 * cos_lambda;  
        sin_sigma = sqrt(tmp1 * tmp1 + tmp2 * tmp2);                
        cos_sigma = sin_U1 * sin_U2 + cos_U1 * cos_U2 * cos_lambda;   
        sin_alpha = cos_U1 * cos_U2 * sin_lambda / sin_sigma;  
        cos_alpha = cos(asin(sin_alpha));                 
        sqr_cos_alpha = cos_alpha * cos_alpha;                     
        cos_2_sigmam = cos_sigma - 2 * sin_U1 * sin_U2 / sqr_cos_alpha;
        sqr_cos_2_sigmam = cos_2_sigmam * cos_2_sigmam; 
        C = f / 16 * sqr_cos_alpha * (4 + f * (4 - 3 * sqr_cos_alpha));
        lambda_prev = lambda; 
        sigma = asin(sin_sigma); 
        lambda = L + 
            (1 - C) * f * sin_alpha
            * (sigma + C * sin_sigma * (cos_2_sigmam + C * cos_sigma * (-1 + 2 * sqr_cos_2_sigmam)));                                                
        delta_lambda = lambda_prev - lambda; 
        if ( delta_lambda < 0 ) delta_lambda = -delta_lambda; 
        sin_lambda = sin(lambda);
        cos_lambda = cos(lambda);
        remaining_steps--; 
    }  /* Iterate */

    /* More calculation  */
    sqr_u = sqr_cos_alpha * (sqr_a - sqr_b) / sqr_b; 
    A = 1 + sqr_u / 16384 * (4096 + sqr_u * (-768 + sqr_u * (320 - 175 * sqr_u)));
    B = sqr_u / 1024 * (256 + sqr_u * (-128 + sqr_u * (74 - 47 * sqr_u)));
    delta_sigma = B * sin_sigma * ( 
        cos_2_sigmam + B / 4 * ( 
        cos_sigma * (-1 + 2 * sqr_cos_2_sigmam) -
        B / 6 * cos_2_sigmam * (-3 + 4 * sin_sigma * sin_sigma) * (-3 + 4 * sqr_cos_2_sigmam)
        ));

    /* Calculate result */
    if ( from_azimuth != 0 )
    {
        double tan_alpha_1 = cos_U2 * sin_lambda / (cos_U1 * sin_U2 - sin_U1 * cos_U2 * cos_lambda);
        *from_azimuth = atan(tan_alpha_1);
    }
    if ( to_azimuth != 0 )
    {
        double tan_alpha_2 = cos_U1 * sin_lambda / (-sin_U1 * cos_U2 + cos_U1 * sin_U2 * cos_lambda);
        *to_azimuth = atan(tan_alpha_2);
    }

    return b * A * (sigma - delta_sigma);
}