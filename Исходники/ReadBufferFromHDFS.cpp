    ReadBufferFromHDFSImpl(const std::string & hdfs_name_)
        : hdfs_uri(hdfs_name_)
        , builder(createHDFSBuilder(hdfs_uri))
        , fs(createHDFSFS(builder.get()))
    {

        auto & path = hdfs_uri.getPath();
        fin = hdfsOpenFile(fs.get(), path.c_str(), O_RDONLY, 0, 0, 0);

        if (fin == nullptr)
            throw Exception("Unable to open HDFS file: " + path + " error: " + std::string(hdfsGetLastError()),
                ErrorCodes::CANNOT_OPEN_FILE);
    }