//从配置文件加载用户歌曲到播放器
void MusicList::loadMusicList()
{
    /*
    DatabaseOperation db(musicListDatabaseName);
    QList<QMap<QString, QStringList> > tableNamesAndTableData;
    tableNamesAndTableData = db.getTableNamesAndTableData();

    for (int i=0; i<tableNamesAndTableData.length(); ++i)
    {
        QString musicListName = tableNamesAndTableData.at(i).firstKey();
        QStringList musicNames = tableNamesAndTableData.at(i).first();

        if ( !DefaultList.contains(musicListName) )
        {
            createMusiclistToplevel(musicListName);
        }

        addMusicToList(musicListName, musicNames);
    }
    */
    QList<QMap<QString, QList<QMap<QString, QString> > > > musicListAndMusics;
    QStringList urlAndName;
    urlAndName << "url" << "name";
    musicListAndMusics = xml.getElementAttributeValueAndChildrenText(xml.MusicListElement, urlAndName);

    for (int i=0; i<musicListAndMusics.length(); ++i)
    {
        QString musicListName = musicListAndMusics.at(i).firstKey();
        QList<QMap<QString, QString> > musics = musicListAndMusics.at(i).first();

        if ( !DefaultList.contains(musicListName) )
        {
            createMusiclistToplevel(musicListName);
        }

        addMusicToList(musicListName, musics);
    }
}