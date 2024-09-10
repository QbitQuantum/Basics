QString ReadableNumber::makeReadable(const char *s) const
{
    QString qs;
    bool ok;

    auto parts = QString(s).split('.');
    auto integer_part = parts[0].toLong(&ok);
    if (!ok) return NaN();

    qs += makeReadable(integer_part);

    if (1 == parts.size()) return qs;

    QString fractional_part = parts[1];
    if (0 == fractional_part.size()) return qs;

    qs += " POINT";

    foreach(auto c, fractional_part)
    {
        auto digit = (long)c.digitValue();
        if (-1 == digit) return NaN();

        qs += " " + makeReadable((long)digit);
    }