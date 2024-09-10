/* this is called for each file to process */
enum codec_status codec_run(void)
{
    int error = CODEC_ERROR;

    SpeexBits bits;
    int eof = 0;
    spx_ogg_sync_state oy;
    spx_ogg_page og;
    spx_ogg_packet op;
    spx_ogg_stream_state os;
    spx_int64_t page_granule = 0;
    spx_int64_t cur_granule = 0;
    int enh_enabled = 1;
    int nframes = 2;
    int eos = 0;
    SpeexStereoState *stereo;
    int channels = -1;
    int samplerate = ci->id3->frequency;
    int extra_headers = 0;
    int stream_init = 0;
    /* rockbox: comment 'set but unused' variables
    int page_nb_packets;
    */
    int frame_size;
    int packet_count = 0;
    int lookahead;
    int headerssize = 0;
    unsigned long strtoffset = ci->id3->offset;
    void *st = NULL;
    int j = 0;
    intptr_t param;

    memset(&bits, 0, sizeof(bits));
    memset(&oy, 0, sizeof(oy));

    /* Ogg handling still uses mallocs, so reset the malloc buffer per track */
    if (codec_init()) {
        goto exit;
    }

    ci->seek_buffer(0);
    ci->set_elapsed(0);

    stereo = speex_stereo_state_init();
    spx_ogg_sync_init(&oy);
    spx_ogg_alloc_buffer(&oy,2*CHUNKSIZE);

    codec_set_replaygain(ci->id3);

    eof = 0;
    while (!eof) {
        enum codec_command_action action = ci->get_command(&param);

        if (action == CODEC_ACTION_HALT)
            break;

        /*seek (seeks to the page before the position) */
        if (action == CODEC_ACTION_SEEK_TIME) {
            if(samplerate!=0&&packet_count>1){
                LOGF("Speex seek page:%lld,%lld,%ld,%lld,%d\n",
                     ((spx_int64_t)param/1000) *
                     (spx_int64_t)samplerate,
                     page_granule, param,
                     (page_granule/samplerate)*1000, samplerate);

                speex_seek_page_granule(((spx_int64_t)param/1000) *
                                        (spx_int64_t)samplerate,
                                        page_granule, &oy, headerssize);
            }

            ci->set_elapsed(param);
            ci->seek_complete();
        }

next_page:
        /*Get the ogg buffer for writing*/
        if(get_more_data(&oy)<1){/*read error*/
            goto done;
        }

        /* Loop for all complete pages we got (most likely only one) */
        while (spx_ogg_sync_pageout(&oy, &og) == 1) {
            int packet_no;
            if (stream_init == 0) {
                spx_ogg_stream_init(&os, spx_ogg_page_serialno(&og));
                stream_init = 1;
            }

            /* Add page to the bitstream */
            spx_ogg_stream_pagein(&os, &og);

            page_granule = spx_ogg_page_granulepos(&og);
            /* page_nb_packets = spx_ogg_page_packets(&og); */

            cur_granule = page_granule;

            /* Extract all available packets */
            packet_no=0;

            while (!eos && spx_ogg_stream_packetout(&os, &op)==1){
                /* If first packet, process as Speex header */
                if (packet_count==0){
                    st = process_header(&op, enh_enabled, &frame_size,
                                         &samplerate, &nframes, &channels,
                                         stereo, &extra_headers);

                    speex_decoder_ctl(st, SPEEX_GET_LOOKAHEAD, &lookahead);
                    if (!nframes)
                        nframes=1;

                    if (!st){
                        goto done;
                    }

                    ci->configure(DSP_SET_FREQUENCY, ci->id3->frequency);
                    ci->configure(DSP_SET_SAMPLE_DEPTH, 16);
                    if (channels == 2) {
                        ci->configure(DSP_SET_STEREO_MODE, STEREO_INTERLEAVED);
                    } else if (channels == 1) {
                        ci->configure(DSP_SET_STEREO_MODE, STEREO_MONO);
                    }

                    /* Speex header in its own page, add the whole page
                       headersize */
                    headerssize += og.header_len+og.body_len;

                } else if (packet_count<=1+extra_headers){
                    /* add packet to headersize */
                    headerssize += op.bytes;

                    /* Ignore extra headers */
                } else {
                    if (packet_count <= 2+extra_headers) {
                        if (strtoffset) {
                            ci->seek_buffer(strtoffset);
                            spx_ogg_sync_reset(&oy);
                            packet_count++;
                            goto next_page;
                        }
                    }
                    packet_no++;

                    if (op.e_o_s) /* End of stream condition */
                        eos=1;

                    /* Set Speex bitstream to point to Ogg packet */
                    speex_bits_set_bit_buffer(&bits, (char *)op.packet,
                                                     op.bytes);
                    for (j = 0; j != nframes; j++){
                        int ret;

                        /* Decode frame */
                        ret = speex_decode_int(st, &bits, output);

                        if (ret == -1)
                            break;

                        if (ret == -2)
                            break;

                        if (speex_bits_remaining(&bits) < 0)
                            break;

                        if (channels == 2)
                            speex_decode_stereo_int(output, frame_size, stereo);

                        if (frame_size > 0) {
                            spx_int16_t *frame_start = output + lookahead;

                            if (channels == 2)
                                frame_start += lookahead;
                            ci->pcmbuf_insert(frame_start, NULL,
                                              frame_size - lookahead);
                            lookahead = 0;
                            /* 2 bytes/sample */
                            cur_granule += frame_size / 2;

                            ci->set_offset((long) ci->curpos);

                            ci->set_elapsed((samplerate == 0) ? 0 :
                                             cur_granule * 1000 / samplerate);
                         }
                    }
                }
                packet_count++;
            }
        }
    }

    error = CODEC_OK;
done:
    /* Clean things up for the next track */
    speex_bits_destroy(&bits);

    if (st)
        speex_decoder_destroy(st);

    if (stream_init)
       spx_ogg_stream_destroy(&os);

    spx_ogg_sync_destroy(&oy);

exit:
    return error;
}