/* Returns the number of sound data frames or negative on error */
static unsigned int get_aiff_header(AVFormatContext *s, int size,
                                    unsigned version)
{
    AVIOContext *pb        = s->pb;
    AVCodecContext *codec  = s->streams[0]->codec;
    AIFFInputContext *aiff = s->priv_data;
    int exp;
    uint64_t val;
    double sample_rate;
    unsigned int num_frames;

    if (size & 1)
        size++;
    codec->codec_type = AVMEDIA_TYPE_AUDIO;
    codec->channels = avio_rb16(pb);
    num_frames = avio_rb32(pb);
    codec->bits_per_coded_sample = avio_rb16(pb);

    exp = avio_rb16(pb);
    val = avio_rb64(pb);
    sample_rate = ldexp(val, exp - 16383 - 63);
    codec->sample_rate = sample_rate;
    size -= 18;

    /* get codec id for AIFF-C */
    if (version == AIFF_C_VERSION1) {
        codec->codec_tag = avio_rl32(pb);
        codec->codec_id  = ff_codec_get_id(ff_codec_aiff_tags, codec->codec_tag);
        size -= 4;
    }

    if (version != AIFF_C_VERSION1 || codec->codec_id == AV_CODEC_ID_PCM_S16BE) {
        codec->codec_id = aiff_codec_get_id(codec->bits_per_coded_sample);
        codec->bits_per_coded_sample = av_get_bits_per_sample(codec->codec_id);
        aiff->block_duration = 1;
    } else {
        switch (codec->codec_id) {
        case AV_CODEC_ID_PCM_F32BE:
        case AV_CODEC_ID_PCM_F64BE:
        case AV_CODEC_ID_PCM_S16LE:
        case AV_CODEC_ID_PCM_ALAW:
        case AV_CODEC_ID_PCM_MULAW:
            aiff->block_duration = 1;
            break;
        case AV_CODEC_ID_ADPCM_IMA_QT:
            codec->block_align = 34*codec->channels;
            break;
        case AV_CODEC_ID_MACE3:
            codec->block_align = 2*codec->channels;
            break;
        case AV_CODEC_ID_MACE6:
            codec->block_align = 1*codec->channels;
            break;
        case AV_CODEC_ID_GSM:
            codec->block_align = 33;
            break;
        default:
            aiff->block_duration = 1;
            break;
        }
        if (codec->block_align > 0)
            aiff->block_duration = av_get_audio_frame_duration(codec,
                                                               codec->block_align);
    }

    /* Block align needs to be computed in all cases, as the definition
     * is specific to applications -> here we use the WAVE format definition */
    if (!codec->block_align)
        codec->block_align = (av_get_bits_per_sample(codec->codec_id) * codec->channels) >> 3;

    if (aiff->block_duration) {
        codec->bit_rate = codec->sample_rate * (codec->block_align << 3) /
                          aiff->block_duration;
    }

    /* Chunk is over */
    if (size)
        avio_skip(pb, size);

    return num_frames;
}