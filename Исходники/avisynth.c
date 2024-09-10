static int avisynth_read_packet(AVFormatContext *s, AVPacket *pkt)
{
  AVISynthContext *avs = s->priv_data;
  HRESULT res;
  AVISynthStream *stream;
  int stream_id = avs->next_stream;
  LONG read_size;

  // handle interleaving manually...
  stream = &avs->streams[stream_id];

  if (stream->read >= stream->info.dwLength)
    return AVERROR(EIO);

  if (av_new_packet(pkt, stream->chunck_size))
    return AVERROR(EIO);
  pkt->stream_index = stream_id;
  pkt->pts = avs->streams[stream_id].read / avs->streams[stream_id].chunck_samples;

  res = AVIStreamRead(stream->handle, stream->read, stream->chunck_samples, pkt->data, stream->chunck_size, &read_size, NULL);

  pkt->pts = stream->read;
  pkt->size = read_size;

  stream->read += stream->chunck_samples;

  // prepare for the next stream to read
  do {
    avs->next_stream = (avs->next_stream+1) % avs->nb_streams;
  } while (avs->next_stream != stream_id && s->streams[avs->next_stream]->discard >= AVDISCARD_ALL);

  return (res == S_OK) ? pkt->size : -1;
}