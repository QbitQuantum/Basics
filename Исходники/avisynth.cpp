int avisynth_read_packet(BYTE *pData, LONG pDataSize)
{
    HRESULT res;
    AVISynthStream *stream;
    int stream_id = avs->next_stream;
    assert(stream_id == 0);
    LONG read_size;

    // handle interleaving manually...
    stream = &avs->streams[stream_id];

    // read is the pts? that always increases...
    //if (stream->read >= stream->info.dwLength)
    //  return -1;

    // chunck_size is an avisynth thing. whoa!
    if(pDataSize < stream->chunck_size)
        assert(false);

    // guess we have our own concept of stream_index, maybe?
    // pkt->stream_index = stream_id;
    // is this like a pts integer or something?
    __int64 pts = avs->streams[stream_id].read / avs->streams[stream_id].chunck_samples;

    // I think this will block until data is available, or 0 for EOF [?]
    res = AVIStreamRead(stream->handle, stream->read, stream->chunck_samples, pData, stream->chunck_size, &read_size, NULL);

    __int64 size = read_size;

    assert(pDataSize >= read_size);

    stream->read += stream->chunck_samples;

    // I guess with avi you're just supposed to read one stream, then the next, forever? huh?

    /*
    // prepare for the next stream to read
    do {
      avs->next_stream = (avs->next_stream+1) % avs->nb_streams;
    } while (avs->next_stream != stream_id && s->streams[avs->next_stream]->discard >= AVDISCARD_ALL);
    */
    return (res == S_OK) ? read_size : -1;
}