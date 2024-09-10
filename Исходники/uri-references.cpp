void URIReference::attach(const URI &uri) throw(BadURIException)
{
    SPDocument *document = NULL;

    // Attempt to get the document that contains the URI
    if (_owner) {
        document = _owner->document;
    } else if (_owner_document) {
        document = _owner_document;
    }

    // createChildDoc() assumes that the referenced file is an SVG.
    // PNG and JPG files are allowed (in the case of feImage).
    gchar *filename = uri.toString();
    bool skip = false;
    if( g_str_has_suffix( filename, ".jpg" ) ||
        g_str_has_suffix( filename, ".JPG" ) ||
        g_str_has_suffix( filename, ".png" ) ||
        g_str_has_suffix( filename, ".PNG" ) ) {
        skip = true;
    }
 
    // The path contains references to separate document files to load.
    if(document && uri.getPath() && !skip ) {
        std::string base = document->getBase() ? document->getBase() : "";
        std::string path = uri.getFullPath(base);
        if(!path.empty()) {
            document = document->createChildDoc(path);
        } else {
            document = NULL;
        }
    }
    if(!document) {
        g_warning("Can't get document for referenced URI: %s", filename);
        g_free( filename );
        return;
    }
    g_free( filename );

    gchar const *fragment = uri.getFragment();
    if ( !uri.isRelative() || uri.getQuery() || !fragment ) {
        throw UnsupportedURIException();
    }

    /* FIXME !!! real xpointer support should be delegated to document */
    /* for now this handles the minimal xpointer form that SVG 1.0
     * requires of us
     */
    gchar *id = NULL;
    if (!strncmp(fragment, "xpointer(", 9)) {
        /* FIXME !!! this is wasteful */
        /* FIXME: It looks as though this is including "))" in the id.  I suggest moving
           the strlen calculation and validity testing to before strdup, and copying just
           the id without the "))".  -- pjrm */
        if (!strncmp(fragment, "xpointer(id(", 12)) {
            id = g_strdup(fragment+12);
            size_t const len = strlen(id);
            if ( len < 3 || strcmp(id+len-2, "))") ) {
                g_free(id);
                throw MalformedURIException();
            }
        } else {
            throw UnsupportedURIException();
        }
    } else {
        id = g_strdup(fragment);
    }

    /* FIXME !!! validate id as an NCName somewhere */

    _connection.disconnect();
    delete _uri;
    _uri = new URI(uri);

    _setObject(document->getObjectById(id));
    _connection = document->connectIdChanged(id, sigc::mem_fun(*this, &URIReference::_setObject));

    g_free(id);
}