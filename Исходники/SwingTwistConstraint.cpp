float SwingTwistConstraint::SwingLimitFunction::getMinDot(float theta) const {
    // extract the positive normalized fractional part of theta
    float integerPart;
    float normalizedTheta = modff(theta / TWO_PI, &integerPart);
    if (normalizedTheta < 0.0f) {
        normalizedTheta += 1.0f;
    }

    // interpolate between the two nearest points in the cycle
    float fractionPart = modff(normalizedTheta * (float)(_minDots.size() - 1), &integerPart);
    int i = (int)(integerPart);
    int j = (i + 1) % _minDots.size();
    return _minDots[i] * (1.0f - fractionPart) + _minDots[j] * fractionPart;
}