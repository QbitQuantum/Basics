double kepler_anomaly_true_to_eccentric(double e, double f) {
    if(zero(e - 1.0))
        return tan(f / 2.0);
    if(e > 1.0)
        return sign(f) * acosh((e + cos(f)) / (1.0 + e * cos(f)));

    return atan2(sqrt(1.0-e*e) * sin(f), cos(f) + e);
}