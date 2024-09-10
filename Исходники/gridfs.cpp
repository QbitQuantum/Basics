    BSONObj GridFS::storeFile( const char* data , size_t length , const string& remoteName , const string& contentType){
        massert("large files not yet implemented", length <= 0xffffffff);
        char const * const end = data + length;

        OID id;
        id.init();
        BSONObj idObj = BSON("_id" << id);

        int chunkNumber = 0;
        while (data < end){
            int chunkLen = MIN(DEFAULT_CHUNK_SIZE, end-data);
            Chunk c(idObj, chunkNumber, data, chunkLen);
            _client.insert( _chunksNS.c_str() , c._data );

            chunkNumber++;
            data += chunkLen;
        }

        return insertFile(remoteName, id, length, contentType);
    }