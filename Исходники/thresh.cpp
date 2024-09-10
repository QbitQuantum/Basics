static void
thresh_16s( const Mat& _src, Mat& _dst, short thresh, short maxval, int type )
{
    int i, j;
    Size roi = _src.size();
    roi.width *= _src.channels();
    const short* src = _src.ptr<short>();
    short* dst = _dst.ptr<short>();
    size_t src_step = _src.step/sizeof(src[0]);
    size_t dst_step = _dst.step/sizeof(dst[0]);

#if CV_SSE2
    volatile bool useSIMD = checkHardwareSupport(CV_CPU_SSE);
#endif

    if( _src.isContinuous() && _dst.isContinuous() )
    {
        roi.width *= roi.height;
        roi.height = 1;
        src_step = dst_step = roi.width;
    }

#ifdef HAVE_TEGRA_OPTIMIZATION
    if (tegra::thresh_16s(_src, _dst, roi.width, roi.height, thresh, maxval, type))
        return;
#endif

#if defined(HAVE_IPP)
    CV_IPP_CHECK()
    {
        IppiSize sz = { roi.width, roi.height };
        CV_SUPPRESS_DEPRECATED_START
        switch( type )
        {
        case THRESH_TRUNC:
#ifndef HAVE_IPP_ICV_ONLY
            if (_src.data == _dst.data && ippiThreshold_GT_16s_C1IR(dst, (int)dst_step*sizeof(dst[0]), sz, thresh) >= 0)
            {
                CV_IMPL_ADD(CV_IMPL_IPP);
                return;
            }
#endif
            if (ippiThreshold_GT_16s_C1R(src, (int)src_step*sizeof(src[0]), dst, (int)dst_step*sizeof(dst[0]), sz, thresh) >= 0)
            {
                CV_IMPL_ADD(CV_IMPL_IPP);
                return;
            }
            setIppErrorStatus();
            break;
        case THRESH_TOZERO:
#ifndef HAVE_IPP_ICV_ONLY
            if (_src.data == _dst.data && ippiThreshold_LTVal_16s_C1IR(dst, (int)dst_step*sizeof(dst[0]), sz, thresh + 1, 0) >= 0)
            {
                CV_IMPL_ADD(CV_IMPL_IPP);
                return;
            }
#endif
            if (ippiThreshold_LTVal_16s_C1R(src, (int)src_step*sizeof(src[0]), dst, (int)dst_step*sizeof(dst[0]), sz, thresh+1, 0) >= 0)
            {
                CV_IMPL_ADD(CV_IMPL_IPP);
                return;
            }
            setIppErrorStatus();
            break;
        case THRESH_TOZERO_INV:
#ifndef HAVE_IPP_ICV_ONLY
            if (_src.data == _dst.data && ippiThreshold_GTVal_16s_C1IR(dst, (int)dst_step*sizeof(dst[0]), sz, thresh, 0) >= 0)
            {
                CV_IMPL_ADD(CV_IMPL_IPP);
                return;
            }
#endif
            if (ippiThreshold_GTVal_16s_C1R(src, (int)src_step*sizeof(src[0]), dst, (int)dst_step*sizeof(dst[0]), sz, thresh, 0) >= 0)
            {
                CV_IMPL_ADD(CV_IMPL_IPP);
                return;
            }
            setIppErrorStatus();
            break;
        }
        CV_SUPPRESS_DEPRECATED_END
    }
#endif

    switch( type )
    {
    case THRESH_BINARY:
        for( i = 0; i < roi.height; i++, src += src_step, dst += dst_step )
        {
            j = 0;
        #if CV_SSE2
            if( useSIMD )
            {
                __m128i thresh8 = _mm_set1_epi16(thresh), maxval8 = _mm_set1_epi16(maxval);
                for( ; j <= roi.width - 16; j += 16 )
                {
                    __m128i v0, v1;
                    v0 = _mm_loadu_si128( (const __m128i*)(src + j) );
                    v1 = _mm_loadu_si128( (const __m128i*)(src + j + 8) );
                    v0 = _mm_cmpgt_epi16( v0, thresh8 );
                    v1 = _mm_cmpgt_epi16( v1, thresh8 );
                    v0 = _mm_and_si128( v0, maxval8 );
                    v1 = _mm_and_si128( v1, maxval8 );
                    _mm_storeu_si128((__m128i*)(dst + j), v0 );
                    _mm_storeu_si128((__m128i*)(dst + j + 8), v1 );
                }
            }
        #elif CV_NEON
            int16x8_t v_thresh = vdupq_n_s16(thresh), v_maxval = vdupq_n_s16(maxval);

            for( ; j <= roi.width - 8; j += 8 )
            {
                uint16x8_t v_mask = vcgtq_s16(vld1q_s16(src + j), v_thresh);
                vst1q_s16(dst + j, vandq_s16(vreinterpretq_s16_u16(v_mask), v_maxval));
            }
        #endif

            for( ; j < roi.width; j++ )
                dst[j] = src[j] > thresh ? maxval : 0;
        }
        break;

    case THRESH_BINARY_INV:
        for( i = 0; i < roi.height; i++, src += src_step, dst += dst_step )
        {
            j = 0;
        #if CV_SSE2
            if( useSIMD )
            {
                __m128i thresh8 = _mm_set1_epi16(thresh), maxval8 = _mm_set1_epi16(maxval);
                for( ; j <= roi.width - 16; j += 16 )
                {
                    __m128i v0, v1;
                    v0 = _mm_loadu_si128( (const __m128i*)(src + j) );
                    v1 = _mm_loadu_si128( (const __m128i*)(src + j + 8) );
                    v0 = _mm_cmpgt_epi16( v0, thresh8 );
                    v1 = _mm_cmpgt_epi16( v1, thresh8 );
                    v0 = _mm_andnot_si128( v0, maxval8 );
                    v1 = _mm_andnot_si128( v1, maxval8 );
                    _mm_storeu_si128((__m128i*)(dst + j), v0 );
                    _mm_storeu_si128((__m128i*)(dst + j + 8), v1 );
                }
            }
        #elif CV_NEON
            int16x8_t v_thresh = vdupq_n_s16(thresh), v_maxval = vdupq_n_s16(maxval);

            for( ; j <= roi.width - 8; j += 8 )
            {
                uint16x8_t v_mask = vcleq_s16(vld1q_s16(src + j), v_thresh);
                vst1q_s16(dst + j, vandq_s16(vreinterpretq_s16_u16(v_mask), v_maxval));
            }
        #endif

            for( ; j < roi.width; j++ )
                dst[j] = src[j] <= thresh ? maxval : 0;
        }
        break;

    case THRESH_TRUNC:
        for( i = 0; i < roi.height; i++, src += src_step, dst += dst_step )
        {
            j = 0;
        #if CV_SSE2
            if( useSIMD )
            {
                __m128i thresh8 = _mm_set1_epi16(thresh);
                for( ; j <= roi.width - 16; j += 16 )
                {
                    __m128i v0, v1;
                    v0 = _mm_loadu_si128( (const __m128i*)(src + j) );
                    v1 = _mm_loadu_si128( (const __m128i*)(src + j + 8) );
                    v0 = _mm_min_epi16( v0, thresh8 );
                    v1 = _mm_min_epi16( v1, thresh8 );
                    _mm_storeu_si128((__m128i*)(dst + j), v0 );
                    _mm_storeu_si128((__m128i*)(dst + j + 8), v1 );
                }
            }
        #elif CV_NEON
            int16x8_t v_thresh = vdupq_n_s16(thresh);

            for( ; j <= roi.width - 8; j += 8 )
                vst1q_s16(dst + j, vminq_s16(vld1q_s16(src + j), v_thresh));
        #endif

            for( ; j < roi.width; j++ )
                dst[j] = std::min(src[j], thresh);
        }
        break;

    case THRESH_TOZERO:
        for( i = 0; i < roi.height; i++, src += src_step, dst += dst_step )
        {
            j = 0;
        #if CV_SSE2
            if( useSIMD )
            {
                __m128i thresh8 = _mm_set1_epi16(thresh);
                for( ; j <= roi.width - 16; j += 16 )
                {
                    __m128i v0, v1;
                    v0 = _mm_loadu_si128( (const __m128i*)(src + j) );
                    v1 = _mm_loadu_si128( (const __m128i*)(src + j + 8) );
                    v0 = _mm_and_si128(v0, _mm_cmpgt_epi16(v0, thresh8));
                    v1 = _mm_and_si128(v1, _mm_cmpgt_epi16(v1, thresh8));
                    _mm_storeu_si128((__m128i*)(dst + j), v0 );
                    _mm_storeu_si128((__m128i*)(dst + j + 8), v1 );
                }
            }
        #elif CV_NEON
            int16x8_t v_thresh = vdupq_n_s16(thresh);

            for( ; j <= roi.width - 8; j += 8 )
            {
                int16x8_t v_src = vld1q_s16(src + j);
                uint16x8_t v_mask = vcgtq_s16(v_src, v_thresh);
                vst1q_s16(dst + j, vandq_s16(vreinterpretq_s16_u16(v_mask), v_src));
            }
        #endif

            for( ; j < roi.width; j++ )
            {
                short v = src[j];
                dst[j] = v > thresh ? v : 0;
            }
        }
        break;

    case THRESH_TOZERO_INV:
        for( i = 0; i < roi.height; i++, src += src_step, dst += dst_step )
        {
            j = 0;
        #if CV_SSE2
            if( useSIMD )
            {
                __m128i thresh8 = _mm_set1_epi16(thresh);
                for( ; j <= roi.width - 16; j += 16 )
                {
                    __m128i v0, v1;
                    v0 = _mm_loadu_si128( (const __m128i*)(src + j) );
                    v1 = _mm_loadu_si128( (const __m128i*)(src + j + 8) );
                    v0 = _mm_andnot_si128(_mm_cmpgt_epi16(v0, thresh8), v0);
                    v1 = _mm_andnot_si128(_mm_cmpgt_epi16(v1, thresh8), v1);
                    _mm_storeu_si128((__m128i*)(dst + j), v0 );
                    _mm_storeu_si128((__m128i*)(dst + j + 8), v1 );
                }
            }
        #elif CV_NEON
            int16x8_t v_thresh = vdupq_n_s16(thresh);

            for( ; j <= roi.width - 8; j += 8 )
            {
                int16x8_t v_src = vld1q_s16(src + j);
                uint16x8_t v_mask = vcleq_s16(v_src, v_thresh);
                vst1q_s16(dst + j, vandq_s16(vreinterpretq_s16_u16(v_mask), v_src));
            }
        #endif
            for( ; j < roi.width; j++ )
            {
                short v = src[j];
                dst[j] = v <= thresh ? v : 0;
            }
        }
        break;
    default:
        return CV_Error( CV_StsBadArg, "" );
    }
}