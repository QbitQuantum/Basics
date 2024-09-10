static bool isCompleteCharLiteral(const BackwardsScanner &tk, int index)
{
    const QStringRef text = tk.textRef(index);

    if (text.length() < 2)
        return false;

    else if (text.at(text.length() - 1) == QLatin1Char('\''))
        return text.at(text.length() - 2) != QLatin1Char('\\'); // ### not exactly.

    return false;
}