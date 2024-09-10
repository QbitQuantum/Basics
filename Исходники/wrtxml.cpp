static int32_t write_utf8_file(FileStream* fileStream, UnicodeString outString)
{
    UErrorCode status = U_ZERO_ERROR;
    int32_t len = 0;

    // preflight to get the destination buffer size
    u_strToUTF8(NULL,
                0,
                &len,
                outString.getBuffer(),
                outString.length(),
                &status);

    // allocate the buffer
    char* dest = (char*)uprv_malloc(len);
    status = U_ZERO_ERROR;

    // convert the data
    u_strToUTF8(dest,
                len,
                &len,
                outString.getBuffer(),
                outString.length(),
                &status);

    // write data to out file
    int32_t ret = T_FileStream_write(fileStream, dest, len);
    uprv_free(dest);
    return (ret);
}