void
audio_resampler_acm::close( void )
{


    MMRESULT err;


    if ( acm_stream )
    {

        if ( acm_header.fdwStatus & ACMSTREAMHEADER_STATUSF_PREPARED )
        {

            acm_header.cbSrcLength = src_buflen;
            acm_header.cbDstLength = dst_buflen;

            err = acmStreamUnprepareHeader( acm_stream, &acm_header, 0L );

        
            if ( err != MMSYSERR_NOERROR )
            {
            
                //
                // Free buffer memory
                //

                if ( acm_header.pbSrc != 0 )
                    delete[] acm_header.pbSrc;

                if ( acm_header.pbDst != 0 )
                    delete[] acm_header.pbDst;


                //
                // Re-init structures
                //

                init_();

                //
                // Updating status
                //

                stream_opened = false;


                //TODO: throw error
                MessageBox( 0, _T("acmStreamUnPrepareHeader error"), _T("ERROR"), MB_ICONERROR );

            
            }
        }


        err = acmStreamClose( acm_stream, 0 );
        acm_stream = 0;

        if ( err != MMSYSERR_NOERROR )
        {

            //
            // Free buffer memory
            //

            if ( acm_header.pbSrc != 0 )
                delete[] acm_header.pbSrc;

            if ( acm_header.pbDst != 0 )
                delete[] acm_header.pbDst;


            //
            // Re-init structures
            //

            init_();


            //
            // Updating status
            //

            stream_opened = false;


            //TODO: throw error!

            MessageBox( 0, _T("acmStreamClose error"), _T("ERROR"), MB_ICONERROR );


        }


    }//if acm_stream != 0






    //
    // Free buffer memory
    //

    if ( acm_header.pbSrc != 0 )
        delete[] acm_header.pbSrc;

    if ( acm_header.pbDst != 0 )
        delete[] acm_header.pbDst;


    //
    // Re-init structures
    //

    init_();


    //
    // Updating status
    //

    stream_opened = false;



    //
    // ACM sream successfully closed.
    //


}