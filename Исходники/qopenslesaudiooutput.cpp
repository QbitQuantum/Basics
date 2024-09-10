inline SLmillibel QOpenSLESAudioOutput::adjustVolume(qreal vol)
{
    if (qFuzzyIsNull(vol))
        return SL_MILLIBEL_MIN;

    if (qFuzzyCompare(vol, qreal(1.0)))
        return 0;

    return 20 * LOG10(vol) * 100; // I.e., 20 * LOG10(SL_MILLIBEL_MAX * vol / SL_MILLIBEL_MAX)
}