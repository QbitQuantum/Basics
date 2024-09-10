void QWinJumpListCategoryPrivate::addRecent(QWinJumpListItem *item)
{
    Q_ASSERT(item->type() == QWinJumpListItem::Link);
    wchar_t *id = 0;
    if (jumpList && !jumpList->identifier().isEmpty())
        id = qt_qstringToNullTerminated(jumpList->identifier());

    SHARDAPPIDINFOLINK info;
    info.pszAppID = id;
    info.psl =  QWinJumpListPrivate::toIShellLink(item);
    if (info.psl) {
        SHAddToRecentDocs(SHARD_APPIDINFOLINK, &info);
        info.psl->Release();
    }
    delete[] id;
}