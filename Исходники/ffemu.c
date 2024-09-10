static bool ffemu_init_audio(ffemu_t *handle)
{
   struct ff_config_param *params = &handle->config;
   struct ff_audio_info *audio    = &handle->audio;
   struct ff_video_info *video    = &handle->video;
   struct ffemu_params *param     = &handle->params;

   AVCodec *codec = avcodec_find_encoder_by_name(*params->acodec ? params->acodec : "flac");
   if (!codec)
   {
      RARCH_ERR("[FFmpeg]: Cannot find acodec %s.\n", *params->acodec ? params->acodec : "flac");
      return false;
   }

   audio->encoder = codec;

   audio->codec = avcodec_alloc_context3(codec);

   audio->codec->codec_type     = AVMEDIA_TYPE_AUDIO;
   audio->codec->channels       = param->channels;
   audio->codec->channel_layout = param->channels > 1 ? AV_CH_LAYOUT_STEREO : AV_CH_LAYOUT_MONO;

   ffemu_audio_resolve_format(audio, codec);
   ffemu_audio_resolve_sample_rate(handle, codec);

   if (params->sample_rate)
   {
      audio->ratio = (double)params->sample_rate / param->samplerate;
      audio->codec->sample_rate = params->sample_rate;
      audio->codec->time_base = av_d2q(1.0 / params->sample_rate, 1000000);

      rarch_resampler_realloc(&audio->resampler_data,
            &audio->resampler,
            g_settings.audio.resampler,
            audio->ratio);
   }
   else
   {
      audio->codec->sample_fmt = AV_SAMPLE_FMT_S16;
      audio->codec->sample_rate = (int)roundf(param->samplerate);
      audio->codec->time_base = av_d2q(1.0 / param->samplerate, 1000000);
   }

   if (params->audio_qscale)
   {
      audio->codec->flags |= CODEC_FLAG_QSCALE;
      audio->codec->global_quality = params->audio_global_quality;
   }
   else if (params->audio_bit_rate)
      audio->codec->bit_rate = params->audio_bit_rate;

   // Allow experimental codecs.
   audio->codec->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;

   if (handle->muxer.ctx->oformat->flags & AVFMT_GLOBALHEADER)
      audio->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;

   if (avcodec_open2(audio->codec, codec, params->audio_opts ? &params->audio_opts : NULL) != 0)
      return false;

   if (!audio->codec->frame_size) // If not set (PCM), just set something.
      audio->codec->frame_size = 1024;

   audio->buffer = (uint8_t*)av_malloc(
         audio->codec->frame_size *
         audio->codec->channels *
         audio->sample_size);

   //RARCH_LOG("[FFmpeg]: Audio frame size: %d.\n", audio->codec->frame_size);

   if (!audio->buffer)
      return false;

   audio->outbuf_size = FF_MIN_BUFFER_SIZE;
   audio->outbuf = (uint8_t*)av_malloc(audio->outbuf_size);
   if (!audio->outbuf)
      return false;

   return true;
}