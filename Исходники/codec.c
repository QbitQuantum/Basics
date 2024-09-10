/*
 * Output handler
 */
static void opng_write_data(png_structp png_ptr, png_bytep data, size_t length)
{
    struct opng_codec_context * context = (struct opng_codec_context *)png_get_io_ptr(png_ptr);
    struct opng_encoding_stats * stats = context->stats;
    FILE * stream = context->stream;

    unsigned io_state = png_get_io_state(png_ptr);
    unsigned io_state_loc = io_state & PNG_IO_MASK_LOC;
    OPNG_ASSERT((io_state & PNG_IO_WRITING) && (io_state_loc != 0), "Incorrect info in png_ptr->io_state");

    /* Handle the optipng-specific events. */
    if (io_state_loc == PNG_IO_CHUNK_HDR)
    {
        OPNG_ASSERT(length == 8, "Writing chunk header, expecting 8 bytes");
        png_bytep chunk_sig = data + 4;
        context->crt_chunk_is_allowed = opng_allow_chunk(context, chunk_sig);
        if (memcmp(chunk_sig, opng_sig_IDAT, 4) == 0)
        {
            context->crt_chunk_is_idat = 1;
            stats->idat_size += png_get_uint_32(data);
        }
        else  /* not IDAT */
        {
            context->crt_chunk_is_idat = 0;
        }
    }
    if (context->no_write) {
        return;
    }

    /* Continue only if the current chunk type is allowed. */
    if (io_state_loc != PNG_IO_SIGNATURE && !context->crt_chunk_is_allowed)
        return;

    /* Here comes an elaborate way of writing the data, in which all IDATs
     * are joined into a single chunk.
     * Normally, the user-supplied I/O routines are not so complicated.
     */
    switch (io_state_loc)
    {
    case PNG_IO_CHUNK_HDR:
        if (context->crt_chunk_is_idat)
        {
            if (context->crt_idat_offset == 0)
            {
                /* This is the header of the first IDAT. */
                context->crt_idat_offset = ftell(stream);
                context->crt_idat_size = length;
                png_save_uint_32(data, (png_uint_32)context->crt_idat_size);
                /* Start computing the CRC of the final IDAT. */
                context->crt_idat_crc = crc32(0, opng_sig_IDAT, 4);
            }
            else
            {
                /* This is not the first IDAT. Do not write its header. */
                return;
            }
        }
        else
        {
            if (context->crt_idat_offset != 0)
            {
                png_byte buf[4];
                /* This is the header of the first chunk after IDAT.
                 * Finalize IDAT before resuming the normal operation.
                 */
                png_save_uint_32(buf, context->crt_idat_crc);
                fwrite(buf, 1, 4, stream);
                if (stats->idat_size != context->crt_idat_size)
                {
                    /* The IDAT size, unknown at the start of encoding,
                     * has not been guessed correctly.
                     * It must be updated in a non-streamable way.
                     */
                    png_save_uint_32(buf, (png_uint_32)stats->idat_size);
                    fpos_t pos;
                    if (fgetpos(stream, &pos) != 0 || fflush(stream) != 0 || (fseek(stream, context->crt_idat_offset, SEEK_SET) != 0) ||
                            (fwrite(buf, 1, 4, stream)!=4) || (fflush(stream) != 0) || (fsetpos(stream, &pos) != 0)) {
                        io_state = 0;
                    }
                }
                if (io_state == 0)
                    png_error(png_ptr, "Can't finalize IDAT");
                context->crt_idat_offset = 0;
            }
        }
        break;
    case PNG_IO_CHUNK_DATA:
        if (context->crt_chunk_is_idat)
            context->crt_idat_crc = crc32(context->crt_idat_crc, data, length);
        break;
    case PNG_IO_CHUNK_CRC:
        if (context->crt_chunk_is_idat)
            return;  /* defer writing until the first non-IDAT occurs */
        break;
    }

    /* Write the data. */
    if (fwrite(data, 1, length, stream) != length)
        png_error(png_ptr, "Can't write file");
}