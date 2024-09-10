void QGeoMappingManagerEngineCm::cleanCacheToSize(int sizeLimit)
{
    DBG_CM(TILES_M, INFO_L, "cleanCacheToSize():  start cleaning cache, sizeLimit = " << sizeLimit);

    QDir dir;
    dir.cd(m_cacheDir);

    QStringList filters;
    filters << "*.png";
    dir.setNameFilters(filters);
    dir.setSorting(QDir::Time);

    qint64 totalSize = 0;   // SUM of all tiles size (not precize cache size, because of cluster size)
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        totalSize += list.at(i).size();
        //QFileInfo fileInfo = list.at(i);
        //qDebug() << fileInfo.lastModified() << "    " << fileInfo.fileName() << "    " << fileInfo.size();
    }
    DBG_CM(TILES_M, INFO_L, "Current cache size in bytes = " << totalSize);

    // start cleaning:
    int listSize = list.size();
    while ((listSize > 0) && (totalSize > sizeLimit)) {
        totalSize -= list.at(listSize-1).size();
        if (!dir.remove(list.at(listSize-1).fileName())) {
            DBG_CM(TILES_M, ERR_L, "Failed to delete file: " << list.at(listSize-1).fileName());
            totalSize += list.at(listSize-1).size();
        }
        listSize--;
    }
    DBG_CM(TILES_M, INFO_L, "Cache cleaning finished, current cache size = " << totalSize);
}