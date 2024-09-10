static bool isOneLeftToRightRun(const TextRun& run)
{
    for (int i = 0; i < run.length(); i++) {
        UCharDirection direction = u_charDirection(run[i]);
        if (direction == U_RIGHT_TO_LEFT || direction > U_OTHER_NEUTRAL)
            return false;
    }
    return true;
}