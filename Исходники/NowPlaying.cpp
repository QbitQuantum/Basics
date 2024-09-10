PLUGIN_EXPORT LPCWSTR GetString(void* data)
{
	Measure* measure = (Measure*)data;
	ParentMeasure* parent = measure->parent;
	if (!parent) return nullptr;

	const Player* player = parent->player;
	static WCHAR buffer[32];

	switch (measure->type)
	{
	case MEASURE_ARTIST:
		return player->GetArtist();

	case MEASURE_TITLE:
		return player->GetTitle();

	case MEASURE_ALBUM:
		return player->GetAlbum();

	case MEASURE_LYRICS:
		return player->GetLyrics();

	case MEASURE_COVER:
		return player->GetCoverPath();

	case MEASURE_FILE:
		return player->GetFilePath();

	case MEASURE_DURATION:
		SecondsToTime(player->GetDuration(), parent->disableLeadingZero, buffer);
		return buffer;

	case MEASURE_POSITION:
		SecondsToTime(player->GetPosition(), parent->disableLeadingZero, buffer);
		return buffer;

	case MEASURE_PROGRESS:
		_itow_s(player->GetDuration() ? ((player->GetPosition() * 100) / player->GetDuration()) : 0, buffer, 10);
		return buffer;

	case MEASURE_RATING:
		_itow_s(player->GetRating(), buffer, 10);
		return buffer;

	case MEASURE_VOLUME:
		_itow_s(player->GetVolume(), buffer, 10);
		return buffer;

	case MEASURE_STATE:
		_itow_s(player->GetState(), buffer, 10);
		return buffer;

	case MEASURE_STATUS:
		_itow_s((int)player->IsInitialized(), buffer, 10);
		return buffer;

	case MEASURE_SHUFFLE:
		_itow_s((int)player->GetShuffle(), buffer, 10);
		return buffer;

	case MEASURE_REPEAT:
		_itow_s((int)player->GetRepeat(), buffer, 10);
		return buffer;

	case MEASURE_NUMBER:
		_itow_s(player->GetNumber(), buffer, 10);
		return buffer;

	case MEASURE_YEAR:
		_itow_s(player->GetYear(), buffer, 10);
		return buffer;
	}

	return nullptr;
}