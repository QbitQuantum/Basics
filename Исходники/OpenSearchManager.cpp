QString OpenSearchManager::trimmedEngineName(const QString &engineName) const
{
    QString trimmed;
    QString::ConstIterator constIter = engineName.constBegin();
    while (constIter != engineName.constEnd()) {
        if (constIter->isSpace()) {
            trimmed.append('-');
        } else if (*constIter != '.') {
            trimmed.append(constIter->toLower());
        }
        constIter++;
    }

    return trimmed;
}