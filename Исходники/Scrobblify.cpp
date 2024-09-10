/**
 * Scrobbles a track. Also finds meta data, length and (possibly) album, for
 * the current track.
 */
int Scrobblify::Start(const std::wstring& artist,
                      const std::wstring& track) {
    // Handle currently playing track
    if (current_request_id_ > 0) {
        Stop();
    }

    // Lines are divided into fields terminated by 0x1
    const wchar_t kDelimiterChar = 0x1;
    const wchar_t kDelimiter[] = {kDelimiterChar, _T('\0')};
    const size_t kDelimiterLength = 1;
    const size_t kHashLength = 32;
    const size_t kLongHashLength = 40;

    // Search all the meta-data files available
    for (std::vector<std::wstring>::const_iterator it = metadata_paths_.begin();
            it != metadata_paths_.end();
            ++it) {
        // Go get some meta data
        FILE *metadata_file;

        if (_wfopen_s(&metadata_file, (*it).c_str(), _T("r")) != 0) {
            continue;
        }

        std::wifstream in(metadata_file);
        const size_t kMaxLineLength = 2048;
        wchar_t line[kMaxLineLength];

        // Skip first line (contains "21" for no apparent reason)
        in.getline(line, kMaxLineLength);

        // Skip if file is empty
        if (wcsnlen(line, 1) == 0) {
            in.close();
            continue;
        }

        // Find hash for artist
        wchar_t artist_hash[kHashLength];
        bool artist_hash_found = false;

        for (;
                wcsnlen(line, kMaxLineLength) > 0;
                in.getline(line, kMaxLineLength)) {
            if (wcsncmp(artist.c_str(),
                        &line[kHashLength + kDelimiterLength],
                        artist.size()) == 0) {
                artist_hash_found = true;
                wcsncpy(artist_hash, line, kHashLength);
                break;
            }
        }

        if (!artist_hash_found) {
            in.close();
            continue; // Try next file
        }

        // Skip rest of artist section
        for (in.getline(line, kMaxLineLength);
                wcsnlen(line, kMaxLineLength) > 0;
                in.getline(line, kMaxLineLength)) {}

        in.getline(line, kMaxLineLength); // Skip section separator
        std::wifstream::pos_type album_section_position = in.tellg();

        // Skip albums section -- move to next empty line
        for (;
                wcsnlen(line, kMaxLineLength) > 0;
                in.getline(line, kMaxLineLength)) { }

        // Parse songs section. Each song is formatted like
        //   hash        32 bytes
        //   track
        //   artists     ; split with 0x2
        //   long hash
        //   length
        //   ...
        int length = 0;
        bool track_found = false;
        wchar_t album_hash[kHashLength];

        for (in.getline(line, kMaxLineLength);
                wcsnlen(line, kMaxLineLength) > 0;
                in.getline(line, kMaxLineLength)) {
            if (wcsncmp(track.c_str(),
                        &line[kHashLength + kDelimiterLength],
                        track.size()) == 0) {
                // Skip hash, separator, track, separator.
                wchar_t *p = &line[kHashLength + kDelimiterLength + track.size() +
                                   kDelimiterLength];

                // Match any of the artists
                bool artist_match_found = wcsncmp(artist_hash, p, kHashLength) == 0;

                for (p += kHashLength;
                        *p == 0x2;
                        p += kHashLength + kDelimiterLength) {
                    if (!artist_match_found && // Don't compare if artist has been found
                            wcsncmp(artist_hash, &p[1], kHashLength) == 0) {
                        artist_match_found = true;
                    }
                }

                if (!artist_match_found) {
                    continue;
                }

                p += kDelimiterLength + kLongHashLength + kDelimiterLength;

                // Read track length
                length = _wtoi(p);
                track_found = true;

                // Skip length
                p = wcschr(p, kDelimiterChar);
                p += kDelimiterLength;

                // Skip track number
                p = wcschr(p, kDelimiterChar);
                p += kDelimiterLength;

                // Get album hash
                wcsncpy(album_hash, p, kHashLength);
                break;
            }
        }

        if (!track_found || length <= 0) {
            in.close();
            continue;
        }

        // Get album
        in.seekg(album_section_position); // Seek back to the album section
        std::wstring album;

        for (in.getline(line, kMaxLineLength);
                wcsnlen(line, kMaxLineLength) > 0;
                in.getline(line, kMaxLineLength)) {
            if (wcsncmp(album_hash, line, kHashLength) == 0) {
                size_t album_length = wcscspn(&line[kHashLength + kDelimiterLength],
                                              kDelimiter);
                album.assign(line, kHashLength + kDelimiterLength, album_length);
                break;
            }
        }

        in.close();
        return current_request_id_ = scrob_submitter_.Start(
                                         ToUtf8(artist),
                                         ToUtf8(track),
                                         ToUtf8(album),
                                         "",
                                         length,
                                         scrobble_directory_);
    }

    // No meta-data found; fall back on a five minute track length
    // TODO(liesen): does this violate any AudioScrobbler rules?
    return current_request_id_ = scrob_submitter_.Start(
                                     ToUtf8(artist),
                                     ToUtf8(track),
                                     "",
                                     "",
                                     5 * 60, // five minutes -- more than most songs
                                     scrobble_directory_);
}