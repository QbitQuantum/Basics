static float
husl_f(float t)
{
    if(t > lab_e)
        return cbrtf(t);
    else
        return 7.787f * t + 16.0f / 116.0f;
}