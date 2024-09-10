void WallConfiguration::loadWallSettings(const int processIndex)
{
    assert(processIndex > 0 && "WallConfiguration::loadWallSettings is only valid for processes of rank > 0");

    QXmlQuery query;
    if(!query.setFocus(QUrl(filename_)))
    {
        put_flog(LOG_FATAL, "failed to load %s", filename_.toLatin1().constData());
        exit(-1);
    }

    QString queryResult;

    // get host
    query.setQuery( QString("string(//process[%1]/@host)").arg(processIndex) );
    if (query.evaluateTo(&queryResult))
        host_ = queryResult.remove(QRegExp("[\\n\\t\\r]"));

    // get display (optional attribute)
    query.setQuery( QString("string(//process[%1]/@display)").arg(processIndex) );
    if(query.evaluateTo(&queryResult))
    {
        display_ = queryResult.remove(QRegExp("[\\n\\t\\r]"));
    }
    else
    {
        display_ = QString("default (:0)"); // the default
    }

    // get number of tiles for my process
    query.setQuery( QString("string(count(//process[%1]/screen))").arg(processIndex) );
    if (query.evaluateTo(&queryResult))
        screenCountForCurrentProcess_ = queryResult.toInt();

    put_flog(LOG_INFO, "rank %i: %i screens", processIndex, screenCountForCurrentProcess_);

    // populate parameters for each screen
    for(int i=1; i<=screenCountForCurrentProcess_; i++)
    {
        QPoint screenPosition;

        query.setQuery( QString("string(//process[%1]/screen[%2]/@x)").arg(processIndex).arg(i) );
        if(query.evaluateTo(&queryResult))
            screenPosition.setX(queryResult.toInt());

        query.setQuery( QString("string(//process[%1]/screen[%2]/@y)").arg(processIndex).arg(i) );
        if(query.evaluateTo(&queryResult))
            screenPosition.setY(queryResult.toInt());

        screenPosition_.push_back(screenPosition);

        QPoint screenIndex;

        query.setQuery( QString("string(//process[%1]/screen[%2]/@i)").arg(processIndex).arg(i) );
        if(query.evaluateTo(&queryResult))
            screenIndex.setX(queryResult.toInt());

        query.setQuery( QString("string(//process[%1]/screen[%2]/@j)").arg(processIndex).arg(i) );
        if(query.evaluateTo(&queryResult))
            screenIndex.setY(queryResult.toInt());

        screenGlobalIndex_.push_back(screenIndex);

        put_flog(LOG_INFO, "  screen parameters: posX = %i, posY = %i, indexX = %i, indexY = %i", screenPosition.x(), screenPosition.y(), screenIndex.x(), screenIndex.y());
    }
}