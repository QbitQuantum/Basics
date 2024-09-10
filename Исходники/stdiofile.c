static void *stdiofile_contents(void *ptr, size_t *size)
{
    struct stdiofile *self = ptr;
    int oflag;
#ifndef WIN32
    int prot;
    struct stat s;
#endif

    if (self->contents) {
        if (size) {
            *size = self->size;
        }
        return self->contents;
    }
#ifdef WIN32
    oflag = (self->mode&ILA_FILE_READ?   FILE_MAP_READ    : 0) |
            (self->mode&ILA_FILE_WRITE?  FILE_MAP_WRITE   : 0);// |
            //(self->mode&ILA_FILE_EXEC?   FILE_MAP_EXECUTE : 0); // TODO: find out why mingw thinks there's no such thing as executable files
    self->handle = OpenFileMappingA(oflag, FALSE, self->path);
    self->size = GetFileSize(self->handle, NULL);
    self->contents = MapViewOfFile(self->handle, oflag, 0, 0, self->size);
#else
    oflag = (self->mode&ILA_FILE_READ && self->mode&ILA_FILE_WRITE? O_RDWR :
                (self->mode&ILA_FILE_READ? O_RDONLY : 0) |
                (self->mode&ILA_FILE_WRITE? O_WRONLY : 0));
    self->fd = open(self->path, oflag);
    if (fstat(self->fd, &s) != 0) {
        return NULL;
    }
    self->size = s.st_size;
    prot = (self->mode&ILA_FILE_READ?  PROT_READ  : 0) |
           (self->mode&ILA_FILE_WRITE? PROT_WRITE : 0) |
           (self->mode&ILA_FILE_EXEC?  PROT_EXEC  : 0);
    self->contents = mmap(NULL, self->size, prot, MAP_SHARED, self->fd, 0);
#endif
    if (size) {
        *size = self->size;
    }
    return self->contents;
}