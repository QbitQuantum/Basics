void LocalScene::populateTopRatedArtist(int YPos)
{
    int artistRow  = 0;
    int Column     = 0;
    item_count = (parentView()->width()/160 > 2) ? parentView()->width()/160 : 2;
    int char_entry = 0;

    CategorieGraphicItem *category = new CategorieGraphicItem(qobject_cast<QGraphicsView*> (parentView())->viewport());
    category->m_name = QString(tr("Top rated artists"));
    category->setPos(0 ,YPos);
    addItem(category);

    //! get artists List from LocalTrackModel
    QList<MEDIA::ArtistPtr> artists;
    for (int i=0 ; i < m_localTrackModel->rootItem()->childCount(); i++ ) {
       artists << MEDIA::ArtistPtr::staticCast(m_localTrackModel->rootItem()->child(i));
     }

    //! sort
    qSort(artists.begin(), artists.end(), MEDIA::compareArtistItemRating);

    //! loop over artist MediaItem
    foreach(MEDIA::ArtistPtr artist, artists)
    {
      if(artist->rating == 0.0 || char_entry == MAX_CHART_ENTRY) break;

      if( !m_localTrackModel->isMediaMatch(artist) ) continue;

      ArtistGraphicItem_v3 *artist_item = new ArtistGraphicItem_v3();
      artist_item->media = artist;
      artist_item->setPos(4+160*Column, YPos + 35 + artistRow*190);

      addItem(artist_item);
      char_entry++;

      /* ALBUM COVER LOOP */
        artist_item->albums_covers.clear();
        for(int j = artist->childCount()-1 ; j >= 0; j--) {
          if(!m_localTrackModel->isMediaMatch(artist->child(j)) ) continue;
          MEDIA::AlbumPtr album = MEDIA::AlbumPtr::staticCast(artist->child(j));

          artist_item->albums_covers.prepend(album);

          /* WARNING limite de l'affichage à 6 cover max */
          if(artist_item->albums_covers.size() >=6) break;
        }

      if(Column < (item_count-1)) {
        Column++;
      }
      else {
        Column = 0;
        artistRow++;
      }
    }

    //! si liste vide --> message
    if(char_entry==0) {
      InfoGraphicItem *info = new InfoGraphicItem(qobject_cast<QGraphicsView*> (parentView())->viewport());
      info->_text = tr("No entry found");
      info->setPos( 0 , YPos + 50);
      addItem(info);
    }
}