static void FindFiles(std::vector<std::string>& matches, const std::string& datadir, const std::string& dir, const boost::regex &regexpattern, int flags)
{
#ifdef _WIN32
    WIN32_FIND_DATA wfd;
    HANDLE hFind = FindFirstFile((datadir + dir + "\\*").c_str(), &wfd);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if(strcmp(wfd.cFileName,".") && strcmp(wfd.cFileName ,"..")) {
                if(!(wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)) {
                    if ((flags & FileSystem::ONLY_DIRS) == 0) {
                        if (boost::regex_match(wfd.cFileName, regexpattern)) {
                            matches.push_back(dir + wfd.cFileName);
                        }
                    }
                } else {
                    if (flags & FileSystem::INCLUDE_DIRS) {
                        if (boost::regex_match(wfd.cFileName, regexpattern)) {
                            matches.push_back(dir + wfd.cFileName + "\\");
                        }
                    }
                    if (flags & FileSystem::RECURSE) {
                        FindFiles(matches, datadir, dir + wfd.cFileName + "\\", regexpattern, flags);
                    }
                }
            }
        } while (FindNextFile(hFind, &wfd));
        FindClose(hFind);
    }
#else
    DIR* dp;
    struct dirent* ep;

    if (!(dp = opendir((datadir + dir).c_str()))) {
        return;
    }

    while ((ep = readdir(dp))) {
        // exclude hidden files
        if (ep->d_name[0] != '.') {
            // is it a file? (we just treat sockets / pipes / fifos / character&block devices as files...)
            // (need to stat because d_type is DT_UNKNOWN on linux :-/)
            struct stat info;
            if (stat((datadir + dir + ep->d_name).c_str(), &info) == 0) {
                if (!S_ISDIR(info.st_mode)) {
                    if ((flags & FileSystem::ONLY_DIRS) == 0) {
                        if (boost::regex_match(ep->d_name, regexpattern)) {
                            matches.push_back(dir + ep->d_name);
                        }
                    }
                } else {
                    // or a directory?
                    if (flags & FileSystem::INCLUDE_DIRS) {
                        if (boost::regex_match(ep->d_name, regexpattern)) {
                            matches.push_back(dir + ep->d_name + "/");
                        }
                    }
                    if (flags & FileSystem::RECURSE) {
                        FindFiles(matches, datadir, dir + ep->d_name + "/", regexpattern, flags);
                    }
                }
            }
        }
    }
    closedir(dp);
#endif
}