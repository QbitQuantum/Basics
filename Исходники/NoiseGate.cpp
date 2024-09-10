inline float rmsToDb(float rms)
{
    float db = 20.0f * log10(rms);
    if(!_finite(db))
        return VOL_MIN;
    return db;
}