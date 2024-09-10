    /**
        Determines whether the specified file exists

        \param[in]      path        Path to file
        \returns        true        iff the path refers to a file (not a directory) and the file exists

        The Exists method should not be used for path validation, this method merely checks
        if the file specified in path exists. Passing an invalid path to Existsl returns false.

        Be aware that another process can potentially do something with the file in between the
        time you call the Exists method and perform another operation on the file, such as Delete.
        A recommended programming practice is to wrap the Exists method, and the operations you
        take on the file, in a try...catch block. The Exists method can only help to ensure that the
        file will be available, it cannot guarantee it.

        The path parameter is permitted to specify relative or absolute path information.
        Relative path information is interpreted as relative to the current working directory.
        To obtain the current working directory, see GetCurrentDirectory.

        \note If path describes a directory, this method returns false.
    */
    bool SCXFile::Exists(const SCXFilePath& path) {
#if defined(WIN32)
        struct __stat64 buf;
        int failure = _wstat64(path.Get().c_str(), &buf );
#elif defined(SCX_UNIX)
        SCXFileSystem::SCXStatStruct buf;
        std::string localizedName = SCXFileSystem::EncodePath(path);
        int failure = SCXFileSystem::Stat(localizedName.c_str(), &buf );
#else
#error
#endif
        return !failure && !(buf.st_mode & S_IFDIR);
    }