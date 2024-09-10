float discreteTimeConstantForSampleRate(float timeConstant, float sampleRate)
{
    // hardcoded value is temporary build fix for Windows.
    // FIXME: replace hardcode 2.718282 with M_E until the correct MathExtras.h solution is determined.
    return 1 - powf(1 / 2.718282f, 1 / (sampleRate * timeConstant));
}