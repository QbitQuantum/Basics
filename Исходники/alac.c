/* this is called for each file to process */
enum codec_status codec_run(void)
{
    size_t n;
    demux_res_t demux_res;
    stream_t input_stream;
    uint32_t samplesdone;
    uint32_t elapsedtime = 0;
    int samplesdecoded;
    unsigned int i;
    unsigned char* buffer;
    alac_file alac;
    intptr_t param;

    /* Clean and initialize decoder structures */
    memset(&demux_res , 0, sizeof(demux_res));
    if (codec_init()) {
        LOGF("ALAC: Error initialising codec\n");
        return CODEC_ERROR;
    }

    ci->configure(DSP_SET_FREQUENCY, ci->id3->frequency);
    codec_set_replaygain(ci->id3);

    ci->seek_buffer(0);

    stream_create(&input_stream,ci);

    /* Read from ci->id3->offset before calling qtmovie_read. */
    samplesdone = (uint32_t)(((uint64_t)(ci->id3->offset) * ci->id3->frequency) /  
                  (ci->id3->bitrate*128));
  
    /* if qtmovie_read returns successfully, the stream is up to
     * the movie data, which can be used directly by the decoder */
    if (!qtmovie_read(&input_stream, &demux_res)) {
        LOGF("ALAC: Error initialising file\n");
        return CODEC_ERROR;
    }

    /* initialise the sound converter */
    alac_set_info(&alac, demux_res.codecdata);
  
    /* Set i for first frame, seek to desired sample position for resuming. */
    i=0;
    if (samplesdone > 0) {
        if (m4a_seek(&demux_res, &input_stream, samplesdone,
                      &samplesdone, (int*) &i)) {
            elapsedtime = (samplesdone * 10) / (ci->id3->frequency / 100);
            ci->set_elapsed(elapsedtime);
        } else {
            samplesdone = 0;
        }
    }

    ci->set_elapsed(elapsedtime);

    /* The main decoding loop */
    while (i < demux_res.num_sample_byte_sizes) {
        enum codec_command_action action = ci->get_command(&param);

        if (action == CODEC_ACTION_HALT)
            break;

        /* Request the required number of bytes from the input buffer */
        buffer=ci->request_buffer(&n, ALAC_BYTE_BUFFER_SIZE);

        /* Deal with any pending seek requests */
        if (action == CODEC_ACTION_SEEK_TIME) {
            if (m4a_seek(&demux_res, &input_stream,
                         (param/10) * (ci->id3->frequency/100),
                         &samplesdone, (int *)&i)) {
                elapsedtime=(samplesdone*10)/(ci->id3->frequency/100);
            }
            ci->set_elapsed(elapsedtime);
            ci->seek_complete();
        }

        /* Request the required number of bytes from the input buffer */
        buffer=ci->request_buffer(&n, ALAC_BYTE_BUFFER_SIZE);

        /* Decode one block - returned samples will be host-endian */
        samplesdecoded=alac_decode_frame(&alac, buffer, outputbuffer, ci->yield);
        ci->yield();

        /* Advance codec buffer by amount of consumed bytes */
        ci->advance_buffer(alac.bytes_consumed);

        /* Output the audio */
        ci->pcmbuf_insert(outputbuffer[0], outputbuffer[1], samplesdecoded);

        /* Update the elapsed-time indicator */
        samplesdone+=samplesdecoded;
        elapsedtime=(samplesdone*10)/(ci->id3->frequency/100);
        ci->set_elapsed(elapsedtime);

        i++;
    }

    LOGF("ALAC: Decoded %lu samples\n",(unsigned long)samplesdone);
    return CODEC_OK;
}