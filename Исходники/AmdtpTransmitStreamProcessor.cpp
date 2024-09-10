/**
 * @brief mux all audio ports to events
 * @param data 
 * @param offset 
 * @param nevents 
 */
void
AmdtpTransmitStreamProcessor::encodeAudioPortsFloat(quadlet_t *data,
                                                    unsigned int offset,
                                                    unsigned int nevents)
{
    unsigned int j;
    quadlet_t *target_event;
    int i;

    float * client_buffers[4];
    float tmp_values[4] __attribute__ ((aligned (16)));
    uint32_t tmp_values_int[4] __attribute__ ((aligned (16)));

    // prepare the scratch buffer
    assert(m_scratch_buffer_size_bytes > nevents * 4);
    memset(m_scratch_buffer, 0, nevents * 4);

    const __m128i label = _mm_set_epi32 (0x40000000, 0x40000000, 0x40000000, 0x40000000);
    const __m128i mask = _mm_set_epi32 (0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF);
    const __m128 mult = _mm_set_ps(AMDTP_FLOAT_MULTIPLIER, AMDTP_FLOAT_MULTIPLIER, AMDTP_FLOAT_MULTIPLIER, AMDTP_FLOAT_MULTIPLIER);

#if AMDTP_CLIP_FLOATS
    const __m128 v_max = _mm_set_ps(1.0, 1.0, 1.0, 1.0);
    const __m128 v_min = _mm_set_ps(-1.0, -1.0, -1.0, -1.0);
#endif

    // this assumes that audio ports are sorted by position,
    // and that there are no gaps
    for (i = 0; i < ((int)m_nb_audio_ports)-4; i += 4) {
        struct _MBLA_port_cache *p;

        // get the port buffers
        for (j=0; j<4; j++) {
            p = &(m_audio_ports.at(i+j));
            if(likely(p->buffer && p->enabled)) {
                client_buffers[j] = (float *) p->buffer;
                client_buffers[j] += offset;
            } else {
                // if a port is disabled or has no valid
                // buffer, use the scratch buffer (all zero's)
                client_buffers[j] = (float *) m_scratch_buffer;
            }
        }

        // the base event for this position
        target_event = (quadlet_t *)(data + i);
        // process the events
        for (j=0;j < nevents; j += 1)
        {
            // read the values
            tmp_values[0] = *(client_buffers[0]);
            tmp_values[1] = *(client_buffers[1]);
            tmp_values[2] = *(client_buffers[2]);
            tmp_values[3] = *(client_buffers[3]);

            // now do the SSE based conversion/labeling
            __m128 v_float = *((__m128*)tmp_values);
            __m128i *target = (__m128i*)target_event;
            __m128i v_int;

            // clip
#if AMDTP_CLIP_FLOATS
            // do SSE clipping
            v_float = _mm_max_ps(v_float, v_min);
            v_float = _mm_min_ps(v_float, v_max);
#endif

            // multiply
            v_float = _mm_mul_ps(v_float, mult);
            // convert to signed integer
            v_int = _mm_cvttps_epi32( v_float );
            // mask
            v_int = _mm_and_si128( v_int, mask );
            // label it
            v_int = _mm_or_si128( v_int, label );

            // do endian conversion (SSE is always little endian)
            // do first swap
            v_int = _mm_or_si128( _mm_slli_epi16( v_int, 8 ), _mm_srli_epi16( v_int, 8 ) );
            // do second swap
            v_int = _mm_or_si128( _mm_slli_epi32( v_int, 16 ), _mm_srli_epi32( v_int, 16 ) );
            // store the packed int
            // (target misalignment is assumed since we don't know the m_dimension)
            _mm_storeu_si128 (target, v_int);

            // increment the buffer pointers
            client_buffers[0]++;
            client_buffers[1]++;
            client_buffers[2]++; 
            client_buffers[3]++;

            // go to next target event position
            target_event += m_dimension;
        }
    }

    // do remaining ports
    // NOTE: these can be time-SSE'd
    for (; i < (int)m_nb_audio_ports; i++) {
        struct _MBLA_port_cache &p = m_audio_ports.at(i);
        target_event = (quadlet_t *)(data + i);
#ifdef DEBUG
        assert(nevents + offset <= p.buffer_size );
#endif

        if(likely(p.buffer && p.enabled)) {
            float *buffer = (float *)(p.buffer);
            buffer += offset;
    
            for (j = 0;j < nevents; j += 4)
            {
                // read the values
                tmp_values[0] = *buffer;
                buffer++;
                tmp_values[1] = *buffer;
                buffer++;
                tmp_values[2] = *buffer;
                buffer++;
                tmp_values[3] = *buffer;
                buffer++;

                // now do the SSE based conversion/labeling
                __m128 v_float = *((__m128*)tmp_values);
                __m128i v_int;

#if AMDTP_CLIP_FLOATS
                // do SSE clipping
                v_float = _mm_max_ps(v_float, v_min);
                v_float = _mm_min_ps(v_float, v_max);
#endif
                // multiply
                v_float = _mm_mul_ps(v_float, mult);
                // convert to signed integer
                v_int = _mm_cvttps_epi32( v_float );
                // mask
                v_int = _mm_and_si128( v_int, mask );
                // label it
                v_int = _mm_or_si128( v_int, label );
    
                // do endian conversion (SSE is always little endian)
                // do first swap
                v_int = _mm_or_si128( _mm_slli_epi16( v_int, 8 ), _mm_srli_epi16( v_int, 8 ) );
                // do second swap
                v_int = _mm_or_si128( _mm_slli_epi32( v_int, 16 ), _mm_srli_epi32( v_int, 16 ) );

                // store the packed int
                _mm_store_si128 ((__m128i *)(&tmp_values_int), v_int);

                // increment the buffer pointers
                *target_event = tmp_values_int[0];
                target_event += m_dimension;
                *target_event = tmp_values_int[1];
                target_event += m_dimension;
                *target_event = tmp_values_int[2];
                target_event += m_dimension;
                *target_event = tmp_values_int[3];
                target_event += m_dimension;
            }

            // do the remainder of the events
            for(;j < nevents; j += 1) {
                float *in = (float *)buffer;
#if AMDTP_CLIP_FLOATS
                // clip directly to the value of a maxed event
                if(unlikely(*in > 1.0)) {
                    *target_event = CONDSWAPTOBUS32_CONST(0x407FFFFF);
                } else if(unlikely(*in < -1.0)) {
                    *target_event = CONDSWAPTOBUS32_CONST(0x40800001);
                } else {
                    float v = (*in) * AMDTP_FLOAT_MULTIPLIER;
                    unsigned int tmp = ((int) v);
                    tmp = ( tmp & 0x00FFFFFF ) | 0x40000000;
                    *target_event = CondSwapToBus32((quadlet_t)tmp);
                }
#else
                float v = (*in) * AMDTP_FLOAT_MULTIPLIER;
                unsigned int tmp = ((int) v);
                tmp = ( tmp & 0x00FFFFFF ) | 0x40000000;
                *target_event = CondSwapToBus32((quadlet_t)tmp);
#endif
                buffer++;
                target_event += m_dimension;
            }

        } else {
            for (j = 0;j < nevents; j += 1)
            {
                // hardcoded byte swapped
                *target_event = 0x00000040;
                target_event += m_dimension;
            }
        }
    }
}