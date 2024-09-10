//! ---------------- addToDatabase ---------------------------------------------
void HistoManager::addToDatabase()
{
    m_timer->stop();

    if(Engine::instance()->state() != ENGINE::PLAYING) {
       m_timer->stop();
       return;
    }

    MEDIA::TrackPtr media   =  m_player->playingTrack();
    int       now_date      =  QDateTime::currentDateTime().toTime_t();

    QString   engine_url    =  media->url;
    if(engine_url.isEmpty())
      return;

    QString   media_name;
    if(media->type() == TYPE_TRACK)
      media_name = media->artist + " - " + media->album + " - " + media->title;
    else
      media_name = media->name;

    Database db;
    if (!db.connect()) return;

    QSqlQuery("BEGIN TRANSACTION;",*db.sqlDb());

    //---------------------------------------
    //    add or update entry in history
    //---------------------------------------
    QSqlQuery q("", *db.sqlDb());
    q.prepare("SELECT `id`,`url` FROM `histo` WHERE `url`=:val;");
    q.bindValue(":val", engine_url );
    q.exec();

    if ( !q.next() ) {
      Debug::debug() << "[Histo] add a new entry" << engine_url;

      q.prepare("INSERT INTO `histo`(`url`,`name`,`date`) VALUES (:u,:n,:d);");
      q.bindValue(":u", engine_url);
      q.bindValue(":n", media_name);
      q.bindValue(":d", now_date);
      q.exec();

      if(q.numRowsAffected() < 1)
        Debug::warning() << "[Histo] error adding entry !! ";

      QSqlQuery query("DELETE FROM `histo` WHERE `id` <= (SELECT MAX(`id`) FROM `histo`) - 2000;", *db.sqlDb());
    }
    else
    {
      Debug::debug() << "[Histo] update an existing entry" << engine_url;
      int histo_id = q.value(0).toString().toInt();

      q.prepare("UPDATE `histo` SET `date`=:d WHERE `id`=:id;");
      q.bindValue(":d", now_date);
      q.bindValue(":id", histo_id);
      q.exec();
    }

    //---------------------------------------
    //    update playcount
    //---------------------------------------
    q.prepare("SELECT `id`,`artist_id`,`album_id` FROM `view_tracks` WHERE `filename`=:val LIMIT 1;");
    q.bindValue(":val", engine_url );
    q.exec();

    if (q.next())
    {
      //Debug::debug() << "update playcount!";

      const int trackId  = q.value(0).toInt();
      const int artistId = q.value(1).toInt();
      const int albumId  = q.value(2).toInt();

      QSqlQuery query1("UPDATE `tracks` " \
                       "SET `playcount`=`playcount`+1 " \
                       "WHERE `id`="+QString::number(trackId)+";", *db.sqlDb());

      QSqlQuery query2("UPDATE `albums` " \
                       "SET `playcount`=`playcount`+1 " \
                       "WHERE `id`="+QString::number(albumId)+";", *db.sqlDb());

      QSqlQuery query3("UPDATE `artists` " \
                       "SET `playcount`=`playcount`+1 " \
                       "WHERE `id`="+QString::number(artistId)+";", *db.sqlDb());

      /* update collection model item */
      MEDIA::TrackPtr track = MEDIA::TrackPtr(
               LocalTrackModel::instance()->trackItemHash.value(trackId)
               );

      if(!track.isNull()) {
        track->playcount++;
        track->lastPlayed = now_date;

        MEDIA::AlbumPtr album = MEDIA::AlbumPtr::staticCast(track->parent());
        album->playcount++;

        MEDIA::ArtistPtr artist = MEDIA::ArtistPtr::staticCast(album->parent());
        artist->playcount++;
      }
    }


    QSqlQuery("COMMIT TRANSACTION;",*db.sqlDb());
}