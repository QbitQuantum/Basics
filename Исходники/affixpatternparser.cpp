void
CurrencyAffixInfo::adjustPrecision(
        const UChar *currency, const UCurrencyUsage usage,
        FixedPrecision &precision, UErrorCode &status) {
    if (U_FAILURE(status)) {
        return;
    }

    int32_t digitCount = ucurr_getDefaultFractionDigitsForUsage(
            currency, usage, &status);
    precision.fMin.setFracDigitCount(digitCount);
    precision.fMax.setFracDigitCount(digitCount);
    double increment = ucurr_getRoundingIncrementForUsage(
            currency, usage, &status);
    if (increment == 0.0) {
        precision.fRoundingIncrement.clear();
    } else {
        precision.fRoundingIncrement.set(increment);
        // guard against round-off error
        precision.fRoundingIncrement.round(6);
    }
}