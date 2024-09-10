    void orderFrames( eq::Frames& frames, const Matrix4f& modelView )
    {
        LBASSERT( !_channel->useOrtho( ));

        // calculate modelview inversed+transposed matrix
        Matrix3f modelviewITM;
        Matrix4f modelviewIM;
        modelView.inverse( modelviewIM );
        Matrix3f( modelviewIM ).transpose_to( modelviewITM );

        Vector3f norm = modelviewITM * Vector3f( 0.0f, 0.0f, 1.0f );
        norm.normalize();
        std::sort( frames.begin(), frames.end(), cmpRangesInc );

        // cos of angle between normal and vectors from center
        std::vector<double> dotVals;

        // of projection to the middle of slices' boundaries
        for( const eq::Frame* frame : frames )
        {
            const double px = -1.0 + frame->getRange().end*2.0;
            const Vector4f pS = modelView * Vector4f( 0.0f, 0.0f, px, 1.0f );
            Vector3f pSsub( pS[ 0 ], pS[ 1 ], pS[ 2 ] );
            pSsub.normalize();
            dotVals.push_back( norm.dot( pSsub ));
        }

        const Vector4f pS = modelView * Vector4f( 0.0f, 0.0f, -1.0f, 1.0f );
        eq::Vector3f pSsub( pS[ 0 ], pS[ 1 ], pS[ 2 ] );
        pSsub.normalize();
        dotVals.push_back( norm.dot( pSsub ));

        // check if any slices need to be rendered in reverse order
        size_t minPos = std::numeric_limits< size_t >::max();
        for( size_t i=0; i<dotVals.size()-1; i++ )
            if( dotVals[i] > 0 && dotVals[i+1] > 0 )
                minPos = static_cast< int >( i );

        const size_t nFrames = frames.size();
        minPos++;
        if( minPos < frames.size()-1 )
        {
            eq::Frames framesTmp = frames;

            // copy slices that should be rendered first
            memcpy( &frames[ nFrames-minPos-1 ], &framesTmp[0],
                    (minPos+1)*sizeof( eq::Frame* ) );

            // copy slices that should be rendered last, in reverse order
            for( size_t i=0; i<nFrames-minPos-1; i++ )
                frames[ i ] = framesTmp[ nFrames-i-1 ];
        }
    }