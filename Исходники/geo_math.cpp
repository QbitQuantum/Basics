/*
 * Compute the initial bearing, **in degrees**, from a starting point to a
 * destination point given as lat/lons in radians.
 */
float
initial_bearing_deg(const double lat_a, const double lon_a,
        const double lat_b, const double lon_b)
{
    using std::sin;
    using std::cos;
    using std::atan2;
    using std::fmod;

    const float delta_lon = lon_b - lon_a;
    const float opposite = sin(delta_lon) * cos(lat_b);
    const float adjacent = 
        cos(lat_a) * sin(lat_b) - sin(lat_a) * cos(lat_b) * cos(delta_lon);

    const float bearing = atan2(opposite, adjacent);
    const float bearing_deg = (bearing >= 0.0 ? to_deg(bearing)
                                              : to_deg(bearing) + 360.0);

    return bearing_deg;
}