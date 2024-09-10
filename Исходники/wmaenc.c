static int encode_block(WMACodecContext *s, float (*src_coefs)[BLOCK_MAX_SIZE],
                        int total_gain)
{
    int v, bsize, ch, coef_nb_bits, parse_exponents;
    float mdct_norm;
    int nb_coefs[MAX_CHANNELS];
    static const int fixed_exp[25] = {
        20, 20, 20, 20, 20,
        20, 20, 20, 20, 20,
        20, 20, 20, 20, 20,
        20, 20, 20, 20, 20,
        20, 20, 20, 20, 20
    };

    // FIXME remove duplication relative to decoder
    if (s->use_variable_block_len) {
        av_assert0(0); // FIXME not implemented
    } else {
        /* fixed block len */
        s->next_block_len_bits = s->frame_len_bits;
        s->prev_block_len_bits = s->frame_len_bits;
        s->block_len_bits      = s->frame_len_bits;
    }

    s->block_len = 1 << s->block_len_bits;
//     av_assert0((s->block_pos + s->block_len) <= s->frame_len);
    bsize = s->frame_len_bits - s->block_len_bits;

    // FIXME factor
    v = s->coefs_end[bsize] - s->coefs_start;
    for (ch = 0; ch < s->avctx->channels; ch++)
        nb_coefs[ch] = v;
    {
        int n4 = s->block_len / 2;
        mdct_norm = 1.0 / (float) n4;
        if (s->version == 1)
            mdct_norm *= sqrt(n4);
    }

    if (s->avctx->channels == 2)
        put_bits(&s->pb, 1, !!s->ms_stereo);

    for (ch = 0; ch < s->avctx->channels; ch++) {
        // FIXME only set channel_coded when needed, instead of always
        s->channel_coded[ch] = 1;
        if (s->channel_coded[ch])
            init_exp(s, ch, fixed_exp);
    }

    for (ch = 0; ch < s->avctx->channels; ch++) {
        if (s->channel_coded[ch]) {
            WMACoef *coefs1;
            float *coefs, *exponents, mult;
            int i, n;

            coefs1    = s->coefs1[ch];
            exponents = s->exponents[ch];
            mult      = ff_exp10(total_gain * 0.05) / s->max_exponent[ch];
            mult     *= mdct_norm;
            coefs     = src_coefs[ch];
            if (s->use_noise_coding && 0) {
                av_assert0(0); // FIXME not implemented
            } else {
                coefs += s->coefs_start;
                n      = nb_coefs[ch];
                for (i = 0; i < n; i++) {
                    double t = *coefs++ / (exponents[i] * mult);
                    if (t < -32768 || t > 32767)
                        return -1;

                    coefs1[i] = lrint(t);
                }
            }
        }
    }

    v = 0;
    for (ch = 0; ch < s->avctx->channels; ch++) {
        int a = s->channel_coded[ch];
        put_bits(&s->pb, 1, a);
        v |= a;
    }

    if (!v)
        return 1;

    for (v = total_gain - 1; v >= 127; v -= 127)
        put_bits(&s->pb, 7, 127);
    put_bits(&s->pb, 7, v);

    coef_nb_bits = ff_wma_total_gain_to_bits(total_gain);

    if (s->use_noise_coding) {
        for (ch = 0; ch < s->avctx->channels; ch++) {
            if (s->channel_coded[ch]) {
                int i, n;
                n = s->exponent_high_sizes[bsize];
                for (i = 0; i < n; i++) {
                    put_bits(&s->pb, 1, s->high_band_coded[ch][i] = 0);
                    if (0)
                        nb_coefs[ch] -= s->exponent_high_bands[bsize][i];
                }
            }
        }
    }

    parse_exponents = 1;
    if (s->block_len_bits != s->frame_len_bits)
        put_bits(&s->pb, 1, parse_exponents);

    if (parse_exponents) {
        for (ch = 0; ch < s->avctx->channels; ch++) {
            if (s->channel_coded[ch]) {
                if (s->use_exp_vlc) {
                    encode_exp_vlc(s, ch, fixed_exp);
                } else {
                    av_assert0(0); // FIXME not implemented
//                    encode_exp_lsp(s, ch);
                }
            }
        }
    } else
        av_assert0(0); // FIXME not implemented

    for (ch = 0; ch < s->avctx->channels; ch++) {
        if (s->channel_coded[ch]) {
            int run, tindex;
            WMACoef *ptr, *eptr;
            tindex = (ch == 1 && s->ms_stereo);
            ptr    = &s->coefs1[ch][0];
            eptr   = ptr + nb_coefs[ch];

            run = 0;
            for (; ptr < eptr; ptr++) {
                if (*ptr) {
                    int level     = *ptr;
                    int abs_level = FFABS(level);
                    int code      = 0;
                    if (abs_level <= s->coef_vlcs[tindex]->max_level)
                        if (run < s->coef_vlcs[tindex]->levels[abs_level - 1])
                            code = run + s->int_table[tindex][abs_level - 1];

                    av_assert2(code < s->coef_vlcs[tindex]->n);
                    put_bits(&s->pb, s->coef_vlcs[tindex]->huffbits[code],
                             s->coef_vlcs[tindex]->huffcodes[code]);

                    if (code == 0) {
                        if (1 << coef_nb_bits <= abs_level)
                            return -1;

                        put_bits(&s->pb, coef_nb_bits, abs_level);
                        put_bits(&s->pb, s->frame_len_bits, run);
                    }
                    // FIXME the sign is flipped somewhere
                    put_bits(&s->pb, 1, level < 0);
                    run = 0;
                } else
                    run++;
            }
            if (run)
                put_bits(&s->pb, s->coef_vlcs[tindex]->huffbits[1],
                         s->coef_vlcs[tindex]->huffcodes[1]);
        }
        if (s->version == 1 && s->avctx->channels >= 2)
            avpriv_align_put_bits(&s->pb);
    }
    return 0;
}