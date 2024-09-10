void mpgfile::decodegop(int start, int stop, std::list<avframe*> &framelist)
{
  stream *S=&s[videostream()];
  if (!S->avcc)
    return;

  if (start<0)
    start=0;
  if (stop<0)
    stop=nextiframe(start+1)+1;
  else if (stop<=start)
    stop=start+1;
  if (stop>pictures)
    stop=pictures;

  if (stop<=start)
    return;
  int pic=lastseqheader(lastiframe(start));
  int streampic=idx.indexnr(pic);
  int seqnr=idx[streampic].getsequencenumber();

  streamhandle s(idx[streampic].getpos().packetposition());
  streamdata *sd=s.newstream(VIDEOSTREAM,streamtype::mpeg2video,istransportstream());

  if (idx[streampic].getpos().packetoffset()>0)
  {
    while( sd->inbytes()<idx[streampic].getpos().packetoffset() )
    {
      if (streamreader(s)<=0)
        return;
    }
    sd->discard(idx[streampic].getpos().packetoffset());
  }

  if (int rv=avcodec_open2(S->avcc, S->dec, NULL))
  {
    fprintf(stderr,"avcodec_open returned %d\n",rv);
    return;
  }
  avframe avf;
  int last_cpn=-1;
  bool firstframe=true, firstsequence=true;

  while (pic<stop && streampic<idx.getpictures())
  {
    filepos_t tp(getfilesize(),0);
    if ((streampic+1)<idx.getpictures())
      tp=idx[streampic+1].getpos();
    while (sd->itemlist().empty() || s.fileposition<tp.fileposition())
      if (streamreader(s)<=0)
        break;

    int bytes=sd->inbytes();

    for(streamdata::itemlisttype::const_iterator it=sd->itemlist().begin();it!=sd->itemlist().end();++it)
      if (it->fileposition.packetposition()==tp.packetposition())
      {
        bytes=it->bufferposition-sd->getoffset()+tp.packetoffset()-it->fileposition.packetoffset();
        break;
      }
      else
        if (it->fileposition.packetposition()>tp.packetposition())
        {
          bytes=it->bufferposition-sd->getoffset();
          break;
        }

    if (!firstframe && idx[streampic].getseqheader())
      firstsequence=false;
    firstframe=false;

    if (!firstsequence || idx[streampic].getsequencenumber()>=seqnr)
    {
      const uint8_t *data=(const uint8_t*)sd->getdata();
      int frameFinished=0;

      int decodebytes=bytes;
      while (decodebytes>0)
      {
        frameFinished=0;

        AVPacket pkt;
        av_init_packet( &pkt );
        pkt.data = (uint8_t*) data;
        pkt.size = decodebytes;
        int bytesDecoded=avcodec_decode_video2( S->avcc, avf,
                                        &frameFinished, &pkt );

        if (bytesDecoded<0)
        {
          fprintf(stderr,"libavcodec error while decoding frame #%d\n",pic);
          avcodec_close(S->avcc);
          return;
        }

        data+=bytesDecoded;
        decodebytes-=bytesDecoded;

        if (frameFinished)
        {
          //fprintf(stderr, "* decoded frame %5d ilace:%d typ:%d pts=%f\n", pic, avf->interlaced_frame, avf->pict_type, (double)avf->pts/90000.0);
          if (last_cpn!=avf->coded_picture_number)
          {
            last_cpn=avf->coded_picture_number;
            if (pic>=start)
              framelist.push_back(new avframe(avf,S->avcc));
            ++pic;
            if (pic>=stop)
            {
              frameFinished=0;
              decodebytes=0;
              break;
            }
          }
          else
            frameFinished=0;
        }
      }
    }

    sd->discard(bytes);
    ++streampic;
  }

  if (pic < stop)
  {
    int frameFinished=0;

    AVPacket pkt;
    av_init_packet( &pkt );
    pkt.data = NULL;
    pkt.size = 0;
    avcodec_decode_video2( S->avcc, avf,
                                        &frameFinished, &pkt );

    if (frameFinished)
    {
      if (last_cpn!=avf->coded_picture_number)
      {
        last_cpn=avf->coded_picture_number;
        if (pic>=start)
          framelist.push_back(new avframe(avf,S->avcc));
      }
    }
  }

  time_base_num = S->avcc->time_base.num;
  time_base_den = S->avcc->time_base.den;
  if (S->avcc->ticks_per_frame > 0) {
    //fprintf(stderr, "field rate -> frame rate\n");
    time_base_num *= S->avcc->ticks_per_frame;
  }

  avcodec_close(S->avcc);
}