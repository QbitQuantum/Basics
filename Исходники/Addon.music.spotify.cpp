bool Addon_music_spotify::GetContextButtons(CFileItemPtr& item,
		CContextButtons &buttons) {
	if (isReady()) {
		CURL url(item->GetPath());
		CStdString uri = url.GetFileNameWithoutPath();
		//the path will look something like this "musicdb://2/spotify:artist:0LcJLqbBmaGUft1e9Mm8HV/-1/"
		//if we are trying to show all tracks for a spotify artist, we cant use the params becouse they are only integers.

		if (uri.Left(13).Equals("spotify:album")) {
			uri = uri.Left(uri.Find('#'));
			sp_link *spLink = sp_link_create_from_string(uri);
			sp_album *spAlbum = sp_link_as_album(spLink);
			SxAlbum* salbum = AlbumStore::getInstance()->getAlbum(spAlbum, true);
			if (salbum) {
				buttons.Add(
						CONTEXT_BUTTON_SPOTIFY_TOGGLE_STAR_ALBUM,
						salbum->isStarred() ?
								Settings::getInstance()->getUnstarAlbumString() :
								Settings::getInstance()->getStarAlbumString());
				AlbumStore::getInstance()->removeAlbum(salbum);
				buttons.Add(CONTEXT_BUTTON_SPOTIFY_BROWSE_ARTIST,
						Settings::getInstance()->getBrowseArtistString());
			}
			sp_link_release(spLink);
			sp_album_release(spAlbum);
		} else if (uri.Left(13).Equals("spotify:track")) {
			uri = uri.Left(uri.Find('.'));
			Logger::printOut(uri);
			sp_link *spLink = sp_link_create_from_string(uri);
			sp_track* spTrack = sp_link_as_track(spLink);
			buttons.Add(
					CONTEXT_BUTTON_SPOTIFY_TOGGLE_STAR_TRACK,
					sp_track_is_starred(Session::getInstance()->getSpSession(), spTrack) ?
							Settings::getInstance()->getUnstarTrackString() :
							Settings::getInstance()->getStarTrackString());
			buttons.Add(CONTEXT_BUTTON_SPOTIFY_BROWSE_ALBUM,
					Settings::getInstance()->getBrowseAlbumString());
			buttons.Add(CONTEXT_BUTTON_SPOTIFY_BROWSE_ARTIST,
					Settings::getInstance()->getBrowseArtistString());

			//this is unstable as it is now... find a solution later

			SxAlbum* salbum = AlbumStore::getInstance()->getAlbum(
					sp_track_album(spTrack), true);
			if (salbum) {
				while (!Session::getInstance()->lock())
					;
				while (!salbum->isLoaded()) {
					Session::getInstance()->processEvents();
				}
				Session::getInstance()->unlock();
				buttons.Add(
						CONTEXT_BUTTON_SPOTIFY_TOGGLE_STAR_ALBUM,
						salbum->isStarred() ?
								Settings::getInstance()->getUnstarAlbumString() :
								Settings::getInstance()->getStarAlbumString());
				AlbumStore::getInstance()->removeAlbum(salbum);
			}

			sp_track_release(spTrack);
			sp_link_release(spLink);
		}
	}
	return true;
}