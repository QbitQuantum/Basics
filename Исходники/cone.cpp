double ConeEffect::gain(FloatPoint3D sourcePosition, FloatPoint3D sourceOrientation, FloatPoint3D listenerPosition)
{
    if (sourceOrientation.isZero() || ((m_innerAngle == 360.0) && (m_outerAngle == 360.0)))
        return 1.0; // no cone specified - unity gain

    // Normalized source-listener vector
    FloatPoint3D sourceToListener = listenerPosition - sourcePosition;
    sourceToListener.normalize();

    FloatPoint3D normalizedSourceOrientation = sourceOrientation;
    normalizedSourceOrientation.normalize();

    // Angle between the source orientation vector and the source-listener vector
    double dotProduct = sourceToListener.dot(normalizedSourceOrientation);
    double angle = 180.0 * acos(dotProduct) / piDouble;
    double absAngle = fabs(angle);

    // Divide by 2.0 here since API is entire angle (not half-angle)
    double absInnerAngle = fabs(m_innerAngle) / 2.0;
    double absOuterAngle = fabs(m_outerAngle) / 2.0;
    double gain = 1.0;

    if (absAngle <= absInnerAngle)
        // No attenuation
        gain = 1.0;
    else if (absAngle >= absOuterAngle)
        // Max attenuation
        gain = m_outerGain;
    else {
        // Between inner and outer cones
        // inner -> outer, x goes from 0 -> 1
        double x = (absAngle - absInnerAngle) / (absOuterAngle - absInnerAngle);
        gain = (1.0 - x) + m_outerGain * x;
    }

    return gain;
}