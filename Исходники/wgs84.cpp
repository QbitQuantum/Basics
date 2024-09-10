/*!
 * Convert longitude, latitude, height to X, Y, Z in wgs84
 * @param[in] longitude in degree
 * @param[in] latitude in degree
 * @param[in] height in meter
 * @return ecef vector<double> contains X, Y, Z in wgs84
 */
vector<double> llh2ecef(const double& longitude, const double& latitude, const double& height)
{
        vector<double> ecef;
        const double n = A / sqrt(1.0 - E * E * sin(toRad(latitude)) * sin(toRad(latitude)));

        ecef.push_back((n + height) * cos(toRad(longitude)) * cos(toRad(latitude)));
        ecef.push_back((n + height) * sin(toRad(longitude)) * cos(toRad(latitude)));
        ecef.push_back(((n * (1.0 - E * E)) + height) * sin(toRad(latitude)));

        return ecef;
}