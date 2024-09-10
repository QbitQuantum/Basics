static void BdExtract( block_t *p_aout_buffer, block_t *p_block,
                       unsigned i_frame_length,
                       unsigned i_channels, unsigned i_channels_padding,
                       unsigned i_bits )
{
    if( i_channels_padding > 0 )
    {
        uint8_t *p_src = p_block->p_buffer;
        uint8_t *p_dst = p_aout_buffer->p_buffer;
        int dst_inc = ((i_bits == 16) ? 2 : 4) * i_channels;

        while( i_frame_length > 0 )
        {
#ifdef WORDS_BIGENDIAN
            memcpy( p_dst, p_src, i_channels * i_bits / 8 );
#else
            if (i_bits == 16) {
                swab( (char *)p_dst, (char *)p_src, (i_channels + i_channels_padding) * i_bits / 8 );			// sunqueen modify
            } else {
                p_dst[0] = 0;
                p_dst[1] = p_src[2];
                p_dst[2] = p_src[1];
                p_dst[3] = p_src[0];
            }
#endif
            p_src += (i_channels + i_channels_padding) * i_bits / 8;
            p_dst += dst_inc;
            i_frame_length--;
        }
    }
    else
    {
#ifdef WORDS_BIGENDIAN
        memcpy( p_aout_buffer->p_buffer, p_block->p_buffer, p_block->i_buffer );
#else
        swab( (char *)p_block->p_buffer, (char *)p_aout_buffer->p_buffer, p_block->i_buffer );			// sunqueen modify
#endif
    }
}