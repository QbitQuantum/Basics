static int make_frame_planar_yuv_stacked
(
    lw_video_output_handler_t *vohp,
    int                        height,
    AVFrame                   *av_frame,
    PVideoFrame               &as_frame
)
{
    as_picture_t dst_picture = { { { NULL } } };
    as_picture_t src_picture = { { { NULL } } };
    as_assign_planar_yuv( as_frame, &dst_picture );
    lw_video_scaler_handler_t *vshp = &vohp->scaler;
    as_video_output_handler_t *as_vohp = (as_video_output_handler_t *)vohp->private_handler;
    if( vshp->input_pixel_format == vshp->output_pixel_format )
        for( int i = 0; i < 3; i++ )
        {
            src_picture.data    [i] = av_frame->data    [i];
            src_picture.linesize[i] = av_frame->linesize[i];
        }
    else
    {
        if( convert_av_pixel_format( vshp->sws_ctx, height, av_frame, &as_vohp->scaled ) < 0 )
            return -1;
        src_picture = as_vohp->scaled;
    }
    for( int i = 0; i < 3; i++ )
    {
        const int src_height = height >> (i ? as_vohp->sub_height : 0);
        const int width      = vshp->input_width >> (i ? as_vohp->sub_width : 0);
        const int width16    = sse2_available > 0 ? (width & ~15) : 0;
        const int width32    = avx2_available > 0 ? (width & ~31) : 0;
        const int lsb_offset = src_height * dst_picture.linesize[i];
        for( int j = 0; j < src_height; j++ )
        {
            /* Here, if available, use SIMD instructions.
             * Note: There is assumption that the address of a given data can be divided by 32 or 16.
             *       The destination is always 32 byte alignment unless AviSynth legacy alignment is used.
             *       The source is not always 32 or 16 byte alignment if the frame buffer is from libavcodec directly. */
            static const uint8_t LW_ALIGN(32) sp16[32] =
                {
                    /* saturation protector
                     * For setting all upper 8 bits to zero so that saturation won't make sense. */
                    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00 ,0xFF, 0x00, 0xFF, 0x00,
                    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00 ,0xFF, 0x00, 0xFF, 0x00
                };
                  uint8_t *dst     = dst_picture.data[i] + j * dst_picture.linesize[i];     /* MSB: dst +     k,     LSB: dst +     k + lsb_offset */
            const uint8_t *src     = src_picture.data[i] + j * src_picture.linesize[i];     /* MSB: src + 2 * k + 1, LSB: src + 2 * k */
            const int     _width16 = ((intptr_t)src & 15) == 0 ? width16 : 0;               /* Don't use SSE2 instructions if set to 0. */
            const int     _width32 = ((intptr_t)src & 31) == 0 ? width32 : 0;               /* Don't use AVX(2) instructions if set to 0. */
#if VC_HAS_AVX2
            /* AVX, AVX2 */
            for( int k = 0; k < _width32; k += 32 )
            {
                __m256i ymm0 = _mm256_load_si256( (__m256i *)(src + 2 * k     ) );
                __m256i ymm1 = _mm256_load_si256( (__m256i *)(src + 2 * k + 32) );
                __m256i mask = _mm256_load_si256( (__m256i *)sp16 );
                __m256i ymm2 = _mm256_packus_epi16( _mm256_and_si256 ( ymm0, mask ), _mm256_and_si256 ( ymm1, mask ) );
                __m256i ymm3 = _mm256_packus_epi16( _mm256_srli_epi16( ymm0,    8 ), _mm256_srli_epi16( ymm1,    8 ) );
                _mm256_store_si256( (__m256i *)(dst + k + lsb_offset), _mm256_permute4x64_epi64( ymm2, _MM_SHUFFLE( 3, 1, 2, 0 ) ) );
                _mm256_store_si256( (__m256i *)(dst + k             ), _mm256_permute4x64_epi64( ymm3, _MM_SHUFFLE( 3, 1, 2, 0 ) ) );
            }
#endif
            /* SSE2 */
            for( int k = _width32; k < _width16; k += 16 )
            {
                __m128i xmm0 = _mm_load_si128( (__m128i *)(src + 2 * k     ) );
                __m128i xmm1 = _mm_load_si128( (__m128i *)(src + 2 * k + 16) );
                __m128i mask = _mm_load_si128( (__m128i *)sp16 );
                _mm_store_si128( (__m128i *)(dst + k + lsb_offset), _mm_packus_epi16( _mm_and_si128 ( xmm0, mask ), _mm_and_si128 ( xmm1, mask ) ) );
                _mm_store_si128( (__m128i *)(dst + k             ), _mm_packus_epi16( _mm_srli_epi16( xmm0,    8 ), _mm_srli_epi16( xmm1,    8 ) ) );
            }
            for( int k = _width16; k < width; k++ )
            {
                *(dst + k + lsb_offset) = *(src + 2 * k    );
                *(dst + k             ) = *(src + 2 * k + 1);
            }
        }
    }
    return 0;
}