int orte_list_local_hnps(opal_list_t *hnps, bool connect)
{
    int ret;
#ifndef __WINDOWS__
    DIR *cur_dirp = NULL;
    struct dirent * dir_entry;
#else
    HANDLE hFind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA file_data;
#endif  /* __WINDOWS__ */
    char *contact_filename = NULL;
    orte_hnp_contact_t *hnp;
    char *headdir;
    
#if !defined(__WINDOWS__)

    /*
     * Check to make sure we have access to the top-level directory
     */
    headdir = opal_os_path(false, orte_process_info.tmpdir_base, orte_process_info.top_session_dir, NULL);
    
    if( ORTE_SUCCESS != (ret = opal_os_dirpath_access(headdir, 0) )) {
        /* it is okay not to find this as there may not be any
         * HNP's present, and we don't write our own session dir
         */
        if (ORTE_ERR_NOT_FOUND != ret) {
            ORTE_ERROR_LOG(ret);
        }
        goto cleanup;
    }
    
    /*
     * Open up the base directory so we can get a listing
     */
    if( NULL == (cur_dirp = opendir(headdir)) ) {
        goto cleanup;
    }
    /*
     * For each directory
     */
    while( NULL != (dir_entry = readdir(cur_dirp)) ) {
        
        /*
         * Skip the obvious
         */
        if( 0 == strncmp(dir_entry->d_name, ".", strlen(".")) ||
            0 == strncmp(dir_entry->d_name, "..", strlen("..")) ) {
            continue;
        }
        
        /*
         * See if a contact file exists in this directory and read it
         */
        contact_filename = opal_os_path( false, headdir,
                                         dir_entry->d_name, "contact.txt", NULL );
        
        hnp = OBJ_NEW(orte_hnp_contact_t);
        if (ORTE_SUCCESS == (ret = orte_read_hnp_contact_file(contact_filename, hnp, connect))) {
            opal_list_append(hnps, &(hnp->super));
        } else {
            OBJ_RELEASE(hnp);
        }
     }
#else
    /*
     * Open up the base directory so we can get a listing.
     *
     * On Windows if we want to parse the content of a directory the filename
     * should end with the "*". Otherwise we will only open the directory
     * structure (and not the content).
     */
    char *subdirs = opal_os_path(false, orte_process_info.tmpdir_base, orte_process_info.top_session_dir, "*", NULL);
    headdir = opal_os_path(false, orte_process_info.tmpdir_base, orte_process_info.top_session_dir, NULL);

    hFind = FindFirstFile( subdirs, &file_data );
    if( INVALID_HANDLE_VALUE == hFind ) {
        goto cleanup;
    }
    
    /*
     * For each directory
     */
    do {
        /*
         * Skip the obvious
         */
        if( 0 == strncmp(file_data.cFileName, ".", strlen(".")) ||
            0 == strncmp(file_data.cFileName, "..", strlen("..")) ) {
            continue;
        }
        
        /*
         * See if a contact file exists in this directory and read it
         */
        contact_filename = opal_os_path( false, headdir,
                                         file_data.cFileName, "contact.txt", NULL );
        
        hnp = OBJ_NEW(orte_hnp_contact_t);
        if (ORTE_SUCCESS == (ret = orte_read_hnp_contact_file(contact_filename, hnp, connect))) {
            opal_list_append(hnps, &(hnp->super));
        } else {
            OBJ_RELEASE(hnp);
        }
    } while( 0 != FindNextFile( hFind, &file_data ) );
    
#endif  /* !defined(__WINDOWS__) */
    
cleanup:
#ifndef __WINDOWS__
    if( NULL != cur_dirp )
        closedir(cur_dirp);
#else
    FindClose(hFind);
#endif  /* __WINDOWS__ */
    free(headdir);
    if( NULL != contact_filename)
        free(contact_filename);
    
    return (opal_list_is_empty(hnps) ? ORTE_ERR_NOT_FOUND : ORTE_SUCCESS);
}