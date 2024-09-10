/*****************************************************************************
 * OpenDecoder: Create the decoder instance
 *****************************************************************************/
static int OpenDecoder(vlc_object_t *p_this, pf_MediaCodecApi_init pf_init)
{
    decoder_t *p_dec = (decoder_t *)p_this;
    decoder_sys_t *p_sys;
    mc_api *api;
    const char *mime = NULL;

    /* Video or Audio if "mediacodec-audio" bool is true */
    if (p_dec->fmt_in.i_cat != VIDEO_ES && (p_dec->fmt_in.i_cat != AUDIO_ES
     || !var_InheritBool(p_dec, CFG_PREFIX "audio")))
        return VLC_EGENERIC;

    if (p_dec->fmt_in.i_cat == VIDEO_ES)
    {
        if (!p_dec->fmt_in.video.i_width || !p_dec->fmt_in.video.i_height)
        {
            /* We can handle h264 without a valid video size */
            if (p_dec->fmt_in.i_codec != VLC_CODEC_H264)
            {
                msg_Dbg(p_dec, "resolution (%dx%d) not supported",
                        p_dec->fmt_in.video.i_width, p_dec->fmt_in.video.i_height);
                return VLC_EGENERIC;
            }
        }

        switch (p_dec->fmt_in.i_codec) {
        case VLC_CODEC_HEVC: mime = "video/hevc"; break;
        case VLC_CODEC_H264: mime = "video/avc"; break;
        case VLC_CODEC_H263: mime = "video/3gpp"; break;
        case VLC_CODEC_MP4V: mime = "video/mp4v-es"; break;
        case VLC_CODEC_WMV3: mime = "video/x-ms-wmv"; break;
        case VLC_CODEC_VC1:  mime = "video/wvc1"; break;
        case VLC_CODEC_VP8:  mime = "video/x-vnd.on2.vp8"; break;
        case VLC_CODEC_VP9:  mime = "video/x-vnd.on2.vp9"; break;
        /* case VLC_CODEC_MPGV: mime = "video/mpeg2"; break; */
        }
    }
    else
    {
        switch (p_dec->fmt_in.i_codec) {
        case VLC_CODEC_AMR_NB: mime = "audio/3gpp"; break;
        case VLC_CODEC_AMR_WB: mime = "audio/amr-wb"; break;
        case VLC_CODEC_MPGA:
        case VLC_CODEC_MP3:    mime = "audio/mpeg"; break;
        case VLC_CODEC_MP2:    mime = "audio/mpeg-L2"; break;
        case VLC_CODEC_MP4A:   mime = "audio/mp4a-latm"; break;
        case VLC_CODEC_QCELP:  mime = "audio/qcelp"; break;
        case VLC_CODEC_VORBIS: mime = "audio/vorbis"; break;
        case VLC_CODEC_OPUS:   mime = "audio/opus"; break;
        case VLC_CODEC_ALAW:   mime = "audio/g711-alaw"; break;
        case VLC_CODEC_MULAW:  mime = "audio/g711-mlaw"; break;
        case VLC_CODEC_FLAC:   mime = "audio/flac"; break;
        case VLC_CODEC_GSM:    mime = "audio/gsm"; break;
        case VLC_CODEC_A52:    mime = "audio/ac3"; break;
        case VLC_CODEC_EAC3:   mime = "audio/eac3"; break;
        case VLC_CODEC_ALAC:   mime = "audio/alac"; break;
        case VLC_CODEC_DTS:    mime = "audio/vnd.dts"; break;
        /* case VLC_CODEC_: mime = "audio/mpeg-L1"; break; */
        /* case VLC_CODEC_: mime = "audio/aac-adts"; break; */
        }
    }
    if (!mime)
    {
        msg_Dbg(p_dec, "codec %4.4s not supported",
                (char *)&p_dec->fmt_in.i_codec);
        return VLC_EGENERIC;
    }

    api = calloc(1, sizeof(mc_api));
    if (!api)
        return VLC_ENOMEM;
    api->p_obj = p_this;
    api->b_video = p_dec->fmt_in.i_cat == VIDEO_ES;
    if (pf_init(api) != VLC_SUCCESS)
    {
        free(api);
        return VLC_EGENERIC;
    }

    /* Allocate the memory needed to store the decoder's structure */
    if ((p_sys = calloc(1, sizeof(*p_sys))) == NULL)
    {
        api->clean(api);
        free(api);
        return VLC_ENOMEM;
    }
    p_sys->api = api;
    p_dec->p_sys = p_sys;

    p_dec->pf_decode_video = DecodeVideo;
    p_dec->pf_decode_audio = DecodeAudio;

    p_dec->fmt_out.i_cat = p_dec->fmt_in.i_cat;
    p_dec->fmt_out.video = p_dec->fmt_in.video;
    p_dec->fmt_out.audio = p_dec->fmt_in.audio;
    p_dec->b_need_packetized = true;
    p_sys->mime = mime;
    p_sys->b_new_block = true;

    if (p_dec->fmt_in.i_cat == VIDEO_ES)
    {
        p_sys->u.video.i_width = p_dec->fmt_in.video.i_width;
        p_sys->u.video.i_height = p_dec->fmt_in.video.i_height;

        p_sys->u.video.timestamp_fifo = timestamp_FifoNew(32);
        if (!p_sys->u.video.timestamp_fifo)
        {
            CloseDecoder(p_this);
            return VLC_ENOMEM;
        }

        if (p_dec->fmt_in.i_codec == VLC_CODEC_H264)
            h264_get_profile_level(&p_dec->fmt_in,
                                   &p_sys->u.video.i_h264_profile, NULL, NULL);

        p_sys->psz_name = MediaCodec_GetName(VLC_OBJECT(p_dec), p_sys->mime,
                                              p_sys->u.video.i_h264_profile);
        if (!p_sys->psz_name)
        {
            CloseDecoder(p_this);
            return VLC_EGENERIC;
        }

        /* Check if we need late opening */
        switch (p_dec->fmt_in.i_codec)
        {
        case VLC_CODEC_H264:
            if (!p_sys->u.video.i_width || !p_sys->u.video.i_height)
            {
                msg_Warn(p_dec, "waiting for sps/pps for codec %4.4s",
                         (const char *)&p_dec->fmt_in.i_codec);
                return VLC_SUCCESS;
            }
        case VLC_CODEC_VC1:
            if (!p_dec->fmt_in.i_extra)
            {
                msg_Warn(p_dec, "waiting for extra data for codec %4.4s",
                         (const char *)&p_dec->fmt_in.i_codec);
                return VLC_SUCCESS;
            }
            break;
        }
    }
    else
    {
        p_sys->u.audio.i_channels = p_dec->fmt_in.audio.i_channels;

        p_sys->psz_name = MediaCodec_GetName(VLC_OBJECT(p_dec), p_sys->mime, 0);
        if (!p_sys->psz_name)
        {
            CloseDecoder(p_this);
            return VLC_EGENERIC;
        }

        /* Marvel ACodec assert if channel count is 0 */
        if (!strncmp(p_sys->psz_name, "OMX.Marvell",
                     __MIN(strlen(p_sys->psz_name), strlen("OMX.Marvell"))))
            p_sys->u.audio.b_need_channels = true;

        /* Check if we need late opening */
        switch (p_dec->fmt_in.i_codec)
        {
        case VLC_CODEC_VORBIS:
        case VLC_CODEC_MP4A:
            if (!p_dec->fmt_in.i_extra)
            {
                msg_Warn(p_dec, "waiting for extra data for codec %4.4s",
                         (const char *)&p_dec->fmt_in.i_codec);
                return VLC_SUCCESS;
            }
            break;
        }
        if (!p_sys->u.audio.i_channels && p_sys->u.audio.b_need_channels)
        {
            msg_Warn(p_dec, "waiting for valid channel count");
            return VLC_SUCCESS;
        }
    }

    return StartMediaCodec(p_dec);
}