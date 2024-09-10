/**
 * Detect subtitle files.
 *
 * When called this function will split up the psz_name string into a
 * directory, filename and extension. It then opens the directory
 * in which the file resides and tries to find possible matches of
 * subtitles files.
 *
 * \ingroup Demux
 * \param p_this the calling \ref input_thread_t
 * \param psz_path a list of subdirectories (separated by a ',') to look in.
 * \param psz_name_org the complete filename to base the search on.
 * \param pp_slaves an initialized input item slave list to append detected subtitles to
 * \param p_slaves pointer to the size of the slave list
 * \return VLC_SUCCESS if ok
 */
int subtitles_Detect( input_thread_t *p_this, char *psz_path, const char *psz_name_org,
                      input_item_slave_t ***ppp_slaves, int *p_slaves )
{
    int i_fuzzy = var_GetInteger( p_this, "sub-autodetect-fuzzy" );
    if ( i_fuzzy == 0 )
        return VLC_EGENERIC;
    int j, i_fname_len;
    input_item_slave_t **pp_slaves = *ppp_slaves;
    int i_slaves = *p_slaves;
    char *f_fname_noext = NULL, *f_fname_trim = NULL;
    char **subdirs; /* list of subdirectories to look in */

    if( !psz_name_org )
        return VLC_EGENERIC;

    char *psz_fname = vlc_uri2path( psz_name_org );
    if( !psz_fname )
        return VLC_EGENERIC;

    /* extract filename & dirname from psz_fname */
    char *f_dir = strdup( psz_fname );
    if( f_dir == 0 )
    {
        free( psz_fname );
        return VLC_ENOMEM;
    }

    const char *f_fname = strrchr( psz_fname, DIR_SEP_CHAR );
    if( !f_fname )
    {
        free( f_dir );
        free( psz_fname );
        return VLC_EGENERIC;
    }
    f_fname++; /* Skip the '/' */
    f_dir[f_fname - psz_fname] = 0; /* keep dir separator in f_dir */

    i_fname_len = strlen( f_fname );

    f_fname_noext = malloc(i_fname_len + 1);
    f_fname_trim = malloc(i_fname_len + 1 );
    if( !f_fname_noext || !f_fname_trim )
    {
        free( f_dir );
        free( f_fname_noext );
        free( f_fname_trim );
        free( psz_fname );
        return VLC_ENOMEM;
    }

    strcpy_strip_ext( f_fname_noext, f_fname );
    strcpy_trim( f_fname_trim, f_fname_noext );

    subdirs = paths_to_list( f_dir, psz_path );
    for( j = -1; (j == -1) || ( j >= 0 && subdirs != NULL && subdirs[j] != NULL ); j++ )
    {
        const char *psz_dir = (j < 0) ? f_dir : subdirs[j];
        if( psz_dir == NULL || ( j >= 0 && !strcmp( psz_dir, f_dir ) ) )
            continue;

        /* parse psz_src dir */
        DIR *dir = vlc_opendir( psz_dir );
        if( dir == NULL )
            continue;

        msg_Dbg( p_this, "looking for a subtitle file in %s", psz_dir );

        const char *psz_name;
        while( (psz_name = vlc_readdir( dir )) )
        {
            if( psz_name[0] == '.' || !subtitles_Filter( psz_name ) )
                continue;

            char tmp_fname_noext[strlen( psz_name ) + 1];
            char tmp_fname_trim[strlen( psz_name ) + 1];
            char tmp_fname_ext[strlen( psz_name ) + 1];
            const char *tmp;
            int i_prio = 0;

            /* retrieve various parts of the filename */
            strcpy_strip_ext( tmp_fname_noext, psz_name );
            strcpy_get_ext( tmp_fname_ext, psz_name );
            strcpy_trim( tmp_fname_trim, tmp_fname_noext );

            if( !strcmp( tmp_fname_trim, f_fname_trim ) )
            {
                /* matches the movie name exactly */
                i_prio = SLAVE_PRIORITY_MATCH_ALL;
            }
            else if( (tmp = strstr( tmp_fname_trim, f_fname_trim )) )
            {
                /* contains the movie name */
                tmp += strlen( f_fname_trim );
                if( whiteonly( tmp ) )
                {
                    /* chars in front of the movie name */
                    i_prio = SLAVE_PRIORITY_MATCH_RIGHT;
                }
                else
                {
                    /* chars after (and possibly in front of)
                     * the movie name */
                    i_prio = SLAVE_PRIORITY_MATCH_LEFT;
                }
            }
            else if( j == -1 )
            {
                /* doesn't contain the movie name, prefer files in f_dir over subdirs */
                i_prio = SLAVE_PRIORITY_MATCH_NONE;
            }
            if( i_prio >= i_fuzzy )
            {
                struct stat st;
                char *path;

                size_t i_len = strlen( psz_dir );
                const char *psz_format;
                if ( i_len == 0 )
                    continue;
                if( psz_dir[i_len - 1] == DIR_SEP_CHAR )
                    psz_format = "%s%s";
                else
                    psz_format = "%s"DIR_SEP"%s";

                if( asprintf( &path, psz_format, psz_dir, psz_name ) < 0 )
                    continue;

                if( strcmp( path, psz_fname )
                 && vlc_stat( path, &st ) == 0
                 && S_ISREG( st.st_mode ) )
                {
                    msg_Dbg( p_this,
                            "autodetected subtitle: %s with priority %d",
                            path, i_prio );
                    char *psz_uri = vlc_path2uri( path, NULL );
                    input_item_slave_t *p_sub = psz_uri != NULL ?
                        input_item_slave_New( psz_uri, SLAVE_TYPE_SPU, i_prio )
                        : NULL;
                    if( p_sub )
                    {
                        p_sub->b_forced = true;
                        INSERT_ELEM( pp_slaves, i_slaves, i_slaves, p_sub );
                    }
                    free( psz_uri );
                }
                free( path );
            }
        }
        closedir( dir );
    }
    if( subdirs )
    {
        for( j = 0; subdirs[j]; j++ )
            free( subdirs[j] );
        free( subdirs );
    }
    free( f_dir );
    free( f_fname_trim );
    free( f_fname_noext );
    free( psz_fname );

    for( int i = 0; i < i_slaves; i++ )
    {
        input_item_slave_t *p_sub = pp_slaves[i];

        bool b_reject = false;
        char *psz_ext = strrchr( p_sub->psz_uri, '.' );
        if( !psz_ext )
            continue;
        psz_ext++;

        if( !strcasecmp( psz_ext, "sub" ) )
        {
            for( int j = 0; j < i_slaves; j++ )
            {
                input_item_slave_t *p_sub_inner = pp_slaves[j];

                /* check that the filenames without extension match */
                if( strncasecmp( p_sub->psz_uri, p_sub_inner->psz_uri,
                    strlen( p_sub->psz_uri ) - 3 ) )
                    continue;

                char *psz_ext_inner = strrchr( p_sub_inner->psz_uri, '.' );
                if( !psz_ext_inner )
                    continue;
                psz_ext_inner++;

                /* check that we have an idx file */
                if( !strcasecmp( psz_ext_inner, "idx" ) )
                {
                    b_reject = true;
                    break;
                }
            }
        }
        else if( !strcasecmp( psz_ext, "cdg" ) )
        {
            if( p_sub->i_priority < SLAVE_PRIORITY_MATCH_ALL )
                b_reject = true;
        }
        if( b_reject )
        {
            pp_slaves[i] = NULL;
            input_item_slave_Delete( p_sub );
        }
    }

    *ppp_slaves = pp_slaves; /* in case of realloc */
    *p_slaves = i_slaves;
    return VLC_SUCCESS;
}