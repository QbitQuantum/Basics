    static void error_exit( j_common_ptr cinfo )
    {
        writer< Device, jpeg_tag >* mgr = reinterpret_cast< writer< Device, jpeg_tag >* >( cinfo->client_data );

        longjmp( mgr->_mark, 1 );
    }