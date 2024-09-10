QByteArray ScriptableProxyHelper::getClipboardData(const QString &mime, QClipboard::Mode mode)
{
    INVOKE(getClipboardData(mime, mode));
    const QMimeData *data = clipboardData(mode);
    if (!data)
        return QByteArray();

    if (mime == "?")
        return data->formats().join("\n").toUtf8() + '\n';

    return cloneData(*data, QStringList(mime)).value(mime).toByteArray();
}