static size_t gzip_read_max(stream_t stream,void*buf,size_t count){
    stream->rd.next_out=buf;
    stream->rd.avail_out=count;
    int res;
    do {
        if (stream->rd.avail_in==0){
            stream->rd.next_in=stream->rd_buf;
            stream->rd.avail_in=stream_read_max(stream->s,stream->rd_buf,stream->bufsize);
        }
        if (stream->compress){
            res=inflate(&stream->rd, Z_NO_FLUSH);
        } else {
            res=deflate(&stream->rd, Z_NO_FLUSH);
        }
        if(res!=Z_OK && res!=Z_STREAM_END){
            Abort("compression error %d %s",res,zError(res));
        }
    } while(stream->rd.avail_out && res!=Z_STREAM_END);
    return (count-stream->rd.avail_out);
}