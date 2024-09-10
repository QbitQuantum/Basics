static QString updateVariable(const QString &varStr, const QString &varsToAdd,
                              const QString &varsToRemove)
{
    QSet<QString> var = parseVariable(varStr);

    QSet<QString> ss = parseVariable(varsToAdd);
    foreach (QString s, ss)
        var << s;

    ss = parseVariable(varsToRemove);
    foreach (QString s, ss)
        var.remove(s);

    QStringList sl = QStringList::fromSet(var);
    return sl.join(QLatin1String(" "));
}