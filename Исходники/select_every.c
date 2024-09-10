static int init( hnd_t *handle, cli_vid_filter_t *filter, video_info_t *info, x264_param_t *param, char *opt_string )
{
    selvry_hnd_t *h = malloc( sizeof(selvry_hnd_t) );
    if( !h )
        return -1;
    h->pattern_len = 0;
    h->step_size = 0;
    int offsets[MAX_PATTERN_SIZE];
    for( char *tok, *p = opt_string; (tok = strtok( p, "," )); p = NULL )
    {
        int val = x264_otoi( tok, -1 );
        if( p )
        {
            FAIL_IF_ERROR( val <= 0, "invalid step `%s'\n", tok );
            h->step_size = val;
            continue;
        }
        FAIL_IF_ERROR( val < 0 || val >= h->step_size, "invalid offset `%s'\n", tok );
        FAIL_IF_ERROR( h->pattern_len >= MAX_PATTERN_SIZE, "max pattern size %d reached\n", MAX_PATTERN_SIZE );
        offsets[h->pattern_len++] = val;
    }
    FAIL_IF_ERROR( !h->step_size, "no step size provided\n" );
    FAIL_IF_ERROR( !h->pattern_len, "no offsets supplied\n" );

    h->pattern = malloc( h->pattern_len * sizeof(int) );
    if( !h->pattern )
        return -1;
    memcpy( h->pattern, offsets, h->pattern_len * sizeof(int) );

    /* determine required cache size to maintain pattern. */
    intptr_t max_rewind = 0;
    int min = h->step_size;
    for( int i = h->pattern_len-1; i >= 0; i-- )
    {
         min = X264_MIN( min, offsets[i] );
         if( i )
             max_rewind = X264_MAX( max_rewind, offsets[i-1] - min + 1 );
         /* reached maximum rewind size */
         if( max_rewind == h->step_size )
             break;
    }
    char name[20];
    sprintf( name, "cache_%d", param->i_bitdepth );
    if( x264_init_vid_filter( name, handle, filter, info, param, (void*)max_rewind ) )
        return -1;

    /* done initing, overwrite properties */
    if( h->step_size != h->pattern_len )
    {
        info->num_frames = (uint64_t)info->num_frames * h->pattern_len / h->step_size;
        info->fps_den *= h->step_size;
        info->fps_num *= h->pattern_len;
        x264_reduce_fraction( &info->fps_num, &info->fps_den );
        if( info->vfr )
        {
            info->timebase_den *= h->pattern_len;
            info->timebase_num *= h->step_size;
            x264_reduce_fraction( &info->timebase_num, &info->timebase_den );
        }
    }

    h->pts = 0;
    h->vfr = info->vfr;
    h->prev_filter = *filter;
    h->prev_hnd = *handle;
    *filter = select_every_filter;
    *handle = h;

    return 0;
}