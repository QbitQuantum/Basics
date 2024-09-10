    /**
     *  Decompress a character buffer.
     *
     *  inbuf    - the compressed buffer.
     *  inbufsz  - size of the compressed buffer.
     *  outbufsz - suggested initial size for the output buffer,
     *             set to inbufsz if 0.
     *  outbuf   - the decompressed buffer, use free_gzip to release it.
     */
    void decode_gzip( const char *inbuf, size_t inbufsz, size_t &outbufsz,
                      char *&outbuf )
    {
        Compress compressor;
        int insize = (int) inbufsz;
        int outsize = (int) outbufsz;

        /*  Allocate the initial quantity of memory suggested. */
        outbuf = (char *) malloc( outbufsz ? outbufsz : inbufsz );
        compressor.decompress( inbuf, insize, outbuf, outsize,
                               Compress::GZIP_COMPRESS );
        outbufsz = (size_t) outsize;
    }