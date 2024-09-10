ComponentResult encodeThisSourceFrame(VP8EncoderGlobals glob,
                                      ICMCompressorSourceFrameRef sourceFrame)
{
  vpx_codec_err_t codecError;
  ComponentResult err = noErr;
  const UInt8 *decoderDataPtr;
  int storageIndex = 0;

  //time is multiplied by 2 to allow space for altref frames
  UInt32 time2 = glob->frameCount * 2;
  dbg_printf("[vp8e - %08lx] encode this frame %08lx %ld  time2 %lu\n",
             (UInt32)glob, (UInt32)sourceFrame, glob->frameCount, time2);

  //long dispNumber = ICMCompressorSourceFrameGetDisplayNumber(sourceFrame);

  // Initialize codec if needed
  initializeCodec(glob, sourceFrame);

  ///////         Transfer the current frame to glob->raw
  if (sourceFrame != NULL)
  {
    if (glob->currentPass != VPX_RC_FIRST_PASS)
      addSourceFrame(glob,sourceFrame);
    err = convertColorSpace(glob, sourceFrame);
    if (err) goto bail;
    int flags = 0 ; //TODO - find out what I may need in these flags
    dbg_printf("[vp8e - %08lx]  vpx_codec_encode codec %x  raw %x framecount %d  flags %x\n", (UInt32)glob, glob->codec, glob->raw, glob->frameCount,  flags);
    //TODO seems like quality should be an option.  Right now hardcoded to GOOD_QUALITY
    codecError = vpx_codec_encode(glob->codec, glob->raw, time2,
                                  1, flags, VPX_DL_GOOD_QUALITY);
    dbg_printf("[vp8e - %08lx]  vpx_codec_encode codec exit\n", (UInt32)glob);
  }
  else  //sourceFrame is Null. this could be termination of a pass
  {
    int flags = 0 ; //TODO - find out what I may need in these flags
    dbg_printf("[vp8e - %08lx]  vpx_codec_encode codec %x  raw %x framecount %d ----NULL TERMINATION\n", (UInt32)glob, glob->codec, NULL, glob->frameCount,  flags);
    codecError = vpx_codec_encode(glob->codec, NULL, time2,
                                  1, flags, VPX_DL_GOOD_QUALITY);
  }
  glob->frameCount++ ;  //framecount gets reset on a new pass

  if (codecError)
  {
    const char *detail = vpx_codec_error_detail(glob->codec);
    dbg_printf("[vp8e - %08lx]  error vpx encode is %s\n", (UInt32)glob, vpx_codec_error(glob->codec));

    if (detail)
      dbg_printf("    %s\n", detail);

    goto bail;
  }


  vpx_codec_iter_t iter = NULL;
  int got_data = 0;

  while (1)
  {
    const vpx_codec_cx_pkt_t *pkt = vpx_codec_get_cx_data(glob->codec, &iter);

    if (pkt == NULL)
      break;

    got_data ++;

    switch (pkt->kind)
    {
      case VPX_CODEC_CX_FRAME_PKT:
        err = emitEncodedFrame(glob, pkt);
        if (err)
          goto bail;
        break;
      case VPX_CODEC_STATS_PKT:
        if (1)
        {
          unsigned long newSize = glob->stats.sz + pkt->data.twopass_stats.sz;
          glob->stats.buf = realloc(glob->stats.buf, newSize);
          if (!glob->stats.buf)
            return mFulErr;
          dbg_printf("[vp8e - %08lx] Reallocation buffer size to %ld\n", (UInt32)glob, newSize);
          memcpy((char*)glob->stats.buf + glob->stats.sz, pkt->data.twopass_stats.buf,
                 pkt->data.twopass_stats.sz);
          glob->stats.sz = newSize;
        }
        break;

      default:
        break;
    }
  }

  if (glob->currentPass == VPX_RC_FIRST_PASS)
  {
    //in the first pass no need to export any frames
    return err;
  }

bail:
  if (err)
    dbg_printf("[vp8e - %08lx]  bailed with err %d\n", (UInt32)glob, err);

  return err;
}