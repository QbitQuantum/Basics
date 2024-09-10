SDL_RWops *
SDL_RWFromFile(const char *file, const char *mode)
{
    SDL_RWops *rwops = NULL;
    if (!file || !*file || !mode || !*mode) {
        SDL_SetError("SDL_RWFromFile(): No file or no mode specified");
        return NULL;
    }
#if defined(ANDROID)
#ifdef HAVE_STDIO_H
    /* Try to open the file on the filesystem first */
    if (*file == '/') {
        FILE *fp = fopen(file, mode);
        if (fp) {
            return SDL_RWFromFP(fp, 1);
        }
    } else {
        /* Try opening it from internal storage if it's a relative path */
        char *path;
        FILE *fp;

        path = SDL_stack_alloc(char, PATH_MAX);
        if (path) {
            SDL_snprintf(path, PATH_MAX, "%s/%s",
                         SDL_AndroidGetInternalStoragePath(), file);
            fp = fopen(path, mode);
            SDL_stack_free(path);
            if (fp) {
                return SDL_RWFromFP(fp, 1);
            }
        }
    }
#endif /* HAVE_STDIO_H */

    /* Try to open the file from the asset system */
    rwops = SDL_AllocRW();
    if (!rwops)
        return NULL;            /* SDL_SetError already setup by SDL_AllocRW() */
    if (Android_JNI_FileOpen(rwops, file, mode) < 0) {
        SDL_FreeRW(rwops);
        return NULL;
    }
    rwops->size = Android_JNI_FileSize;
    rwops->seek = Android_JNI_FileSeek;
    rwops->read = Android_JNI_FileRead;
    rwops->write = Android_JNI_FileWrite;
    rwops->close = Android_JNI_FileClose;
    rwops->type = SDL_RWOPS_JNIFILE;

#elif defined(__WIN32__)
    rwops = SDL_AllocRW();
    if (!rwops)
        return NULL;            /* SDL_SetError already setup by SDL_AllocRW() */
    if (windows_file_open(rwops, file, mode) < 0) {
        SDL_FreeRW(rwops);
        return NULL;
    }
    rwops->size = windows_file_size;
    rwops->seek = windows_file_seek;
    rwops->read = windows_file_read;
    rwops->write = windows_file_write;
    rwops->close = windows_file_close;
    rwops->type = SDL_RWOPS_WINFILE;

#elif HAVE_STDIO_H
    {
        #ifdef __APPLE__
        FILE *fp = SDL_OpenFPFromBundleOrFallback(file, mode);
        #elif __WINRT__
        FILE *fp = NULL;
        fopen_s(&fp, file, mode);
        #else
        FILE *fp = fopen(file, mode);
        #endif
        if (fp == NULL) {
            SDL_SetError("Couldn't open %s", file);
        } else {
            rwops = SDL_RWFromFP(fp, 1);
        }
    }
#else
    SDL_SetError("SDL not compiled with stdio support");
#endif /* !HAVE_STDIO_H */

    return rwops;
}