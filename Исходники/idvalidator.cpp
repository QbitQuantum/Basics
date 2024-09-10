bool CSVWorld::IdValidator::isValid (const QChar& c, bool first) const
{
    if (c.isLetter() || c=='_')
        return true;

    if (!first && (c.isDigit()  || c.isSpace()))
        return true;

    return false;
}