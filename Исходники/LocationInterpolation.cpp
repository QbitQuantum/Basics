// Interpolate fractional arc between two wgs84 vectors.
// This models the earths ellipsoid.
geolocation Slerper::GeoSlerp(double frac)
{
    // Generate normalized ECEF vector
    xyz slerp = Slerp(frac);

    // Scale ecef unit vector so its roughly at earth surface
    double interpaltitudestep = m_altitude_delta * frac;
    slerp = slerp.scale(m_x0_magnitude + interpaltitudestep);

    // Convert ecef back to wgs84
    geolocation slerpgeo = slerp.togeolocation();

    // Set linear interpolated altitude on slerped wgs84 vector
    double interpaltitude = m_altitude_delta * frac;
    slerpgeo.Alt() = m_g0.Alt() + interpaltitude;

    return slerpgeo;
}