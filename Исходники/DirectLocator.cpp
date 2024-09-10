void Rotation::inverseTransform(double& lat, double& lon) const {
    const double u = toRadians(lon);
    const double v = toRadians(lat);

    const double w = cos(v);
    const double x = cos(u) * w;
    const double y = sin(u) * w;
    const double z = sin(v);

    const double x2 = a11 * x + a21 * y + a31 * z;
    const double y2 = a12 * x + a22 * y + a32 * z;
    const double z2 = a13 * x + a23 * y + a33 * z;

    lat = toDegrees(asin(z2));
    lon = toDegrees(atan2(y2, x2));
}