uint CSVController::hexDigitToDecimalValue(const QChar& c) const
{
    if (c.isDigit())
    {
        return c.digitValue();
    }
    else if ('a' <= c && c <= 'f')
    {
        return c.unicode() - 'a' + 10;
    }
    else if ('A' <= c && c <= 'F')
    {
        return c.unicode() - 'A' + 10;
    }
    return 0;
}