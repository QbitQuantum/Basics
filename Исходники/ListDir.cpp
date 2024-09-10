void ListDir(const std::string& path, bool directories, void (*CallBack)(const std::string& filename, void* param), void* param, std::list<std::string> *liste)
{
    // Pfad zum Ordner, wo die Dateien gesucht werden sollen
    std::string rpath = path.substr(0, path.find_last_of('/') + 1);

    // Pfad in Kleinbuchstaben umwandeln
    std::string filen(path);
    std::transform(path.begin(), path.end(), filen.begin(), tolower);

    //LOG.lprintf("%s\n", filen.c_str());
    // Dateiendung merken
    size_t pos = path.find_last_of('.');
    if(pos == std::string::npos)
        return;

    std::string endung = path.substr(pos + 1);

#ifdef _WIN32
    HANDLE hFile;
    WIN32_FIND_DATAA wfd;

    hFile = FindFirstFileA(path.c_str(), &wfd);
    if(hFile != INVALID_HANDLE_VALUE)
    {
        do
        {
            std::string whole_path = rpath + wfd.cFileName;

            bool push = true;
            if(!directories && ( (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) )
                push = false;

            if(push)
            {
                if(CallBack)
                    CallBack(whole_path.c_str(), param);
                if(liste)
                    liste->push_back(whole_path);
            }
        }
        while(FindNextFileA(hFile, &wfd));

        FindClose(hFile);
    }
#else
    DIR* dir_d;
    dirent* dir = NULL;
    if ((dir_d = opendir(rpath.c_str())) != NULL)
    {
        while( (dir = readdir(dir_d)) != NULL)
        {
            struct stat file_stat;
            std::string whole_path = rpath + dir->d_name;

            stat(whole_path.c_str(), &file_stat);

            bool push = true;
            if(!directories && S_ISDIR(file_stat.st_mode))
                push = false;

            if(push)
            {
                std::string ende = dir->d_name;
                size_t pos = ende.find_last_of('.');
                if(pos == std::string::npos)
                    continue;

                ende = ende.substr(pos + 1);

                if(endung != ende)
                    std::transform(ende.begin(), ende.end(), ende.begin(), tolower);

                //LOG.lprintf("%s == %s\n", endung.c_str(), ende.c_str());

                if(endung != ende)
                    continue;

                if(CallBack)
                    CallBack(whole_path, param);
                if(liste)
                    liste->push_back(whole_path);
            }
        }
        closedir(dir_d);
        if(liste)
            liste->sort();
    }
#endif // _WIN32

}