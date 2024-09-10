static void recodeAndAppend(QString &to, const QString &input,
                            QUrl::ComponentFormattingOptions encoding, const ushort *tableModifications)
{
    if (!qt_urlRecode(to, input.constData(), input.constData() + input.length(), encoding, tableModifications))
        to += input;
}