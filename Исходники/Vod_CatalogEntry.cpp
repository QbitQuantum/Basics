    bool CatalogEntry::loadFrame ( uint32_t frameId, Buffer & destBuf ) const
    {
        std::string header;
        char * headerCstr;
        std::ostringstream oss;
        uint64_t headerSize;
        uint64_t fileSize;

        // Fetchs the image file path
        CatalogImages::const_iterator it = mpimages -> find ( frameId );

        if ( it == mpimages -> end ( ) )
        {
            return false;
        }

        // Opens the file
        std::ifstream f ( "data/" + it -> second, std::ios::binary | std::ios::ate );

        if ( ! f.is_open ( ) )
        {
            std::cerr << "Unable to open image file '" << it -> second << "'" << std::endl;
            return false;
        }

        fileSize = ( uint64_t ) f.tellg ( );
        f.seekg ( 0, f.beg );

        // Prepares the header
        oss << frameId << "\r\n" << fileSize << "\r\n";
        header = oss.str ( );
        headerSize = header.length ( );
        headerCstr = ( char * ) header.c_str ( );

        // Copies header and file in buffer
        destBuf.allocate ( headerSize + fileSize );
        destBuf.memcpy ( 0, headerCstr, headerSize );

        f.read ( destBuf.data ( ) + headerSize, ( int64_t ) fileSize );
        f.close ( );

        return true;
    }