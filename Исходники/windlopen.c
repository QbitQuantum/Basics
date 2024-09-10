/* gets the list of mechanisms */
int _sasl_load_plugins(const add_plugin_list_t *entrypoints,
		       const sasl_callback_t *getpath_cb,
		       const sasl_callback_t *verifyfile_cb)
{
    int result;
    TCHAR cur_dir[PATH_MAX], full_name[PATH_MAX+2], prefix[PATH_MAX+2];
				/* 1 for '\\' 1 for trailing '\0' */
    TCHAR * pattern;
    TCHAR c;
    int pos;
    int retCode = SASL_OK;
    char *utf8path = NULL;
    TCHAR *path=NULL;
    int position;
    const add_plugin_list_t *cur_ep;
    struct _stat statbuf;		/* filesystem entry information */
    intptr_t fhandle;			/* file handle for _findnext function */
    struct _tfinddata_t finddata;	/* data returned by _findnext() */
    size_t prefix_len;
    
    /* for static plugins */
    add_plugin_t *add_plugin;
    _sasl_plug_type type;
    _sasl_plug_rec *p;

    if (! entrypoints
	|| ! getpath_cb
	|| getpath_cb->id != SASL_CB_GETPATH
	|| ! getpath_cb->proc
	|| ! verifyfile_cb
	|| verifyfile_cb->id != SASL_CB_VERIFYFILE
	|| ! verifyfile_cb->proc)
	return SASL_BADPARAM;

    /* do all the static plugins first */

    for (cur_ep = entrypoints; cur_ep->entryname; cur_ep++) {

        /* What type of plugin are we looking for? */
        if (!strcmp(cur_ep->entryname, "sasl_server_plug_init")) {
            type = SERVER;
            add_plugin = (add_plugin_t *)sasl_server_add_plugin;
        }
        else if (!strcmp(cur_ep->entryname, "sasl_client_plug_init")) {
            type = CLIENT;
            add_plugin = (add_plugin_t *)sasl_client_add_plugin;
        }
        else if (!strcmp(cur_ep->entryname, "sasl_auxprop_plug_init")) {
            type = AUXPROP;
            add_plugin = (add_plugin_t *)sasl_auxprop_add_plugin;
        }
        else if (!strcmp(cur_ep->entryname, "sasl_canonuser_init")) {
            type = CANONUSER;
            add_plugin = (add_plugin_t *)sasl_canonuser_add_plugin;
        }
        else {
            /* What are we looking for then? */
            return SASL_FAIL;
        }
        for (p = _sasl_static_plugins; p->type; p++) {
            if (type == p->type)
                result = add_plugin(p->name, p->plug);
        }
    }

    /* get the path to the plugins */
    result = ((sasl_getpath_t *)(getpath_cb->proc))(getpath_cb->context,
						    &utf8path);
    if (result != SASL_OK) return result;
    if (!utf8path) return SASL_FAIL;

    if (sizeof(TCHAR) == sizeof(char)) {
        path = (TCHAR*)utf8path;
    }
    else {
        path = _sasl_utf8_to_wchar(utf8path);
        if (!path) return SASL_FAIL;
    }

    if (_tcslen(path) >= PATH_MAX) { /* no you can't buffer overrun */
	    retCode = SASL_FAIL;
        goto cleanup;
    }

    position=0;
    do {
	pos=0;
	do {
	    c=path[position];
	    position++;
	    cur_dir[pos]=c;
	    pos++;
	} while ((c!=PATHS_DELIMITER) && (c!=0));
	cur_dir[pos-1]='\0';


/* : check to make sure that a valid directory name was passed in */
	if (_tstat (cur_dir, &statbuf) < 0) {
	    continue;
	}
	if ((statbuf.st_mode & S_IFDIR) == 0) {
	    continue;
	}

    _tcscpy(prefix, cur_dir);
	prefix_len = _tcslen (prefix);

/* : Don't append trailing \ unless required */
	if (prefix[prefix_len-1] != '\\') {
        _tcscat(prefix,_T("\\"));
	    prefix_len++;
	}

	pattern = prefix;

/* : Check that we have enough space for "*.dll" */
	if ((prefix_len + DLL_MASK_LEN) > (sizeof(prefix) / sizeof(TCHAR) - 1)) {
	    _sasl_log(NULL, SASL_LOG_WARN, "plugin search mask is too big");
            continue;
	}

	_tcscat (prefix + prefix_len, _T("*") DLL_SUFFIX);

        fhandle = _tfindfirst (pattern, &finddata);
        if (fhandle == -1) {	/* no matching files */
            continue;
        }

/* : Truncate "*.dll" */
	prefix[prefix_len] = '\0';

	do {
	    size_t length;
	    void *library;
	    char *c;
	    char plugname[PATH_MAX];
	    int entries;

	    length = _tcslen(finddata.name);
	    if (length < 5) { /* At least <Ch>.dll */
		continue; /* can not possibly be what we're looking for */
	    }

/* : Check for overflow */
	    if (length + prefix_len >= PATH_MAX) continue; /* too big */

	    if (_tcscmp(finddata.name + (length - _tcslen(DLL_SUFFIX)), DLL_SUFFIX) != 0) {
		continue;
	    }

/* : Check that it is not a directory */
	    if ((finddata.attrib & _A_SUBDIR) == _A_SUBDIR) {
		continue;
	    }

/* : Construct full name from prefix and name */

        _tcscpy (full_name, prefix);
        _tcscat (full_name, finddata.name);
		
/* cut off .dll suffix -- this only need be approximate */
        if (sizeof(TCHAR) != sizeof(char)) {
            if (WideCharToMultiByte(CP_UTF8, 0, finddata.name, -1, plugname, sizeof(plugname), NULL, NULL) == 0) { // in case of unicode use utf8
                continue;
            }
        }
        else {
            _tcscpy((TCHAR*)plugname, finddata.name); // w/o unicode local enconding is fine
        }
	    c = strchr(plugname, '.');
	    if (c != NULL) *c = '\0';

	    result = _tsasl_get_plugin (full_name, verifyfile_cb, &library);

	    if (result != SASL_OK) {
		continue;
	    }

	    entries = 0;
	    for (cur_ep = entrypoints; cur_ep->entryname; cur_ep++) {
		result = _sasl_plugin_load(plugname,
					   library,
					   cur_ep->entryname,
					   cur_ep->add_plugin);
		if (result == SASL_OK) {
		    ++entries;
		}
		/* If this fails, it's not the end of the world */
	    }
	    if (entries == 0) {
		_sasl_remove_last_plugin();
	    }

	} while (_tfindnext (fhandle, &finddata) == 0);
	
	_findclose (fhandle);

    } while ((c!='=') && (c!=0));

cleanup:
    if (sizeof(TCHAR) != sizeof(char)) {
        sasl_FREE(path); /* It's always allocated in coversion to wchar */
    }
    return retCode;
}