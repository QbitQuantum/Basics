void KRecentDocument::clear()
{
    const QStringList list = recentDocuments();
    QDir dir;
    for (QStringList::ConstIterator it = list.begin(); it != list.end(); ++it) {
        dir.remove(*it);
    }
}