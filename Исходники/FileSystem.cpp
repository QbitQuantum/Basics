    // Initializes a new instance of the FileSystemInfo class.
    FileSystemInfo::FileSystemInfo(const TString& path)
    {
        size_t pathLen = path.Length();
        size_t lastPos = pathLen - 1;

        // remove all the '\\'s at the end of the path
        while (lastPos != 0 && path[lastPos] == '\\')
            lastPos--;

        if (lastPos == 0 && path[lastPos] == '\\')
            _path = "";
        else
            _path = path.Substring(0, lastPos + 1);
    }