int CMediaLibrary::GetExtendedFileInfo(const wchar_t *fn, const wchar_t *Metadata, wchar_t *dest, size_t destlen)
{

	bool FindTag;
	int RetCode;

	::EnterCriticalSection(&CriticalSection);

	if (std::wstring(fn) != FileName)
	{
		FindTag = GetTagInfo(fn);
	}
	else
	{
		FindTag = true;
	}

	if (FindTag) {
		wchar_t	Buff[MAX_MUSICTEXT];
		const char *MetaData = reinterpret_cast<const char*>(Metadata);

		if (_stricmp(MetaData, "length") == 0) {
			_ultow_s(TagDataW.Length, dest, destlen, 10);
			RetCode = 1;
		}
		else if (_stricmp(MetaData, "formatinformation") == 0) {
			wcsncpy_s(dest, destlen, TagDataW.Format.c_str(), _TRUNCATE);
			RetCode = 1;
		}
		else if (_stricmp(MetaData, "type") == 0) {
			Buff[0] = '0';
			Buff[1] = 0;
			wcsncpy_s(dest, destlen, Buff, _TRUNCATE);
			RetCode = 1;
		}
		else if (_stricmp(MetaData, "family") == 0) {
			wcsncpy_s(dest, destlen, L"The True Audio File", _TRUNCATE);
			RetCode = 1;
		}
		else if (_stricmp(MetaData, "lossless") == 0) {
			Buff[0] = '1';
			wcsncpy_s(dest, destlen, Buff, _TRUNCATE);
			RetCode = 1;
		}
		else if (_stricmp(MetaData, "title") == 0) {
			wcsncpy_s(dest, destlen, TagDataW.Title.c_str(), _TRUNCATE);
			RetCode = 1;
		}
		else if (_stricmp(MetaData, "artist") == 0) {
			wcsncpy_s(dest, destlen, TagDataW.Artist.c_str(), _TRUNCATE);
			RetCode = 1;
		}
		else if (_stricmp(MetaData, "albumartist") == 0) {
			wcsncpy_s(dest, destlen, TagDataW.AlbumArtist.c_str(), _TRUNCATE);
			RetCode = 1;
		}
		else if (_stricmp(MetaData, "comment") == 0) {
			wcsncpy_s(dest, destlen, TagDataW.Comment.c_str(), _TRUNCATE);
			RetCode = 1;
		}
		else if (_stricmp(MetaData, "album") == 0) {
			wcsncpy_s(dest, destlen, TagDataW.Album.c_str(), _TRUNCATE);
			RetCode = 1;
		}
		else if (_stricmp(MetaData, "year") == 0) {
			wcsncpy_s(dest, destlen, TagDataW.Year.c_str(), _TRUNCATE);
			RetCode = 1;
		}
		else if (_stricmp(MetaData, "genre") == 0) {
			wcsncpy_s(dest, destlen, TagDataW.Genre.c_str(), _TRUNCATE);
			RetCode = 1;
		}
		else if (_stricmp(MetaData, "track") == 0) {
			wcsncpy_s(dest, destlen, TagDataW.Track.c_str(), _TRUNCATE);
			RetCode = 1;
		}
		else if (_stricmp(MetaData, "composer") == 0) {
			wcsncpy_s(dest, destlen, TagDataW.Composer.c_str(), _TRUNCATE);
			RetCode = 1;
		}
		else if (_stricmp(MetaData, "publisher") == 0) {
			wcsncpy_s(dest, destlen, TagDataW.Publisher.c_str(), _TRUNCATE);
			RetCode = 1;
		}
		else if (_stricmp(MetaData, "disc") == 0) {
			wcsncpy_s(dest, destlen, TagDataW.Disc.c_str(), _TRUNCATE);
			RetCode = 1;
		}
		else if (_stricmp(MetaData, "bpm") == 0) {
			wcsncpy_s(dest, destlen, TagDataW.BPM.c_str(), _TRUNCATE);
			RetCode = 1;
		}
		else {
			RetCode = 0;
		}

	}
	else {
		FileName = L"";
		RetCode = 0;
	}

	::LeaveCriticalSection(&CriticalSection);
	return RetCode;
}