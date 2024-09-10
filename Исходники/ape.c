/* this is the codec entry point */
enum codec_status codec_main(void)
{
    struct ape_ctx_t ape_ctx;
    uint32_t samplesdone;
    uint32_t elapsedtime;
    size_t bytesleft;
    int retval;

    uint32_t currentframe;
    uint32_t newfilepos;
    uint32_t samplestoskip;
    int nblocks;
    int bytesconsumed;
    unsigned char* inbuffer;
    uint32_t blockstodecode;
    int res;
    int firstbyte;
    size_t resume_offset;

    /* Generic codec initialisation */
    ci->configure(DSP_SET_SAMPLE_DEPTH, APE_OUTPUT_DEPTH-1);

next_track:
    retval = CODEC_OK;

    if (codec_init()) {
        LOGF("APE: Error initialising codec\n");
        retval = CODEC_ERROR;
        goto exit;
    }

    if (codec_wait_taginfo() != 0)
        goto done;

    /* Remember the resume position - when the codec is opened, the
       playback engine will reset it. */
    resume_offset = ci->id3->offset;

    inbuffer = ci->request_buffer(&bytesleft, INPUT_CHUNKSIZE);

    /* Read the file headers to populate the ape_ctx struct */
    if (ape_parseheaderbuf(inbuffer,&ape_ctx) < 0) {
        LOGF("APE: Error reading header\n");
        retval = CODEC_ERROR;
        goto exit;
    }

    /* Initialise the seektable for this file */
    ape_ctx.seektable = seektablebuf;
    ape_ctx.numseekpoints = MIN(MAX_SEEKPOINTS,ape_ctx.numseekpoints);

    ci->advance_buffer(ape_ctx.seektablefilepos);

    /* The seektable may be bigger than the guard buffer (32KB), so we
       do a read() */
    ci->read_filebuf(ape_ctx.seektable, ape_ctx.numseekpoints * sizeof(uint32_t));

#ifdef ROCKBOX_BIG_ENDIAN
    /* Byte-swap the little-endian seekpoints */
    {
        uint32_t i;

        for(i = 0; i < ape_ctx.numseekpoints; i++)
            ape_ctx.seektable[i] = swap32(ape_ctx.seektable[i]);
    }
#endif

    /* Now advance the file position to the first frame */
    ci->advance_buffer(ape_ctx.firstframe - 
                       (ape_ctx.seektablefilepos +
                        ape_ctx.numseekpoints * sizeof(uint32_t)));

    ci->configure(DSP_SWITCH_FREQUENCY, ape_ctx.samplerate);
    ci->configure(DSP_SET_STEREO_MODE, ape_ctx.channels == 1 ?
                  STEREO_MONO : STEREO_NONINTERLEAVED);
    codec_set_replaygain(ci->id3);

    /* The main decoding loop */

    if (resume_offset) {
        /* The resume offset is a value in bytes - we need to
           turn it into a frame number and samplestoskip value */

        ape_resume(&ape_ctx, resume_offset, 
                   &currentframe, &samplesdone, &samplestoskip, &firstbyte);
    } else {
        currentframe = 0;
        samplesdone = 0;
        samplestoskip = 0;
        firstbyte = 3;  /* Take account of the little-endian 32-bit byte ordering */
    }

    /* Initialise the buffer */
    inbuffer = ci->request_buffer(&bytesleft, INPUT_CHUNKSIZE);

    /* The main decoding loop - we decode the frames a small chunk at a time */
    while (currentframe < ape_ctx.totalframes)
    {
frame_start:
        /* Calculate how many blocks there are in this frame */
        if (currentframe == (ape_ctx.totalframes - 1))
            nblocks = ape_ctx.finalframeblocks;
        else
            nblocks = ape_ctx.blocksperframe;

        ape_ctx.currentframeblocks = nblocks;

        /* Initialise the frame decoder */
        init_frame_decoder(&ape_ctx, inbuffer, &firstbyte, &bytesconsumed);

        ci->advance_buffer(bytesconsumed);
        inbuffer = ci->request_buffer(&bytesleft, INPUT_CHUNKSIZE);

        /* Decode the frame a chunk at a time */
        while (nblocks > 0)
        {
            ci->yield();
            if (ci->stop_codec || ci->new_track) {
                goto done;
            }

            /* Deal with any pending seek requests */
            if (ci->seek_time) 
            {
                if (ape_calc_seekpos(&ape_ctx,
                    ((ci->seek_time-1)/10) * (ci->id3->frequency/100),
                    &currentframe,
                    &newfilepos,
                    &samplestoskip))
                {
                    samplesdone = currentframe * ape_ctx.blocksperframe;

                    /* APE's bytestream is weird... */
                    firstbyte = 3 - (newfilepos & 3);
                    newfilepos &= ~3;

                    ci->seek_buffer(newfilepos);
                    inbuffer = ci->request_buffer(&bytesleft, INPUT_CHUNKSIZE);

                    ci->seek_complete();
                    goto frame_start;  /* Sorry... */
                }
                ci->seek_complete();
            }

            blockstodecode = MIN(BLOCKS_PER_LOOP, nblocks);

            if ((res = decode_chunk(&ape_ctx, inbuffer, &firstbyte,
                                    &bytesconsumed,
                                    decoded0, decoded1,
                                    blockstodecode)) < 0)
            {
                /* Frame decoding error, abort */
                LOGF("APE: Frame %lu, error %d\n",(unsigned long)currentframe,res);
                retval = CODEC_ERROR;
                goto done;
            }

            ci->yield();

            if (samplestoskip > 0) {
                if (samplestoskip < blockstodecode) {
                    ci->pcmbuf_insert(decoded0 + samplestoskip, 
                                      decoded1 + samplestoskip, 
                                      blockstodecode - samplestoskip);
                    samplestoskip = 0;
                } else {
                    samplestoskip -= blockstodecode;
                }
            } else {
                ci->pcmbuf_insert(decoded0, decoded1, blockstodecode);
            }
        
            samplesdone += blockstodecode;

            if (!samplestoskip) {
                /* Update the elapsed-time indicator */
                elapsedtime = (samplesdone*10)/(ape_ctx.samplerate/100);
                ci->set_elapsed(elapsedtime);
            }

            ci->advance_buffer(bytesconsumed);
            inbuffer = ci->request_buffer(&bytesleft, INPUT_CHUNKSIZE);

            /* Decrement the block count */
            nblocks -= blockstodecode;
        }

        currentframe++;
    }

done:
    LOGF("APE: Decoded %lu samples\n",(unsigned long)samplesdone);

    if (ci->request_next_track())
        goto next_track;

exit:
    return retval;
}