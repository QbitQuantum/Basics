/*******************************************************************************
    LocalScene::rateTrack
*******************************************************************************/
void LocalScene::rateTrack(QGraphicsItem* gi)
{
    TrackGraphicItem *item = static_cast<TrackGraphicItem*>(gi);

    MEDIA::TrackPtr track = item->media;
    if(track->id != -1) {
      Database db;
      if (!db.connect()) return;

      QSqlQuery q("", *db.sqlDb());
      q.prepare("UPDATE `tracks` SET `rating`=:rat WHERE `id`=:id;");
      q.bindValue(":rat", track->rating );
      q.bindValue(":id", track->id );
      q.exec();

      MEDIA::AlbumPtr album = MEDIA::AlbumPtr::staticCast(track->parent());
      if(!album->isUserRating)
         album->rating = m_localTrackModel->getItemAutoRating(album);

      MEDIA::ArtistPtr artist = MEDIA::ArtistPtr::staticCast(album->parent());
      if(!artist->isUserRating)
         artist->rating = m_localTrackModel->getItemAutoRating(artist);
     }
}