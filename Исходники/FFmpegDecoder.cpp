bool FFmpegDecoder::Open(FileSpecifier& File)
{
	Close();
    
    // make sure one-time setup succeeded
    if (!av || !av->temp_data || !av->fifo)
        return false;
    
    // open the file
    if (avformat_open_input(&av->ctx, File.GetPath(), NULL, NULL) != 0)
        return false;
    
    // retrieve format info
    if (avformat_find_stream_info(av->ctx, NULL) < 0)
    {
        Close();
        return false;
    }
    
    // find the audio
    AVCodec *codec;
    av->stream_idx = av_find_best_stream(av->ctx, AVMEDIA_TYPE_AUDIO, -1, -1, &codec, 0);
    if (av->stream_idx < 0)
    {
        Close();
        return false;
    }
    av->stream = av->ctx->streams[av->stream_idx];
    if (avcodec_open2(av->stream->codec, codec, NULL) < 0)
    {
        Close();
        return false;
    }
    channels = av->stream->codec->channels;
    rate = av->stream->codec->sample_rate;
	
	return true;
}