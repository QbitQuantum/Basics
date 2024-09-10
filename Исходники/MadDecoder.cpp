    int64 MadDecoder::getDurationMs(unsigned char* buffer, size_t bufferSize)
    {
        struct mad_stream madStream;
        struct mad_frame  madFrame;
        struct mad_header madHeader;
        mad_timer_t  time = mad_timer_zero;

        bool depadded = false;
        bool vbr = false;
        size_t tagsize = 0;
        size_t consumed = 0;
        size_t numFrames = 0;
        size_t initialBitrate = 0;


        mad_stream_init(&madStream);
        mad_header_init(&madHeader);
        mad_frame_init(&madFrame);

        do  // Read data from the MP3 file 
        {
            int padding = 0;
            size_t leftover = madStream.bufend - madStream.next_frame;
            memcpy(buffer, madStream.this_frame, leftover);

            int bytesRead = fread(buffer + leftover, (size_t)1, bufferSize - leftover, handle_);
            if (bytesRead <= 0) {
                break;
            }
            for (; !depadded && padding < bytesRead && !buffer[padding]; ++padding);
            depadded = true;
            mad_stream_buffer(&madStream, buffer + padding, leftover + bytesRead - padding);

            while (true)   // decode frame headers 
            {
                madStream.error = MAD_ERROR_NONE;
                if (mad_header_decode(&madHeader, &madStream) == -1)
                {
                    if (madStream.error == MAD_ERROR_BUFLEN)     // Normal behaviour; get some more data from the file
                        break;
                    if (MAD_RECOVERABLE(madStream.error) == 0)
                        break;
                    if (madStream.error == MAD_ERROR_LOSTSYNC)
                    {
                        unsigned available = (madStream.bufend - madStream.this_frame);
                        tagsize = getId3TagSize(madStream.this_frame, (size_t)available);

                        if (tagsize)    // It's some ID3 tags, so just skip 
                        {
                            if (tagsize >= available) {
                                _fseeki64(handle_, (int64)(tagsize - available), SEEK_CUR);
                                depadded = false;
                            }
                            mad_stream_skip(&madStream, std::min(tagsize, available));
                        }
                    }
                    continue; // not an audio frame
                }

                mad_timer_add(&time, madHeader.duration);
                consumed += madStream.next_frame - madStream.this_frame;

                if (numFrames == 0) {
                    initialBitrate = madHeader.bitrate;

                    // Get the precise frame count from the XING header if present 
                    madFrame.header = madHeader;
                    if (mad_frame_decode(&madFrame, &madStream) == -1)
                    {
                        if (MAD_RECOVERABLE(madStream.error) == 0) {
                            break;
                        }
                    }
                    if ((numFrames = xingFrames(madStream.anc_ptr, madStream.anc_bitlen)))
                    {
                        mad_timer_multiply(&time, (signed long)numFrames);
                        break;
                    }
                }
                else {
                    vbr |= madHeader.bitrate != initialBitrate;
                }

                // If not VBR, we can time just a few frames then extrapolate (not exact!)
                if (++numFrames == 25 && !vbr)
                {
                    struct stat st;
                    fstat(fileno(handle_), &st);
                    timerMultiply(&time, (double)(st.st_size - tagsize) / consumed);
                    break;
                }
            }   // while(true)
        } while (madStream.error == MAD_ERROR_BUFLEN);

        mad_frame_finish(&madFrame);
        mad_header_finish(&madHeader);
        mad_stream_finish(&madStream);
        rewind(handle_);

        return mad_timer_count(time, MAD_UNITS_MILLISECONDS);
    }