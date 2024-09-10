 int32_t __srs_stream_read_4bytes(char* pp)
 {
     static SrsStream stream;
     
     int ret = stream.initialize(pp, 4);
     srs_assert(ret == ERROR_SUCCESS);
     
     return stream.read_4bytes();
 }