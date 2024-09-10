 FILE* track_freopen(const char *path, const char *mode, FILE *stream)
 {
   uintptr_t loc = (uintptr_t)_ReturnAddress();
   
   tracker_file_free(loc, (uintptr_t)stream, FILE_XBMC_FOPEN);
   stream = dll_freopen(path, mode, stream);
   if (stream)
     tracker_file_track(loc, (uintptr_t)stream, FILE_XBMC_FOPEN, path);
   return stream;
 }