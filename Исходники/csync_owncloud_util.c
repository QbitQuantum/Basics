void fill_webdav_properties_into_resource(struct resource* newres, const ne_prop_result_set *set)
{
    const char *clength, *modtime, *file_id = NULL;
    const char *directDownloadUrl = NULL;
    const char *directDownloadCookies = NULL;
    const char *resourcetype = NULL;
    const char *etag = NULL;
    const char *perm = NULL;

    modtime      = ne_propset_value( set, &ls_props[0] );
    clength      = ne_propset_value( set, &ls_props[1] );
    resourcetype = ne_propset_value( set, &ls_props[2] );
    etag       = ne_propset_value( set, &ls_props[3] );
    file_id      = ne_propset_value( set, &ls_props[4] );
    directDownloadUrl = ne_propset_value( set, &ls_props[5] );
    directDownloadCookies = ne_propset_value( set, &ls_props[6] );
    perm = ne_propset_value( set, &ls_props[7] );

    if( resourcetype && strncmp( resourcetype, "<DAV:collection>", 16 ) == 0) {
        newres->type = resr_collection;
    } else {
        newres->type = resr_normal;
    }

    if (modtime) {
        newres->modtime = oc_httpdate_parse(modtime);
    }

    /* DEBUG_WEBDAV("Parsing Modtime: %s -> %llu", modtime, (unsigned long long) newres->modtime ); */
    newres->size = 0;
    if (clength) {
        newres->size = atoll(clength);
        /* DEBUG_WEBDAV("Parsed File size for %s from %s: %lld", newres->name, clength, (long long)newres->size ); */
    }

    if( etag ) {
        newres->md5 = csync_normalize_etag(etag);
    }

    csync_vio_set_file_id(newres->file_id, file_id);
    /*
    DEBUG_WEBDAV("propfind_results_recursive %s [%s] %s", newres->uri, newres->type == resr_collection ? "collection" : "file", newres->md5);
    */

    if (directDownloadUrl) {
        newres->directDownloadUrl = c_strdup(directDownloadUrl);
    }
    if (directDownloadCookies) {
        newres->directDownloadCookies = c_strdup(directDownloadCookies);
    }
    if (perm && !perm[0]) {
        // special meaning for our code: server returned permissions but are empty
        // meaning only reading is allowed for this resource
        newres->remotePerm[0] = ' ';
        // see _csync_detect_update()
    } else if (perm && strlen(perm) < sizeof(newres->remotePerm)) {
        strncpy(newres->remotePerm, perm, sizeof(newres->remotePerm));
    } else {
        // old server, keep newres->remotePerm empty
    }
}