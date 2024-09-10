void TsubtitlesFile::findPossibleSubtitles(const char_t *aviFlnm, const char_t *sdir, strings &files, subtitleFilesSearchMode searchMode)
{
    if (!aviFlnm || !sdir) {
        return;
    }
    char_t avidir[MAX_PATH];
    if (aviFlnm[0]) {
        char_t dsk[MAX_PATH], dir[MAX_PATH], name[MAX_PATH];
        _splitpath_s(aviFlnm, dsk, MAX_PATH, dir, MAX_PATH, name, MAX_PATH, NULL, 0);
        _makepath_s(avidir, countof(avidir), dsk, dir, NULL, NULL);
    } else {
        strcpy(avidir, _l("."));
    }
    strings dirs;
    strtok(sdir, _l(";"), dirs);
    fixRelativePaths(dirs, avidir);
    for (strings::const_iterator sd = dirs.begin(); sd != dirs.end(); sd++) {
        findPossibleSubtitles(sd->c_str(), files);
    }

    // If search mode is "search video file match then heuristic", then test if at least 1 subtitle filename matches with the video filename
    bool videoFileMatch = false;
    ffstring videoFlnmNoExt;
    extractfilenameWOext(aviFlnm, videoFlnmNoExt);
    videoFlnmNoExt.ConvertToLowerCase();

    if (searchMode == SUBFILES_VIDEO_FILE_HEURISTIC) {
        for (strings::iterator f = files.begin(); f != files.end(); f++) {
            ffstring flnmNoExt;
            extractfilenameWOext((*f).c_str(), flnmNoExt);
            flnmNoExt.ConvertToLowerCase();
            if (strncmp(videoFlnmNoExt.c_str(), flnmNoExt.c_str(), videoFlnmNoExt.length()) == 0) {
                /* Common portion of video and subtitle filenames. Check if lengths are equal (identical names)
                   or if this is a dot "." right after like in videofile.<suffix>.ext */
                if (videoFlnmNoExt.length() == flnmNoExt.length() || flnmNoExt[videoFlnmNoExt.length()] == _l('.')) {
                    videoFileMatch = true;
                    break;
                }
            }
        }
    }

    if (searchMode != SUBFILES_ALL) {
        EditDistance dist;
        for (strings::iterator f = files.begin(); f != files.end();) {
            ffstring flnmNoExt;
            extractfilenameWOext((*f).c_str(), flnmNoExt);
            flnmNoExt.ConvertToLowerCase();
            // If search mode is based on video file name removes the non matching entries
            if (searchMode == SUBFILES_VIDEO_FILE_MATCH
                    || (searchMode == SUBFILES_VIDEO_FILE_HEURISTIC && videoFileMatch)) {
                if (strncmp(videoFlnmNoExt.c_str(), flnmNoExt.c_str(), videoFlnmNoExt.length()) != 0
                        || (videoFlnmNoExt.length() != flnmNoExt.length() && flnmNoExt[videoFlnmNoExt.length()] != _l('.'))) {
                    f = files.erase(f);
                } else {
                    f++;
                }
                continue;
            }

            // Heuristic search
            int distance = dist.CalEditDistance(videoFlnmNoExt.c_str(), flnmNoExt.c_str(), 2 * MAX_PATH);
            //DPRINTF(_l("Subtitle files : %s vs %s match result = %d"), flnmNoExt.c_str(), videoFlnmNoExt.c_str(), distance);
            if (distance > SUBFILES_HEURISTIC_LIMIT) {
                f = files.erase(f);
            } else {
                f++;
            }
        }
    }
}