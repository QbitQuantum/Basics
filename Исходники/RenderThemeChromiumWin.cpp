static double querySystemBlinkInterval(double defaultInterval)
{
    UINT blinkTime = GetCaretBlinkTime();
    if (blinkTime == 0)
        return defaultInterval;
    if (blinkTime == INFINITE)
        return 0;
    return blinkTime / 1000.0;
}