Vector3d DataGenerator::getAngularVelocity()
{
    const double delta_t = 0.00001;
    Matrix3d rot = getRotation();
    t += delta_t;
    Matrix3d drot = (getRotation() - rot) / delta_t;
    t -= delta_t;
    Matrix3d skew = rot.inverse() * drot;
#ifdef WITH_NOISE
    Vector3d disturb = Vector3d(distribution(generator) * sqrt(gyr_cov(0, 0)),
                                distribution(generator) * sqrt(gyr_cov(1, 1)),
                                distribution(generator) * sqrt(gyr_cov(2, 2))
                               );
    return disturb + Vector3d(skew(2, 1), -skew(2, 0), skew(1, 0));
#else
    return Vector3d(skew(2, 1), -skew(2, 0), skew(1, 0));
#endif
}