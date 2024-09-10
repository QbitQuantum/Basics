bool GlslHighlighter::isPPKeyword(const QStringRef &text) const
{
    switch (text.length())
    {
    case 2:
        if (text.at(0) == QLatin1Char('i') && text.at(1) == QLatin1Char('f'))
            return true;
        break;

    case 4:
        if (text.at(0) == QLatin1Char('e') && text == QLatin1String("elif"))
            return true;
        else if (text.at(0) == QLatin1Char('e') && text == QLatin1String("else"))
            return true;
        break;

    case 5:
        if (text.at(0) == QLatin1Char('i') && text == QLatin1String("ifdef"))
            return true;
        else if (text.at(0) == QLatin1Char('u') && text == QLatin1String("undef"))
            return true;
        else if (text.at(0) == QLatin1Char('e') && text == QLatin1String("endif"))
            return true;
        else if (text.at(0) == QLatin1Char('e') && text == QLatin1String("error"))
            return true;
        break;

    case 6:
        if (text.at(0) == QLatin1Char('i') && text == QLatin1String("ifndef"))
            return true;
        if (text.at(0) == QLatin1Char('i') && text == QLatin1String("import"))
            return true;
        else if (text.at(0) == QLatin1Char('d') && text == QLatin1String("define"))
            return true;
        else if (text.at(0) == QLatin1Char('p') && text == QLatin1String("pragma"))
            return true;
        break;

    case 7:
        if (text.at(0) == QLatin1Char('i') && text == QLatin1String("include"))
            return true;
        else if (text.at(0) == QLatin1Char('w') && text == QLatin1String("warning"))
            return true;
        break;

    case 12:
        if (text.at(0) == QLatin1Char('i') && text == QLatin1String("include_next"))
            return true;
        break;

    default:
        break;
    }

    return false;
}