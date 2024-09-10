    /**
     * \brief Lossy data compression by linear or logarithmic quantization (16 bit)
     *
     * Allocates \p m_cdata and use it to store compressed data from \p m_rdata.
     * Only double types accepted! NaN, +Inf and -Inf are allowed.
     * 
     * \param[in] bDoLog Using logarithmic (true) or linear (false) quantization.
     */
    bool linlogQuantizerCompress( bool bDoLog )
    {
        assert( m_rdata && !m_cdata && 
                m_rdata_element_size == sizeof( double ) && 
                m_rdata_size % m_rdata_element_size == 0 );
        
        double    dOffset = 0.0, dScale = 1.0;
        double    dMinVal, dMaxVal;
        bool      bMinValSet = false, bMaxValSet = false;
        double*   rdata = (double*)m_rdata;
        size_t    cntElements = m_rdata_size / sizeof(*rdata);
        float*    pFloatData;
        uint16_t* pUintData;
        
        // compressor works for double type only
        if( !m_rdata_is_double_type )
        {
            m_err.set( MSG_ERRCOMPRARG );
            return false;
        }
        
        // seek data limits for quantization
        for( size_t i = 0; i < cntElements; i++ )
        {
            if( DBL_ISFINITE( rdata[i] ) && rdata[i] != 0.0 )
            {
                if( !bMinValSet || rdata[i] < dMinVal )
                {
                    dMinVal = rdata[i];
                    bMinValSet = true;
                }
                
                if( !bMaxValSet || rdata[i] > dMaxVal )
                {
                    dMaxVal = rdata[i];
                    bMaxValSet = true;
                }
            }
        }

        // in logarithmic mode, no negative values are allowed
        if( bDoLog && dMinVal < 0.0 )
        {
            m_err.set( MSG_ERRCOMPRLOGMINVALS );
            return false;
        }

        // compressor converts each value to uint16_t
        // 2 additional floats for offset and scale
        m_cdata_size = 2 * sizeof( float ) + cntElements * sizeof( uint16_t );  
        m_cdata      = m_Allocator( m_cdata_size );

        if( !m_cdata )
        {
            m_err.set( MSG_ERRMEMORY );
            return false;
        }
        
        pFloatData   = (float*)m_cdata;
        pUintData    = (uint16_t*)&pFloatData[2];

        // calculate offset information
        if( bMinValSet )
        {
            dOffset = bDoLog ? log( dMinVal ) : dMinVal;
        }

        // calculate scale information
        if( bMaxValSet )
        {
            double dValue = bDoLog ? log( dMaxVal ) : dMaxVal;

            // data is mapped on 65529 (0xFFF8u) levels
            dScale  = ( dValue - dOffset ) / 0xFFF8u;

            // if dMaxValue == dMinValue, scale would be set to zero.
            // to avoid division by zero on decompression, it is set to 1.0 here.
            // this doesn't affect the result (0/1 = 0)
            if( dScale == 0.0 )
            {
                dScale = 1.0;
            }
        }

        // store offset and scale information for decompression
        pFloatData[0] = (float)dOffset;
        pFloatData[1] = (float)dScale;
        
        // quantization
        for( size_t i = 0; i < cntElements; i++ )
        {
            // non-finite values and zero are mapped to special values
            if( DBL_ISFINITE( rdata[i] ) && rdata[i] != 0.0 )
            {
                double dValue = bDoLog ? log( rdata[i] ) : rdata[i];

                *pUintData++ = (uint16_t) ( (dValue - dOffset ) / dScale ) & 0xFFF8u;
            } 
            else
            {
                // special values for zero, infinity and nan
                if( fabs( rdata[i] ) == 0.0 )
                {
                    *pUintData++ = 0xFFF8u + 1 + ( _copysign( 1.0, rdata[i] ) < 0.0 );
                }
                else if( DBL_ISINF( rdata[i] ) )
                {
                    *pUintData++ = 0xFFF8u + 3 + ( _copysign( 1.0, rdata[i] ) < 0.0 );
                }
                else if( DBL_ISNAN( rdata[i] ) )
                {
                    *pUintData++ = 0xFFF8u + 5;
                }
            }
        }
        
        return true;
    }