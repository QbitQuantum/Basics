std::string get_codec_name(AVCodecContext *pCodecCtx)
{
  AVCodecID id = pCodecCtx->codec_id;

  // Grab the codec
  const AVCodec *p = avcodec_find_decoder(id);
  const AVCodecDescriptor *desc = avcodec_descriptor_get(id);
  const char *profile = avcodec_profile_name(id, pCodecCtx->profile);

  std::ostringstream codec_name;

  const char *nice_name = nullptr;
  for (int i = 0; i < countof(nice_codec_names); ++i)
  {
    if (nice_codec_names[i].id == id) {
      nice_name = nice_codec_names[i].name;
      break;
    }
  }

  if (id == AV_CODEC_ID_DTS && pCodecCtx->codec_tag == 0xA2) {
    profile = "DTS Express";
  }

  if (id == AV_CODEC_ID_H264 && profile) {
    codec_name << nice_name << " " << tolower(profile);
    if (pCodecCtx->level && pCodecCtx->level != FF_LEVEL_UNKNOWN && pCodecCtx->level < 1000) {
      char l_buf[5];
      sprintf_s(l_buf, "%.1f", pCodecCtx->level / 10.0);
      codec_name << " L" << l_buf;
    }
  } else if (id == AV_CODEC_ID_VC1 && profile) {
    codec_name << nice_name << " " << tolower(profile);
    if (pCodecCtx->level != FF_LEVEL_UNKNOWN) {
      codec_name << " L" << pCodecCtx->level;
    }
  } else if (id == AV_CODEC_ID_DTS && profile) {
    codec_name << tolower(profile);
  } else if (id == AV_CODEC_ID_JPEG2000 && profile) {
    codec_name << tolower(profile);
  } else if (nice_name) {
    codec_name << nice_name;
    if (profile)
      codec_name << " " << tolower(profile);
  } else if (desc && desc->name) {
    codec_name << desc->name;
    if (profile)
      codec_name << " " << tolower(profile);
  } else if (p && p->name) {
    codec_name << p->name;
    if (profile)
      codec_name << " " << tolower(profile);
  } else {
    /* output avi tags */
    char buf[32];
    av_get_codec_tag_string(buf, sizeof(buf), pCodecCtx->codec_tag);
    codec_name << buf;
    sprintf_s(buf, "0x%04X", pCodecCtx->codec_tag);
    codec_name  << " / " << buf;
  }
  return codec_name.str();
}