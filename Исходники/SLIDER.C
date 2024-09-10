static double SliderIntervalRound(double fValue, double fInterval,
                                  double fMin, double fMax,
                                  WORD wParam)
{
    if (fInterval == 0.0)
        return fValue;

    if (fValue > fMax)
        return fMax;
    else if (fValue < fMin)
        return fMin;
    
    if ((double) (long) fInterval == fInterval &&
        (double) (long) fValue == fValue)
    {
        int dec, sign;
        return atof(fcvt(fValue, 0, &dec, &sign));
    }
    else
    {
        double dInterval = fInterval / 100000;

        if (wParam == SB_LINEUP)
        {
            fValue = floor((fValue - fMin) / dInterval) * dInterval + fMin;
            return ceil(fValue * 100000) / 100000;
        }
        else
        {
            fValue = ceil((fValue - fMin) / dInterval) * dInterval + fMin;
            return floor(fValue * 100000) / 100000;
        }
    }
}