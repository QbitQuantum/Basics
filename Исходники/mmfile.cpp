/* for now just 16bit signed values, mono channels FIXME
 * maybe use SDL_AudioConvert() for this */
int
mm_decode_audio(mm_file *mf, void *buf, int buflen)
{
    const int max_val = 32767;
    const int min_val = -32768;
    const int bytes_per_sample = 2;

    int rv = 0, samples = 0, left = 0, total = 0;
    unsigned channels = 0;

    assert(mf);

    if (-1 == mm_audio_info(mf, &channels, NULL)) {
        return -1;
    }

    if (mf->drop_packets & MEDIA_AUDIO) {
        WARNING1("requested decode but MEDIA_AUDIO is set to ignore");
        return -1;
    }

    /* convert buflen [bytes] to left [samples] */
    left = buflen;
    left = left / channels / bytes_per_sample;

    while (left > 0) {
        float **pcm;
        ogg_packet pkt;

        /* also outputs any samples left from last decoding */
        while (left > 0
               && (samples = vorbis_synthesis_pcmout(mf->audio_ctx, &pcm)) > 0) {
            int i = 0;
            unsigned ch = 0;

            samples = MIN(samples, left);

            for (i = 0; i < samples; ++i) {
                for (ch = 0; ch < channels; ++ch) {
                    // lrint is not available on MSVC
#ifdef HAVE_LRINT
                    int val = lrint(pcm[ch][i] * max_val);
#else
                    int val = (int)floor(pcm[ch][i] * max_val);
#endif

                    if (val > max_val) {
                        val = max_val;
                    }

                    if (val < min_val) {
                        val = min_val;
                    }

                    *((int16_t *) buf + (total + i) * channels + ch) = val;
                }
            }

            total += samples;
            left -= samples;
            vorbis_synthesis_read(mf->audio_ctx, samples);

        }

        /* grab new packets if we need more */
        for (;;) {
            rv = get_packet(mf, &pkt, MEDIA_AUDIO);

            if (rv < 0) {
                return rv;
            } else if (rv == 0) {
                return total * channels * bytes_per_sample;
            }

            /* have packet, synthesize */
            if (vorbis_synthesis(mf->audio_blk, &pkt) == 0) {
                vorbis_synthesis_blockin(mf->audio_ctx, mf->audio_blk);
                break;
            } else {
                WARNING1("packet does not contain a valid vorbis frame");
                /* get next packet */
            }
        }
    }

    return total * channels * bytes_per_sample;
}