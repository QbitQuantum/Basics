nfsstat3 CNFS3Prog::ProcedureREAD(void)
{
    char *path;
    offset3 offset;
    count3 count;
    post_op_attr file_attributes;
    bool eof;
    opaque data;
    nfsstat3 stat;
    FILE *pFile;

    PrintLog("READ");
    path = GetPath();
    Read(&offset);
    Read(&count);
    stat = CheckFile(path);

    if (stat == NFS3_OK) {
        data.SetSize(count);
        pFile = _fsopen(path, "rb", _SH_DENYWR);

        if (pFile != NULL) {
            _fseeki64(pFile, offset, SEEK_SET) ;
            count = fread(data.contents, sizeof(char), count, pFile);
            eof = fgetc(pFile) == EOF;
            fclose(pFile);
        } else {
            char buffer[BUFFER_SIZE];
            errno_t errorNumber = errno;
            strerror_s(buffer, BUFFER_SIZE, errorNumber);
            PrintLog(buffer);

            if (errorNumber == 13) {
                stat = NFS3ERR_ACCES;
            } else {
                stat = NFS3ERR_IO;
            }
        }
    }

    file_attributes.attributes_follow = GetFileAttributesForNFS(path, &file_attributes.attributes);

    Write(&stat);
    Write(&file_attributes);

    if (stat == NFS3_OK) {
        Write(&count);
        Write(&eof);
        Write(&data);
    }

    return stat;
}