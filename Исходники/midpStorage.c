/*
 * Read from an open file in storage, returning the number of bytes read or
 * -1 for the end of the file. May read less than the length of the buffer.
 *
 * If not successful *ppszError will set to point to an error string,
 * on success it will be set to NULL.
 */
long
storageRead(char** ppszError, int handle, char* buffer, long length) {
    long bytesRead;

    *ppszError = NULL;
    if (0 == length) {
        return 0;
    }

    bytesRead = pcsl_file_read((void *)handle, (unsigned char*)buffer, length);

    REPORT_INFO2(LC_CORE, "storageRead on fd %d res = %ld\n",
          handle, bytesRead);

    if (-1 == bytesRead) {
        *ppszError = getLastError("storageRead()");
    } else if (0 == bytesRead) {
        /* end of file in java is -1 */
        bytesRead = -1;
    }

    return bytesRead;
}