CDVDVideoCodec::VCReturn CDVDVideoCodecFFmpeg::GetPicture(VideoPicture* pVideoPicture)
{
  if (m_eof)
  {
    return VC_EOF;
  }

  // handle hw accelerators first, they may have frames ready
  if (m_pHardware)
  {
    int flags = m_codecControlFlags;
    flags &= ~DVD_CODEC_CTRL_DRAIN;
    m_pHardware->SetCodecControl(flags);
    CDVDVideoCodec::VCReturn ret = m_pHardware->Decode(m_pCodecContext, nullptr);
    if (ret == VC_PICTURE)
    {
      if (m_pHardware->GetPicture(m_pCodecContext, pVideoPicture))
        return VC_PICTURE;
      else
        return VC_ERROR;
    }
    else if (ret == VC_BUFFER)
      ;
    else
      return ret;
  }
  else if (m_pFilterGraph && !m_filterEof)
  {
    CDVDVideoCodec::VCReturn ret = FilterProcess(nullptr);
    if (ret == VC_PICTURE)
    {
      if (!SetPictureParams(pVideoPicture))
        return VC_ERROR;
      return VC_PICTURE;
    }
    else if (ret == VC_BUFFER)
      ;
    else
      return ret;
  }

  // process ffmpeg
  if (m_codecControlFlags & DVD_CODEC_CTRL_DRAIN)
  {
    AVPacket avpkt;
    av_init_packet(&avpkt);
    avpkt.data = nullptr;
    avpkt.size = 0;
    avpkt.dts = AV_NOPTS_VALUE;
    avpkt.pts = AV_NOPTS_VALUE;
    avcodec_send_packet(m_pCodecContext, &avpkt);
  }

  int ret = avcodec_receive_frame(m_pCodecContext, m_pDecodedFrame);

  if (m_decoderState == STATE_HW_FAILED && !m_pHardware)
    return VC_REOPEN;

  if(m_iLastKeyframe < m_pCodecContext->has_b_frames + 2)
    m_iLastKeyframe = m_pCodecContext->has_b_frames + 2;

  if (ret == AVERROR_EOF)
  {
    // next drain hw accel or filter
    if (m_pHardware)
    {
      int flags = m_codecControlFlags;
      flags |= DVD_CODEC_CTRL_DRAIN;
      m_pHardware->SetCodecControl(flags);
      int ret = m_pHardware->Decode(m_pCodecContext, nullptr);
      if (ret == VC_PICTURE)
      {
        if (m_pHardware->GetPicture(m_pCodecContext, pVideoPicture))
          return VC_PICTURE;
        else
          return VC_ERROR;
      }
      else
      {
        m_eof = true;
        CLog::Log(LOGDEBUG, "CDVDVideoCodecFFmpeg::GetPicture - eof hw accel");
        return VC_EOF;
      }
    }
    else if (m_pFilterGraph && !m_filterEof)
    {
      int ret = FilterProcess(nullptr);
      if (ret == VC_PICTURE)
      {
        if (!SetPictureParams(pVideoPicture))
          return VC_ERROR;
        else
          return VC_PICTURE;
      }
      else
      {
        m_eof = true;
        CLog::Log(LOGDEBUG, "CDVDVideoCodecFFmpeg::GetPicture - eof filter");
        return VC_EOF;
      }
    }
    else
    {
      m_eof = true;
      CLog::Log(LOGDEBUG, "CDVDVideoCodecFFmpeg::GetPicture - eof");
      return VC_EOF;
    }
  }
  else if (ret == AVERROR(EAGAIN))
  {
    return VC_BUFFER;
  }
  else if (ret)
  {
    CLog::Log(LOGERROR, "%s - avcodec_receive_frame returned failure", __FUNCTION__);
    return VC_ERROR;
  }

  // here we got a frame
  int64_t framePTS = m_pDecodedFrame->best_effort_timestamp;

  if (m_pCodecContext->skip_frame > AVDISCARD_DEFAULT)
  {
    if (m_dropCtrl.m_state == CDropControl::VALID &&
        m_dropCtrl.m_lastPTS != AV_NOPTS_VALUE &&
        framePTS != AV_NOPTS_VALUE &&
        framePTS > (m_dropCtrl.m_lastPTS + m_dropCtrl.m_diffPTS * 1.5))
    {
      m_droppedFrames++;
      if (m_interlaced)
        m_droppedFrames++;
    }
  }
  m_dropCtrl.Process(framePTS, m_pCodecContext->skip_frame > AVDISCARD_DEFAULT);

  if (m_pDecodedFrame->key_frame)
  {
    m_started = true;
    m_iLastKeyframe = m_pCodecContext->has_b_frames + 2;
  }
  if (m_pDecodedFrame->interlaced_frame)
    m_interlaced = true;
  else
    m_interlaced = false;

  if (!m_started)
  {
    int frames = 300;
    if (m_dropCtrl.m_state == CDropControl::VALID)
      frames = static_cast<int>(6000000 / m_dropCtrl.m_diffPTS);
    if (m_iLastKeyframe >= frames && m_pDecodedFrame->pict_type == AV_PICTURE_TYPE_I)
    {
      m_started = true;
    }
    else
    {
      av_frame_unref(m_pDecodedFrame);
      return VC_BUFFER;
    }
  }

  // push the frame to hw decoder for further processing
  if (m_pHardware)
  {
    av_frame_unref(m_pFrame);
    av_frame_move_ref(m_pFrame, m_pDecodedFrame);
    CDVDVideoCodec::VCReturn ret = m_pHardware->Decode(m_pCodecContext, m_pFrame);
    if (ret == VC_FLUSHED)
    {
      Reset();
      return ret;
    }
    else if (ret == VC_FATAL)
    {
      m_decoderState = STATE_HW_FAILED;
      return VC_REOPEN;
    }
    else if (ret == VC_PICTURE)
    {
      if (m_pHardware->GetPicture(m_pCodecContext, pVideoPicture))
        return VC_PICTURE;
      else
        return VC_ERROR;
    }

    return ret;
  }
  // process filters for sw decoding
  else
  {
    SetFilters();

    bool need_scale = std::find(m_formats.begin(),
                                m_formats.end(),
                                m_pCodecContext->pix_fmt) == m_formats.end();

    bool need_reopen = false;
    if (m_filters != m_filters_next)
      need_reopen = true;

    if (!m_filters_next.empty() && m_filterEof)
      need_reopen = true;

    if (m_pFilterIn)
    {
      if (m_pFilterIn->outputs[0]->format != m_pCodecContext->pix_fmt ||
          m_pFilterIn->outputs[0]->w != m_pCodecContext->width ||
          m_pFilterIn->outputs[0]->h != m_pCodecContext->height)
        need_reopen = true;
    }

    // try to setup new filters
    if (need_reopen || (need_scale && m_pFilterGraph == nullptr))
    {
      m_filters = m_filters_next;

      if (FilterOpen(m_filters, need_scale) < 0)
        FilterClose();
    }

    if (m_pFilterGraph && !m_filterEof)
    {
      CDVDVideoCodec::VCReturn ret = FilterProcess(m_pDecodedFrame);
      if (ret != VC_PICTURE)
        return VC_NONE;
    }
    else
    {
      av_frame_unref(m_pFrame);
      av_frame_move_ref(m_pFrame, m_pDecodedFrame);
    }

    if (!SetPictureParams(pVideoPicture))
      return VC_ERROR;
    else
      return VC_PICTURE;
  }

  return VC_NONE;
}