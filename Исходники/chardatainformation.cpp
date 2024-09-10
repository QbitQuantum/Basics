QString CharDataInformation::valueString(quint8 value)
{
    QChar qchar = QChar::fromLatin1(value);
    qchar = qchar.isPrint() ? qchar : QChar(QChar::ReplacementCharacter);
    QString charStr = QLatin1Char('\'') + qchar + QLatin1Char('\'');
    if (Kasten2::StructViewPreferences::showCharNumericalValue())
    {
        int base = displayBase();
        QString num = QString::number(value, base);
        if (base == 16)
            num.prepend(QLatin1String("0x"));
        if (base == 10 && Kasten2::StructViewPreferences::localeAwareDecimalFormatting())
            num = KGlobal::locale()->formatNumber(num, false, 0);
        charStr += QLatin1String(" (") + num + QLatin1Char(')');
    }
    return charStr;
}