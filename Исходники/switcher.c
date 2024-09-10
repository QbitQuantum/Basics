/*****************************************************************************
 * VideoGetBuffer: Build an alternate video buffer
 *****************************************************************************/
static block_t *VideoGetBuffer( sout_stream_t *p_stream, sout_stream_id_t *id,
                                block_t *p_buffer )
{
    sout_stream_sys_t *p_sys = p_stream->p_sys;
    int i_out;
    block_t *p_out;

    id->p_frame->quality = p_sys->i_qscale * powf(2.0, FF_LAMBDA_SHIFT + 7.0)
                            / 139.0;
    id->p_frame->interlaced_frame = 0;
    id->p_frame->top_field_first = 1;
    id->p_frame->pts = p_buffer->i_dts;

    if ( id->i_nb_pred >= p_sys->i_gop )
    {
        id->p_frame->pict_type = AV_PICTURE_TYPE_I;
#if 0
        id->p_frame->me_threshold = 0;
        id->p_frame->mb_threshold = 0;
#endif
        id->i_nb_pred = 0;
    }
    else
    {
        id->p_frame->pict_type = AV_PICTURE_TYPE_P;
#if 0
        if ( id->p_frame->mb_type != NULL )
        {
            id->p_frame->me_threshold = MAX_THRESHOLD;
            id->p_frame->mb_threshold = MAX_THRESHOLD;
        }
#endif
        id->i_nb_pred++;
    }

    i_out = avcodec_encode_video( id->ff_enc_c, id->p_buffer_out,
                                  id->ff_enc_c->width * id->ff_enc_c->height * 3,
                                  id->p_frame );

    if ( i_out <= 0 )
        return NULL;

#if 0
    if ( id->p_frame->mb_type == NULL
          && id->ff_enc_c->coded_frame->pict_type != AV_PICTURE_TYPE_I )
    {
        int mb_width = (id->ff_enc_c->width + 15) / 16;
        int mb_height = (id->ff_enc_c->height + 15) / 16;
        int h_chroma_shift, v_chroma_shift;
        int i;

        avcodec_get_chroma_sub_sample( id->ff_enc_c->pix_fmt, &h_chroma_shift,
                                       &v_chroma_shift );

        id->p_frame->motion_subsample_log2
            = id->ff_enc_c->coded_frame->motion_subsample_log2;
        id->p_frame->mb_type = malloc( ((mb_width + 1) * (mb_height + 1) + 1)
                                    * sizeof(uint32_t) );
        memcpy( id->p_frame->mb_type, id->ff_enc_c->coded_frame->mb_type,
                    (mb_width + 1) * mb_height * sizeof(id->p_frame->mb_type[0]));

        for ( i = 0; i < 2; i++ )
        {
            int stride = ((16 * mb_width )
                    >> id->ff_enc_c->coded_frame->motion_subsample_log2) + 1;
            int height = ((16 * mb_height)
                    >> id->ff_enc_c->coded_frame->motion_subsample_log2);
            int b8_stride = mb_width * 2 + 1;

            if ( id->ff_enc_c->coded_frame->motion_val[i] )
            {
                id->p_frame->motion_val[i] = malloc( 2 * stride * height
                                                * sizeof(int16_t) );
                memcpy( id->p_frame->motion_val[i],
                            id->ff_enc_c->coded_frame->motion_val[i],
                            2 * stride * height * sizeof(int16_t) );
            }
            if ( id->ff_enc_c->coded_frame->ref_index[i] )
            {
                id->p_frame->ref_index[i] = malloc( b8_stride * 2 * mb_height
                                               * sizeof(int8_t) );
                memcpy( id->p_frame->ref_index[i],
                            id->ff_enc_c->coded_frame->ref_index[i],
                            b8_stride * 2 * mb_height * sizeof(int8_t));
            }
        }
    }