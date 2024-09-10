zdir_t *
zdir_new (const char *path, const char *parent)
{
    zdir_t *self = (zdir_t *) zmalloc (sizeof (zdir_t));
    assert (self);

    if (parent) {
        if (streq (parent, "-")) {
            self->trimmed = true;
            self->path = strdup (path);
            if (!self->path) {
                zdir_destroy (&self);
                return NULL;
            }
        }
        else {
            self->path = (char *) zmalloc (strlen (path) + strlen (parent) + 2);
            if (self->path)
                sprintf (self->path, "%s/%s", parent, path);
            else {
                zdir_destroy (&self);
                return NULL;
            }
        }
    }
    else {
        self->path = strdup (path);
        if (!self->path) {
            zdir_destroy (&self);
            return NULL;
        }
    }
    if (self->path)
        self->files = zlist_new ();
    if (self->files)
        self->subdirs = zlist_new ();
    if (!self->subdirs) {
        zdir_destroy (&self);
        return NULL;
    }

#if (defined (WIN32))
    //  On Windows, replace backslashes by normal slashes
    char *path_clean_ptr = self->path;
    while (*path_clean_ptr) {
        if (*path_clean_ptr == '\\')
            *path_clean_ptr = '/';
        path_clean_ptr++;
    }
    //  Remove any trailing slash
    if (self->path [strlen (self->path) - 1] == '/')
        self->path [strlen (self->path) - 1] = 0;

    //  Win32 wants a wildcard at the end of the path
    char *wildcard = (char *) zmalloc (strlen (self->path) + 3);
    if (!wildcard) {
        zdir_destroy (&self);
        return NULL;
    }
    sprintf (wildcard, "%s/*", self->path);
    WIN32_FIND_DATAA entry;
    HANDLE handle = FindFirstFileA (wildcard, &entry);
    freen (wildcard);

    if (handle != INVALID_HANDLE_VALUE) {
        //  We have read an entry, so return those values
        s_win32_populate_entry (self, &entry);
        while (FindNextFileA (handle, &entry))
            s_win32_populate_entry (self, &entry);
        FindClose (handle);
    }
#else
    //  Remove any trailing slash
    if (self->path [strlen (self->path) - 1] == '/')
        self->path [strlen (self->path) - 1] = 0;

    DIR *handle = opendir (self->path);
    if (handle) {
        // readdir_r is deprecated in glibc 2.24, but readdir is still not
        // guaranteed to be thread safe if the same directory is accessed
        // by different threads at the same time. Unfortunately given it was
        // not a constraint before we cannot change it now as it would be an
        // API breakage. Use a global lock when scanning the directory to
        // work around it.
        pthread_mutex_lock (&s_readdir_mutex);
        struct dirent *entry = readdir (handle);
        pthread_mutex_unlock (&s_readdir_mutex);
        while (entry != NULL) {
            // Beware of recursion. Lock only around readdir calls.
            s_posix_populate_entry (self, entry);
            pthread_mutex_lock (&s_readdir_mutex);
            entry = readdir (handle);
            pthread_mutex_unlock (&s_readdir_mutex);
        }
        closedir (handle);
    }
#endif
    else {
        zdir_destroy (&self);
        return NULL;
    }
    //  Update directory signatures
    zdir_t *subdir = (zdir_t *) zlist_first (self->subdirs);
    while (subdir) {
        if (self->modified < subdir->modified)
            self->modified = subdir->modified;
        self->cursize += subdir->cursize;
        self->count += subdir->count;
        subdir = (zdir_t *) zlist_next (self->subdirs);
    }
    zfile_t *file = (zfile_t *) zlist_first (self->files);
    while (file) {
        if (self->modified < zfile_modified (file))
            self->modified = zfile_modified (file);
        self->cursize += zfile_cursize (file);
        self->count += 1;
        file = (zfile_t *) zlist_next (self->files);
    }
    return self;
}