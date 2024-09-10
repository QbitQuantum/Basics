QString FormatKey(QString pKey)
{
    QString result = "";
    QChar *base = pKey.data();
    QChar *ch;
    int max = pKey.length();
    for (int pos = 0; pos < max; pos++)
    {
        ch = base + pos;
        if (pos == 0) result += QString(ch->toUpper());
        else if (*ch > 64 && *ch < 91) result += " " + QString(*ch);
        else result += QString(*ch);
    }

    return result;
}