//! ----------------------- PlaylistWriter::updateDatabase ---------------------
void PlaylistWriter::updateDatabase(QList<MEDIA::TrackPtr> list)
{
    Database db;
    if (!db.connect()) return;

    QFileInfo fileInfo(m_fileToSave);
    QString fname = fileInfo.filePath().toUtf8();
    QString pname = fileInfo.baseName();
    uint mtime    = fileInfo.lastModified().toTime_t();

    //! delete playlist and playlist items
    QSqlField data("col",QVariant::String);
    data.setValue(fname);
    QString fnameDb = db.sqlDb()->driver()->formatValue(data,false);

    {
    QSqlQuery cleanQuery1("DELETE FROM `playlists` WHERE `filename`="+fnameDb+";", *db.sqlDb());
    QSqlQuery cleanQuery2("DELETE FROM `playlist_items` WHERE `playlist_id` NOT IN (SELECT `id` FROM `playlists`);", *db.sqlDb());
    }

    //! add playlist
    Debug::debug() << "    [PlaylistWriter] insert playlist into db" << m_fileToSave;

    int favorite = 0;

    /*-----------------------------------------------------------*/
    /* PLAYLIST part in database                                 */
    /* ----------------------------------------------------------*/ 
    {
        QSqlQuery playlistQuery(*db.sqlDb());
        playlistQuery.prepare("INSERT INTO `playlists`(`filename`,`name`,`type`,`favorite`, `mtime`)" \
                      "VALUES(?," \
                      "       ?," \
                      "       ?," \
                      "       ?," \
                      "       ?);");
        playlistQuery.addBindValue(fname);
        playlistQuery.addBindValue(pname);
        playlistQuery.addBindValue((int) T_FILE);
        playlistQuery.addBindValue(favorite);
        playlistQuery.addBindValue(mtime);
        playlistQuery.exec();
    }

    /*-----------------------------------------------------------*/
    /* PLAYLIST ITEMS part in database                           */
    /* ----------------------------------------------------------*/
    foreach(MEDIA::TrackPtr track, list)
    {
      QString url       = track->url;
      QString name      = QFileInfo(url).baseName();

      //! Playlist Item part in database
      QSqlQuery itemQuery(*db.sqlDb());
      Debug::debug() << "--- PlaylistWriter -> insert playlistitem url:" << url;

      itemQuery.prepare("INSERT INTO `playlist_items`(`url`,`name`,`playlist_id`)" \
                        "VALUES(?," \
                        "       ?," \
                        "       (SELECT `id` FROM `playlists` WHERE `filename`="+fnameDb+"));");
      itemQuery.addBindValue(url);
      itemQuery.addBindValue(name);
      itemQuery.exec();
    }