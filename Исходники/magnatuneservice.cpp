QVariant MagnatuneService::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        switch (role) {
        case Cantata::Role_CoverSong: {
            QVariant v;
            Item *item = static_cast<Item *>(index.internalPointer());
            switch (item->getType()) {
            case T_Album:
                if (item->getSong().isEmpty()) {
                    Song song;
                    song.artist=item->getParent()->getId();
                    song.album=item->getId();
                    song.setIsFromOnlineService(constName);
                    song.file=constName; // Just so that isEmpty() is false!
                    QString url=static_cast<OnlineDb *>(db)->getCoverUrl(/*T_Album==topLevel() ? static_cast<AlbumItem *>(item)->getArtistId() : */item->getParent()->getId(), item->getId());
                    song.setExtraField(Song::OnlineImageUrl, url);
                    item->setSong(song);
                }
                v.setValue<Song>(item->getSong());
                break;
            case T_Artist:
                break;
            default:
                break;
            }
            return v;
        }
        }
    }
    return OnlineDbService::data(index, role);
}