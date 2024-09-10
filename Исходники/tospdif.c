/*****************************************************************************
 * DoWork: convert a buffer
 *****************************************************************************/
static block_t *DoWork( filter_t * p_filter, block_t *p_in_buf )
{
    size_t i_length = p_in_buf->i_buffer;
    uint8_t * p_in = p_in_buf->p_buffer;
    block_t *p_out_buf = NULL;

    uint16_t i_data_type = get_data_type( p_filter, p_in_buf );
    if( i_data_type == 0 || ( i_length + 8 ) > AOUT_SPDIF_SIZE )
        goto out;

    size_t i_out_length = p_in_buf->i_nb_samples * 4;
    p_out_buf = block_Alloc( i_out_length );
    if( !p_out_buf )
        goto out;
    uint8_t *p_out = p_out_buf->p_buffer;

    /* Copy the S/PDIF headers. */
    void (*write16)(void *, uint16_t) =
        ( p_filter->fmt_out.audio.i_format == VLC_CODEC_SPDIFB )
        ? SetWBE : SetWLE;

    write16( &p_out[0], 0xf872 ); /* syncword 1 */
    write16( &p_out[2], 0x4e1f ); /* syncword 2 */
    write16( &p_out[4], i_data_type ); /* data type */
    write16( &p_out[6], i_length * 8 ); /* length in bits */

    bool b_input_big_endian = is_big_endian( p_filter, p_in_buf );
    bool b_output_big_endian =
        p_filter->fmt_out.audio.i_format == VLC_CODEC_SPDIFB;

    if( b_input_big_endian != b_output_big_endian )
    {
        swab( p_in, p_out + 8, i_length & ~1 );

        /* If i_length is odd, we have to adjust swapping a bit... */
        if( i_length & 1 && ( i_length + 9 ) <= i_out_length )
        {
            p_out[8 + i_length - 1] = 0;
            p_out[8 + i_length] = p_in[i_length-1];
            i_length++;
        }
    } else
        memcpy( p_out + 8, p_in, i_length );

    if( 8 + i_length < i_out_length ) /* padding */
        memset( p_out + 8 + i_length, 0, i_out_length - i_length - 8 );

    p_out_buf->i_dts = p_in_buf->i_dts;
    p_out_buf->i_pts = p_in_buf->i_pts;
    p_out_buf->i_nb_samples = p_in_buf->i_nb_samples;
    p_out_buf->i_buffer = i_out_length;
out:
    block_Release( p_in_buf );
    return p_out_buf;
}