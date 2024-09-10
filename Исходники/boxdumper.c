int main( int argc, char *argv[] )
{
    if( argc < 2 )
        return print_help( -1 );
    int dump_box = 1;
    int chapter = 0;
    char *filename;
    if( argc > 2 )
    {
        if( !strcasecmp( argv[1], "--box" ) )
            DO_NOTHING;
        else if( !strcasecmp( argv[1], "--chapter" ) )
            chapter = 1;
        else if( !strcasecmp( argv[1], "--timestamp" ) )
            dump_box = 0;
        else
            return print_help( -1 );
        filename = argv[2];
    }
    else
    {
        if( !strcasecmp( argv[1], "-h" ) || !strcasecmp( argv[1], "--help" ) )
            return print_help( 0 );
        filename = argv[1];
    }
#ifdef _WIN32
    _setmode( _fileno(stdin), _O_BINARY );
#endif
    lsmash_file_mode mode = LSMASH_FILE_MODE_READ;
    if( dump_box )
        mode |= LSMASH_FILE_MODE_DUMP;
    lsmash_root_t *root = lsmash_open_movie( filename, mode );
    if( !root )
    {
        fprintf( stderr, "Failed to open input file.\n" );
        return -1;
    }
    if( chapter )
    {
        if( lsmash_print_chapter_list( root ) )
            return BOXDUMPER_ERR( "Failed to extract chapter.\n" );
    }
    else if( dump_box )
    {
        if( lsmash_print_movie( root, "-" ) )
            return BOXDUMPER_ERR( "Failed to dump box structure.\n" );
    }
    else
    {
        lsmash_movie_parameters_t movie_param;
        lsmash_initialize_movie_parameters( &movie_param );
        lsmash_get_movie_parameters( root, &movie_param );
        uint32_t num_tracks = movie_param.number_of_tracks;
        for( uint32_t track_number = 1; track_number <= num_tracks; track_number++ )
        {
            uint32_t track_ID = lsmash_get_track_ID( root, track_number );
            if( !track_ID )
                return BOXDUMPER_ERR( "Failed to get track_ID.\n" );
            lsmash_media_parameters_t media_param;
            lsmash_initialize_media_parameters( &media_param );
            if( lsmash_get_media_parameters( root, track_ID, &media_param ) )
                return BOXDUMPER_ERR( "Failed to get media parameters.\n" );
            if( lsmash_construct_timeline( root, track_ID ) )
                return BOXDUMPER_ERR( "Failed to construct timeline.\n" );
            uint32_t timeline_shift;
            if( lsmash_get_composition_to_decode_shift_from_media_timeline( root, track_ID, &timeline_shift ) )
                return BOXDUMPER_ERR( "Failed to get timestamps.\n" );
            lsmash_media_ts_list_t ts_list;
            if( lsmash_get_media_timestamps( root, track_ID, &ts_list ) )
                return BOXDUMPER_ERR( "Failed to get timestamps.\n" );
            fprintf( stdout, "track_ID: %"PRIu32"\n", track_ID );
            fprintf( stdout, "Media timescale: %"PRIu32"\n", media_param.timescale );
            lsmash_media_ts_t *ts_array = ts_list.timestamp;
            if( !ts_array )
            {
                fprintf( stdout, "\n" );
                continue;
            }
            for( uint32_t i = 0; i < ts_list.sample_count; i++ )
                fprintf( stdout, "DTS = %"PRIu64", CTS = %"PRIu64"\n", ts_array[i].dts, ts_array[i].cts + timeline_shift );
            free( ts_array );
            fprintf( stdout, "\n" );
        }
    }
    lsmash_destroy_root( root );
    return 0;
}